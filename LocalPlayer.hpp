#pragma once
#ifndef LOCALPLAYER
#define LOCALPLAYER
class LocalPlayer : public pComponent
{
public:
	bool bEnabled = true;
	bool bInited = false;
	bool light = false;
	int outlook;

	LocalPlayer() { strcpy(classname, "LocalPlayer");  strcpy(version, "0.1.0"); };
	~LocalPlayer() {};
	Game GameContext;
	char buf[100];
	void onStart(Game game)
	{
		outlook = GamePtr.GetLocalPlayer()->getOutfit().LookType;
		bInited = true;
	}
	bool teste = false;

	int32_t areaTeste[13][13] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0},
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

		//if (GamePtr.GetLocalPlayer()->getOutfit().LookType != outlook) {
			//GamePtr.GetLocalPlayer()->setLookType(outlook);
		//}

		if (light) {
			GamePtr.GetLocalPlayer()->SetLight(20);
		}
		else {
			GamePtr.GetLocalPlayer()->SetLight(0);
		}

		GameContext = game;
	}

	void RenderCreatureList()
	{
		ImGui::Columns(6, "mycolumns");
		ImGui::Separator();
		ImGui::Text("Name / World"); ImGui::NextColumn();
		ImGui::Text("Level"); ImGui::NextColumn();
		ImGui::Text("Health"); ImGui::NextColumn();
		ImGui::Text("Outfit"); ImGui::NextColumn();
		ImGui::Text("FullLight"); ImGui::NextColumn();
		ImGui::Text("Position"); ImGui::NextColumn();
		ImGui::Separator();
		//GamePtr.GetLocalPlayer()->GetName()

		ImGui::Text("censuradoXD (%s)", GamePtr.GetWorldName()); ImGui::NextColumn();
		ImGui::Text("%i", GamePtr.GetLocalPlayer()->getLevel()); ImGui::NextColumn();
		ImGui::Text("%i / %i", GamePtr.GetLocalPlayer()->getHealth(), GamePtr.GetLocalPlayer()->getMaxHealth()); ImGui::NextColumn();
		//ImGui::Text("%i / %i", GamePtr.GetLocalPlayer()->getMana(), GamePtr.GetLocalPlayer()->getMaxMana()); ImGui::NextColumn();

		static int i0 = 123;
		if (GamePtr.GetLocalPlayer()->getOutfit().LookType != i0) {
			i0 = GamePtr.GetLocalPlayer()->getOutfit().LookType;
		}
		ImGui::InputInt("Id", &i0);
		if (GamePtr.GetLocalPlayer()->getOutfit().LookType != i0) {
			GamePtr.GetLocalPlayer()->setLookType(i0);
		}
		//ImGui::InputInt("", &outlook);

		ImGui::NextColumn();

		ImGui::Checkbox("On/Off", &light);

		ImGui::NextColumn();

		ImGui::Text("x: %i, y: %i z: %i", GamePtr.GetLocalPlayer()->GetPosition().x, GamePtr.GetLocalPlayer()->GetPosition().y, GamePtr.GetLocalPlayer()->GetPosition().z); ImGui::NextColumn();

		ImGui::Columns(1);

		if (mySummon != nullptr) {
			ImGui::Separator();
			ImGui::Columns(4, "pokeColum");
			ImGui::Separator();
			ImGui::Text("Pokemon"); ImGui::NextColumn();
			ImGui::Text("Health"); ImGui::NextColumn();
			ImGui::Text("Outfit"); ImGui::NextColumn();
			ImGui::Text("Position"); ImGui::NextColumn();
			ImGui::Separator();
			ImGui::Text("%s", mySummon->GetName()); ImGui::NextColumn();
			ImGui::Text("%i / %i", GamePtr.GetLocalPlayer()->getMana(), GamePtr.GetLocalPlayer()->getMaxMana()); ImGui::NextColumn();
			ImGui::Text("%i", mySummon->getOutfit().LookType); ImGui::NextColumn();
			ImGui::Text("x: %i, y: %i z: %i", mySummon->GetPosition().x, mySummon->GetPosition().y, mySummon->GetPosition().z); ImGui::NextColumn();
			ImGui::Columns(1);
		}
	}

	void MiscTab()
	{

		ImGui::Separator();

		RenderCreatureList();

		ImGui::Separator();

	}

	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::BeginTabItem("Jodador"))
		{
			MiscTab();
			ImGui::EndTabItem();
		}
	}
};
#endif