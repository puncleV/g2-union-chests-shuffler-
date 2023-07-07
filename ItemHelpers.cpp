// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	const int BIT_ITEM_QUESTITEM = (1 << 19);

	bool IsQuestItem(oCItem* item) {
		if ((item->hitp & BIT_ITEM_QUESTITEM) != 0) {
			return true;
		}
		return false;
	}

	bool IsIgnoredOrTestItem(oCItem* item) {
		if (item == nullptr) {
			return false;
		}

		auto name = item->GetObjectName();
		return name.HasWordI("ITKE_") || name.HasWordI("LUTERO") || name.HasWordI("SNC_SPEC");
	}
}