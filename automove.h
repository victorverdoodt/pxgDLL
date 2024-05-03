#pragma once
#ifndef AUTOMOVE
#define AUTOMOVE
class AutoMove : public pComponent
{
public:
	bool bEnabled = false;
	bool bInited = false;
	bool lEnabled = false;
	int lastWalkIndex = -1;


	AutoMove() { strcpy(classname, "AutoMove");  strcpy(version, "0.1.0"); };
	~AutoMove() {};
	Game GameContext;
	void onStart(Game game)
	{
		bInited = true;
		GameContext = game;
	}

	DWORD dealyTimer;
	void onUpdate(Game game)
	{
		if (!bInited)
			return;

		if (!bEnabled)
			return;

		auto creatures = WayPoints;
		for (int i = 0; i < creatures.size(); i++) {
			Position pCreature = creatures[i];
			if (pCreature.z == GamePtr.GetLocalPlayer()->GetPosition().z) {
				//getEnemiesRange(CreaturePtr* cid, int range, bool filter = true)
				if (ReadMemory<CreaturePtr*>(baseAddr + gGame + 0x4) == nullptr && !GamePtr.GetLocalPlayer()->isAutoWalking() && !GamePtr.GetLocalPlayer()->isWalking() && (!GamePtr.GetAttackTarget() || GamePtr.GetAttackTarget()->getHealthPercent() <= 0 || _lastTarget == nullptr)) {

					auto pickLoot = false;
					if (pickLoot) {
						int Dist = 10000;
						ItemPtr Selected;
						auto teste = haveLootToGet(GamePtr);

						for (auto &i : teste) {
							auto newDist = i.getPosition().distance(GamePtr.GetLocalPlayer()->GetPosition());
							if (newDist < Dist) {
								Dist = newDist;
								Selected = i;
							}
							//use(GamePtr, getTopThing(i.getPosition()));
						}
						if (Dist < 10000 && !selectedLootPos.isValid()) {
							selectedLootPos = Selected.getPosition();
							console.AddLog("seted pos");
						}

						if (selectedLootPos.isValid()) {
							use(GamePtr, getTopThing(selectedLootPos));
						}
						else {
							if (i > lastWalkIndex) {
								lastWalkIndex = i;
								doWalkToPosition(GamePtr, pCreature);
							}
						}
					}else{
						if (i > lastWalkIndex) {
							lastWalkIndex = i;
							doWalkToPosition(GamePtr, pCreature);
						}
					}
				}
			}
		}

		if (lastWalkIndex >= creatures.size()-1 && !GamePtr.GetLocalPlayer()->isAutoWalking() && !GamePtr.GetLocalPlayer()->isWalking()) {
			lastWalkIndex = -1;
		}


		GameContext = game;
	}

	void RenderCreatureList()
	{
		ImGui::Columns(1, "mycolumns");
		ImGui::Separator();
		ImGui::Text("Position"); ImGui::NextColumn();
		ImGui::Separator();

		auto creatures = WayPoints;
		for (int i = 0; i < creatures.size(); i++) {
			Position pCreature = creatures[i];
			if (pCreature.z == GamePtr.GetLocalPlayer()->GetPosition().z) {
				if (i == lastWalkIndex) {
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "x: %i, y: %i z: %i", pCreature.x, pCreature.y, pCreature.z); ImGui::NextColumn();
				}
				else {
					ImGui::Text("x: %i, y: %i z: %i", pCreature.x, pCreature.y, pCreature.z); ImGui::NextColumn();
				}
				
			}
		}

		ImGui::Columns(1);
		ImGui::Separator();
	}

	void MiscTab()
	{

		ImGui::Checkbox("##Enabled", &bEnabled); ImGui::SameLine();
		ImGui::InputInt("EnemiesToStop##eId2", &enemiesToStop);
		ImGui::Checkbox("Loot##Loot", &lEnabled);


		if (ImGui::SmallButton("Add")) { WayPoints.push_back(GamePtr.GetLocalPlayer()->GetPosition()); };
		ImGui::SameLine();
		if (ImGui::SmallButton("Clear")) { WayPoints.clear(); };

		ImGui::Separator();

		RenderCreatureList();

		ImGui::Separator();

	}

	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::BeginTabItem("Waypoints"))
		{
			MiscTab();
			ImGui::EndTabItem();
		}
	}
};
#endif