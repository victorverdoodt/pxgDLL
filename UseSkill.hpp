#pragma once
#ifndef SKILLS
#define SKILLS
using namespace std;
class UseSkill : public pComponent
{
public:
	bool bEnabled = true;
	bool bInited = false;

	UseSkill() { strcpy(classname, "UseSkill");  strcpy(version, "0.1.0"); };
	~UseSkill() {};
	Game GameContext;
	class SkillData
	{
	public:
		bool Enabled;
		WPARAM key;
		int Cd;
		int Type;
		int Area;
		int Line;
		int CastCount;

	};

	void onStart(Game game)
	{
		bInited = true;
		GameContext = game;
	}

	DWORD F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12;
	void sendAttacks(WPARAM key, int timer) {

		if (GetActiveWindowTitle() == "PXG Client") {

			if (((clock() - getSkill(key)) / (double)CLOCKS_PER_SEC) > timer + 1) {
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

	bool f1Enabled, f2Enabled, f3Enabled, f4Enabled, f5Enabled, f6Enabled, f7Enabled, f8Enabled, f9Enabled, f10Enabled, f11Enabled, f12Enabled = false;
	int f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12 = 0;
	int sf1, sf2, sf3, sf4, sf5, sf6, sf7, sf8, sf9, sf10, sf11, sf12 = 0;
	int af1, af2, af3, af4, af5, af6, af7, af8, af9, af10, af11, af12 = 0;
	int lf1, lf2, lf3, lf4, lf5, lf6, lf7, lf8, lf9, lf10, lf11, lf12 = 0;
	int nf1, nf2, nf3, nf4, nf5, nf6, nf7, nf8, nf9, nf10, nf11, nf12 = 1;



	SkillData getSkillData(int key) {
		SkillData newDATA;
		switch (key)
		{
		case 1:
			newDATA.Enabled = f1Enabled;
			newDATA.key = VK_F1;
			newDATA.Cd = f1;
			newDATA.Type = sf1;
			newDATA.Area = af1;
			newDATA.Line = lf1;
			newDATA.CastCount = nf1;
			return newDATA;
		case 2:
			newDATA.Enabled = f2Enabled;
			newDATA.key = VK_F2;
			newDATA.Cd = f2;
			newDATA.Type = sf2;
			newDATA.Area = af2;
			newDATA.Line = lf2;
			newDATA.CastCount = nf2;
			return newDATA;
		case 3:
			newDATA.Enabled = f3Enabled;
			newDATA.key = VK_F3;
			newDATA.Cd = f3;
			newDATA.Type = sf3;
			newDATA.Area = af3;
			newDATA.Line = lf3;
			newDATA.CastCount = nf3;
			return newDATA;
		case 4:
			newDATA.Enabled = f4Enabled;
			newDATA.key = VK_F4;
			newDATA.Cd = f4;
			newDATA.Type = sf4;
			newDATA.Area = af4;
			newDATA.Line = lf4;
			newDATA.CastCount = nf4;
			return newDATA;
		case 5:
			newDATA.Enabled = f5Enabled;
			newDATA.key = VK_F5;
			newDATA.Cd = f5;
			newDATA.Type = sf5;
			newDATA.Area = af5;
			newDATA.Line = lf5;
			newDATA.CastCount = nf5;
			return newDATA;
		case 6:
			newDATA.Enabled = f6Enabled;
			newDATA.key = VK_F6;
			newDATA.Cd = f6;
			newDATA.Type = sf6;
			newDATA.Area = af6;
			newDATA.Line = lf6;
			newDATA.CastCount = nf6;
			return newDATA;
		case 7:
			newDATA.Enabled = f7Enabled;
			newDATA.key = VK_F7;
			newDATA.Cd = f7;
			newDATA.Type = sf7;
			newDATA.Area = af7;
			newDATA.Line = lf7;
			newDATA.CastCount = nf7;
			return newDATA;
		case 8:
			newDATA.Enabled = f8Enabled;
			newDATA.key = VK_F8;
			newDATA.Cd = f8;
			newDATA.Type = sf8;
			newDATA.Area = af8;
			newDATA.Line = lf8;
			newDATA.CastCount = nf8;
			return newDATA;
		case 9:
			newDATA.Enabled = f9Enabled;
			newDATA.key = VK_F9;
			newDATA.Cd = f9;
			newDATA.Type = sf9;
			newDATA.Area = af9;
			newDATA.Line = lf9;
			newDATA.CastCount = nf9;
			return newDATA;
		case 10:
			newDATA.Enabled = f10Enabled;
			newDATA.key = VK_F11;
			newDATA.Cd = f10;
			newDATA.Type = sf10;
			newDATA.Area = af10;
			newDATA.Line = lf10;
			newDATA.CastCount = nf10;
			return newDATA;
		case 11:
			newDATA.Enabled = f11Enabled;
			newDATA.key = VK_F11;
			newDATA.Cd = f11;
			newDATA.Type = sf11;
			newDATA.Area = af11;
			newDATA.Line = lf11;
			newDATA.CastCount = nf11;
			return newDATA;
		case 12:
			newDATA.Enabled = f12Enabled;
			newDATA.key = VK_F12;
			newDATA.Cd = f12;
			newDATA.Type = sf12;
			newDATA.Area = af12;
			newDATA.Line = lf12;
			newDATA.CastCount = nf12;
			return newDATA;
		default:
			break;
		}
	}

	int32_t line1[13][13] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	int32_t line3[13][13] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	int32_t area1x1[13][13] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	int32_t area2x2[13][13] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	int32_t area3x3[13][13] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 2, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};


	std::vector<CreaturePtr*> getEnemiesInArea(CreaturePtr* cid, int area[13][13], bool filter = true) {

		std::vector<CreaturePtr*> list;
		auto creatures = CreatureCache;
		for (int i = 0; i < creatures.size(); i++) {
			CreaturePtr* pCreature = creatures[i];
			if (pCreature) {
				if (pCreature->isValid() && pCreature->isDiff((CreaturePtr*)GamePtr.GetLocalPlayer())) {
					if (pCreature->GetPosition().distance(cid->GetPosition()) <= 7) {
						auto tespos = getPosfromArea(cid, area);
						if (filter && isPartOf(target, pCreature->GetName())) {
							for (auto &i : tespos) {
								if (pCreature->GetPosition() == i) {
									list.push_back(pCreature);
								}
							}
						}
						else {
							for (auto &i : tespos) {
								if (pCreature->GetPosition() == i) {
									list.push_back(pCreature);
								}
							}
						}
					}
				}
			}
		}
		return list;
	}


	void onUpdate(Game game)
	{
		if (!bInited)
			return;

		auto actTarget = ReadMemory<CreaturePtr*>(baseAddr + gGame + 0x4);

		for (int i = 1; i < 13; i++) {
			SkillData keyData = getSkillData(i);
			if (keyData.Enabled) {
				if (keyData.Type == 0) { //Target
					if (actTarget != nullptr) {
						sendAttacks(keyData.key, keyData.Cd);
					}
				}
				else if (keyData.Type == 1) {//Heal
					if (mySummon->getHealthPercent() <= 25) {
						sendAttacks(keyData.key, keyData.Cd);
					}
				}
				else if (keyData.Type == 2) {//Area
					if (keyData.Area = 0) {
						auto Enemies = getEnemiesInArea(mySummon, area1x1);
						if (Enemies.size() >= keyData.CastCount) {
							sendAttacks(keyData.key, keyData.Cd);
						}
					}else if (keyData.Area = 1) {
						auto Enemies = getEnemiesInArea(mySummon, area2x2);
						if (Enemies.size() >= keyData.CastCount) {
							sendAttacks(keyData.key, keyData.Cd);
						}
					}else if (keyData.Area = 2) {
						auto Enemies = getEnemiesInArea(mySummon, area3x3);
						if (Enemies.size() >= keyData.CastCount) {
							sendAttacks(keyData.key, keyData.Cd);
						}
					}

				}
				else if (keyData.Type == 3) {//Line
					if (keyData.Line = 0) {
						auto Enemies = getEnemiesInArea(mySummon, line1);
						if (Enemies.size() >= keyData.CastCount) {
							sendAttacks(keyData.key, keyData.Cd);
						}
					}
					else if(keyData.Line = 1){
						auto Enemies = getEnemiesInArea(mySummon, line3);
						std::cout << Enemies.size() << "\n";
						if (Enemies.size() >= keyData.CastCount) {
							sendAttacks(keyData.key, keyData.Cd);
						}
					}
				}
			}
		}

		GameContext = game;
	}

	void MiscTab()
	{
		const char* listbox_items[] = { "Target", "Heal", "AoE", "Line" };
		const char* area_items[] = { "1x1", "2x2", "3x3" };
		const char* line_items[] = { "1", "3" };
		if (ImGui::TreeNode("F1"))
		{
			ImGui::Checkbox("Cd##eF1", &f1Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id1", &f1);
			ImGui::Combo("Type##CF1", &sf1, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf1 > 1) {
				if (sf1 == 2) {
					ImGui::Combo("Area##AF1", &af1, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf1 == 3) {
					ImGui::Combo("Line##LF1", &lf1, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf1", &nf1);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F2"))
		{
			ImGui::Checkbox("##eF2", &f2Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id2", &f2);
			ImGui::Combo("Type##CF2", &sf2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf2 > 1) {
				if (sf2 == 2) {
					ImGui::Combo("Area##AF2", &af2, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf2 == 3) {
					ImGui::Combo("Line##LF2", &lf2, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf2", &nf2);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F3"))
		{
			ImGui::Checkbox("##eF3", &f3Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id3", &f3);
			ImGui::Combo("Type##CF3", &sf3, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf3 > 1) {
				if (sf3 == 2) {
					ImGui::Combo("Area##AF3", &af3, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf3 == 3) {
					ImGui::Combo("Line##LF3", &lf3, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf3", &nf3);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F4"))
		{
			ImGui::Checkbox("##eF4", &f4Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id4", &f4);
			ImGui::Combo("Type##CF4", &sf4, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf4 > 1) {
				if (sf4 == 2) {
					ImGui::Combo("Area##AF4", &af4, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf4 == 3) {
					ImGui::Combo("Line##LF4", &lf4, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf4", &nf4);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F5"))
		{
			ImGui::Checkbox("##eF5", &f5Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id5", &f5);
			ImGui::Combo("Type##CF5", &sf5, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf5 > 1) {
				if (sf5 == 2) {
					ImGui::Combo("Area##AF5", &af5, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf5 == 3) {
					ImGui::Combo("Line##LF5", &lf5, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf5", &nf5);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F6"))
		{
			ImGui::Checkbox("##eF6", &f6Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id6", &f6);
			ImGui::Combo("Type##CF8", &sf6, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf6 > 1) {
				if (sf6 == 2) {
					ImGui::Combo("Area##AF8", &af6, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf6 == 3) {
					ImGui::Combo("Line##LF6", &lf6, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf6", &nf6);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F7"))
		{
			ImGui::Checkbox("##eF7", &f7Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id7", &f7);
			ImGui::Combo("Type##CF8", &sf7, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf7 > 1) {
				if (sf7 == 2) {
					ImGui::Combo("Area##aF8", &af7, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf7 == 3) {
					ImGui::Combo("Line##LF8", &lf7, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf7", &nf7);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F8"))
		{
			ImGui::Checkbox("##eF8", &f8Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id8", &f8);
			ImGui::Combo("Type##CF8", &sf8, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf8 > 1) {
				if (sf8 == 2) {
					ImGui::Combo("Area##AF8", &af8, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf8 == 3) {
					ImGui::Combo("Line##LF8", &lf8, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf8", &nf8);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F9"))
		{
			ImGui::Checkbox("##eF9", &f9Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id9", &f9);
			ImGui::Combo("Type##CF9", &sf9, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf9 > 1) {
				if (sf9 == 2) {
					ImGui::Combo("Area##AF9", &af9, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf9 == 3) {
					ImGui::Combo("Line##LF8", &lf9, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf9", &nf9);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F10"))
		{
			ImGui::Checkbox("##eF10", &f10Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id10", &f10);
			ImGui::Combo("Type##CF10", &sf8, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf10 > 1) {
				if (sf10 == 2) {
					ImGui::Combo("Area##AF10", &af10, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf10 == 3) {
					ImGui::Combo("Line##LF10", &lf10, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf10", &nf10);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F11"))
		{
			ImGui::Checkbox("##eF11", &f11Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id11", &f11);
			ImGui::Combo("Type##CF11", &sf8, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf11 > 1) {
				if (sf8 == 2) {
					ImGui::Combo("Area##AF8", &af11, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf11 == 3) {
					ImGui::Combo("Line##LF11", &lf11, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf11", &nf11);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("F12"))
		{
			ImGui::Checkbox("##eF12", &f12Enabled);
			ImGui::SameLine(); ImGui::InputInt("##Id12", &f12);
			ImGui::Combo("Type##CF12", &sf12, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			if (sf12 > 1) {
				if (sf12 == 2) {
					ImGui::Combo("Area##AF12", &af12, area_items, IM_ARRAYSIZE(area_items), 4);
				}
				else if (sf1 == 3) {
					ImGui::Combo("Line##LF12", &lf12, line_items, IM_ARRAYSIZE(line_items), 4);
				}
				ImGui::InputInt("EnemiesToCast##nf12", &nf12);
			}
			ImGui::TreePop();
		}


	}

	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::BeginTabItem("Skills"))
		{
			MiscTab();
			ImGui::EndTabItem();
		}
	}
};
#endif