// Supported with union (c) 2020 Union team
// Union SOURCE file
namespace GOTHIC_ENGINE {
	int (*innerEvalFunc)(const zSTRING&, zSTRING&);

	

	bool chestsRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("chests_shuffle")) {
			auto result = shuffleChests();
			msg = "Shuffled container for: " + Z result + " items.";

			return true;
		}
	}



	int ConsoleEvalFunc(const zSTRING& inpstr, zSTRING& msg) {
		if (innerEvalFunc && innerEvalFunc(inpstr, msg))
			return true;

		if (inpstr.HasWordI("punclevutils")) {
			if (inpstr.HasWordI("debug")) {
				IS_DEBUG = IS_DEBUG ? 0 : 1;
				msg = "Debug: " + IS_DEBUG;
				
				return true;
			}

			return chestsRandomizerHandler(inpstr, msg);
		}


		return false;
	}

	void RegisterEvalFunc() {
		int evalNum = 0;

		for (int i = 1; i < zCON_MAX_EVAL; i++)
			if (zcon->evalfunc[i])
				evalNum = i;

		innerEvalFunc = zcon->evalfunc[evalNum];
		zcon->evalfunc[evalNum] = &ConsoleEvalFunc;
	}

	void RegisterCommands() {
		RegisterEvalFunc();
		zcon->Register("punclevutils debug", "Toggle debug");
		zcon->Register("punclevutils chests_shuffle", "shuffle chests");
	}
}