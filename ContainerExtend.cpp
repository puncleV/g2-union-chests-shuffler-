// Supported with union (c) 2020 Union team
// Union SOURCE file

#include<array>
namespace GOTHIC_ENGINE {
	auto const SHUFFLED_CHEST_FLAG = 16;

    bool oCMobContainer::isShuffled() {
        return (this->hitp & SHUFFLED_CHEST_FLAG) == SHUFFLED_CHEST_FLAG;
    }

    void oCMobContainer::exchangeContentWithAnyOtherChest() {
        zCArray<zCVob*> arrMob;
        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        std::vector<oCMobContainer*> chestsList;

        if (world) {
            world->SearchVobListByClass(oCMobContainer::classDef, arrMob, NULL);
            for (auto i = 0; i < arrMob.GetNumInList(); i += 1) {
                chestsList.push_back(dynamic_cast<oCMobContainer*>(arrMob[i]));
            }
        }

        std::vector<oCMobContainer*> nonTouchedChests;
        for (auto i = 0; i < chestsList.size(); i += 1)
        {
            oCMobContainer* chest = chestsList[i];

            if (chest->containList.GetNumInList() > 0 && !(chest->isShuffled())) {
                nonTouchedChests.push_back(chest);
            }
        }

        for (auto attempt = 0; attempt < 3; attempt += 1) {
            auto chestToSwitchWith = randomizer.getRandomArrayElement(nonTouchedChests);

            std::vector<oCItem*> chestItems;
            std::vector<oCItem*> secondChestItems;

            for (size_t j = 0; j < this->containList.GetNumInList(); ++j) {
                if (IsQuestItem(this->containList[j]) || IsIgnoredOrTestItem(this->containList[j])) {
                    continue;
                }

                chestItems.push_back(this->containList[j]);
                this->Remove(this->containList[j]);
            }

            for (size_t j = 0; j < chestToSwitchWith->containList.GetNumInList(); ++j) {
                if (IsQuestItem(chestToSwitchWith->containList[j]) || IsIgnoredOrTestItem(chestToSwitchWith->containList[j])) {
                    continue;
                }

                secondChestItems.push_back(chestToSwitchWith->containList[j]);
                chestToSwitchWith->Remove(chestToSwitchWith->containList[j]);
            }

            for (size_t j = 0; j < chestItems.size(); ++j) {
                chestToSwitchWith->Insert(chestItems[j]);
            }

            for (size_t j = 0; j < secondChestItems.size(); ++j) {
                this->Insert(secondChestItems[j]);
            }
        }

        this->hitp |= SHUFFLED_CHEST_FLAG;

        chestsList.clear();
        nonTouchedChests.clear();
    }
}