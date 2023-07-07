// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		IS_DEBUG = zoptions->ReadBool("PUNCLEVUTILS", "Debug", FALSE);
		SHOULD_SHUFFLE_CHESTS = zoptions->ReadBool("PUNCLEVUTILS", "ShouldShuffleChests", FALSE);
	}
}