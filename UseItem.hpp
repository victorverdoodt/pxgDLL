#pragma once
#ifndef USEITEM
#define USEITEM
class UseItem : public pComponent
{
public:
	bool bEnabled = true;
	bool bInited = false;

	UseItem() { strcpy(classname, "LocalPlayer");  strcpy(version, "0.1.0"); };
	~UseItem() {};
	Game GameContext;
	void onStart(Game game)
	{
		bInited = true;
	}
	bool teste = false;


	class ItemData
	{
	public:
		bool Enabled = false;
		int ItemId = 0;
		int Cd = 1;
		DWORD cdTimer;
		int Type = 0;
		int Health = 25;
		int targetId = 0;

	};
	std::vector<ItemData> Items;
	bool canUse(int index) {
		if (((clock() - Items[index].cdTimer) / (double)CLOCKS_PER_SEC) > Items[index].Cd + 1) {
			return true;
		}
		return false;
	}


	void onUpdate(Game game)
	{
		if (!bInited)
			return;

		if (!bEnabled)
			return;

		for (int i = 0; i < Items.size(); i++) {
			auto Item = Items[i];
			if (Item.Enabled && canUse(i)) {
				if (Item.Type == 0) {//USE ON SUMMON
					if (mySummon->getHealthPercent() <= Item.Health) {
						useOnCreature(GamePtr, Item.ItemId, mySummon);
						Item.cdTimer = clock();
					}
				}
				else if (Item.Type == 1) {//USE ON POS
					auto teste = getContainers(GamePtr);
					for (auto i : teste) {
						if (Item.targetId == i.getServerId()) {
							useOnItem(GamePtr, Item.ItemId, i);
							Item.cdTimer = clock();
						}
					}
					
				}
				else if (Item.Type == 2) {//USE ON PLAYER
					useOnCreature(GamePtr, Item.ItemId, (CreaturePtr*)GamePtr.GetLocalPlayer());
					Item.cdTimer = clock();
				}

			}
		}

		GameContext = game;
	}

	void MiscTab()
	{
		//ItemId;
		//Typo -> Use, UseOnSummon
		
		ImGui::Separator();
		if (ImGui::SmallButton("Add")) { 
			ItemData defaultData;
			Items.push_back(defaultData);
		};
		ImGui::SameLine();
		if (ImGui::SmallButton("Clear")) { Items.clear(); };
		//"UseOnItem" 
		const char* line_items[] = { "UseOnPokemon", "UseOnItem", "UseOnPlayer"};
		for (std::vector<int>::size_type i = 0; i != Items.size(); i++) {
			ImGui::PushID(i);
			if (ImGui::TreeNode("Item "))
			{
				ImGui::Checkbox("##eI1", &Items[i].Enabled); ImGui::SameLine();
				ImGui::Combo("Type", &Items[i].Type, line_items, IM_ARRAYSIZE(line_items), 4);
				ImGui::InputInt("ItemId", &Items[i].ItemId);
				ImGui::InputInt("Cd", &Items[i].Cd);
				if (Items[i].Type == 0) {
					ImGui::InputInt("Health", &Items[i].Health);
				}
				else if (Items[i].Type == 1) {
					ImGui::InputInt("TargetId", &Items[i].targetId);
				}
				ImGui::TreePop();
			}
			ImGui::PopID();

		}
		ImGui::Separator();

	}

	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::BeginTabItem("Items"))
		{
			MiscTab();
			ImGui::EndTabItem();
		}
	}
};
#endif