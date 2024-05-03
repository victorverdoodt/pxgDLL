#pragma once
#ifndef HELPER
#define HELPER
using namespace std;
class Cavebot : public pComponent
{
public:
	Cavebot() { strcpy(classname, "CaveBot");  strcpy(version, "0.1.0"); };
	~Cavebot() {};
	Game GameContext;
	bool bEnabled = false;
	bool bInited = false;

	void onStart(Game game)
	{
		bInited = true;
		GameContext = game;
	}

	DWORD F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12;
	void sendAttacks(WPARAM key, int timer) {
		if (!bEnabled)
			return;

		if (GetActiveWindowTitle() == "PXG Client") {

			if (((clock() - getSkill(key)) / (double)CLOCKS_PER_SEC) > timer) {
				setSkill(key, clock());
				SendKeyStroke(key);
				//talk(GamePtr, "#s m1");
			}
		}
	}

	void setSkill(WPARAM key, DWORD value) {
		switch (key)
		{
		case VK_F1:
			F1 = value;
			break;
		case VK_F2:
			F2 = value;
			break;
		case VK_F3:
			F3 = value;
			break;
		case VK_F4:
			F4 = value;
			break;
		case VK_F5:
			F5 = value;
			break;
		case VK_F6:
			F6 = value;
			break;
		case VK_F7:
			F7 = value;
			break;
		case VK_F8:
			F8 = value;
			break;
		case VK_F9:
			F9 = value;
			break;
		case VK_F10:
			F10 = value;
			break;
		case VK_F11:
			F11 = value;
			break;
		case VK_F12:
			F12 = value;
			break;
		default:
			break;
		}
	}

	DWORD getSkill(WPARAM key) {
		switch (key)
		{
		case VK_F1:
			return F1;
		case VK_F2:
			return F2;
		case VK_F3:
			return F3;
		case VK_F4:
			return F4;
		case VK_F5:
			return F5;
		case VK_F6:
			return F6;
		case VK_F7:
			return F7;
		case VK_F8:
			return F8;
		case VK_F9:
			return F9;
		case VK_F10:
			return F10;
		case VK_F11:
			return F11;
		case VK_F12:
			return F12;
		default:
			break;
		}
	}

	string GetActiveWindowTitle()
	{
		char wnd_title[256];
		HWND hwnd = GetForegroundWindow(); // get handle of currently active window
		GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
		return wnd_title;
	}

	int32_t areaTeste[13][13] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	void onUpdate(Game game)
	{
		if (!bInited)
			return;

		if (!bEnabled)
			return;

		auto creatures = CreatureCache;
		for (int i = 0; i < creatures.size(); i++) {
			CreaturePtr* pCreature = creatures[i];
			if (pCreature) {
				if (pCreature->isValid() && pCreature->isDiff((CreaturePtr*)GameContext.GetLocalPlayer())) {
					if (isPartOf(target, pCreature->GetName()) && pCreature->GetPosition().distance(GameContext.GetLocalPlayer()->GetPosition()) <= 7)
						doAttackCreature(GamePtr, pCreature);
				}
			}
		}

		GameContext = game;
	}

	void RenderCreatureList()
	{
		if (ImGui::TreeNode("CreatureList"))
		{
			ImGui::Columns(3, "mycolumns");
			ImGui::Separator();
			ImGui::Text("Name"); ImGui::NextColumn();
			ImGui::Text("Health"); ImGui::NextColumn();
			ImGui::Text("LookType"); ImGui::NextColumn();
			ImGui::Separator();

			auto creatures = CreatureCache;
			for (int i = 0; i < creatures.size(); i++) {
				CreaturePtr* pCreature = creatures[i];
				if (pCreature) {
					if (pCreature->isValid() && !pCreature->isPlayer() && !pCreature->isSummon() && pCreature->isDiff((CreaturePtr*)GameContext.GetLocalPlayer())) {
						auto it = std::find(ExcludeCreatureCache.begin(), ExcludeCreatureCache.end(), pCreature);
						if (it != ExcludeCreatureCache.end())
						{
							ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), pCreature->GetName());  ImGui::NextColumn();
							ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", pCreature->getHealthPercent()); ImGui::NextColumn();
							ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", pCreature->getOutfit().LookType); ImGui::NextColumn();
						}
						else {
							ImGui::Text(pCreature->GetName()); ImGui::NextColumn();
							ImGui::Text("%i", pCreature->getHealthPercent()); ImGui::NextColumn();
							ImGui::Text("%i", pCreature->getOutfit().LookType); ImGui::NextColumn();
						}
					}
				}
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::TreePop();
		}
	}

	void MiscTab()
	{

		ImGui::Checkbox("Enabled", &bEnabled);

		ImGui::InputText("AtttackTarget", target, IM_ARRAYSIZE(target));
/*/
		if (ImGui::TreeNode("Skill"))
		{
			ImGui::Checkbox("F1", &F1Enabled); ImGui::InputInt("Id", &i0);
			ImGui::TreePop();
		}*/


			if (ImGui::SmallButton("Clear")) { ExcludeCreatureCache.clear(); };

			ImGui::Separator();

			RenderCreatureList();
		

		ImGui::Separator();

	}

	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::BeginTabItem("Creatures"))
		{
			MiscTab();
			ImGui::EndTabItem();
		}
	}
};
#endif