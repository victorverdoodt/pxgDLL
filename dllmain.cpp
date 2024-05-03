// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "dllmain.h"
#include "MatrixArea.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <thread>
#include <future>
#include "Menu.h"
#include "ComponentBase.hpp"
#include "Cavebot.hpp"
#include "LocalPlayer.hpp"
#include "automove.h"
#include "PokeInfo.h"
#include "UseSkill.hpp"
#include "UseItem.hpp"
#include "Anti Leak.h"
std::vector<DWORD>pComponents;
CFunctions Functions;

void PopulateBattleList() {
	auto count = ReadMemory<int>((baseAddr + battleList) + Count);
	CreatureCache.clear();
	//std::cout << "Creatures Found:" << count << "\n";
	if (count > 0) {
		auto bufferPointer = ReadMemory<DWORD>((baseAddr + battleList) + BufferPointer);
		auto currentNodeAddress = bufferPointer + NodePointer;

		int i = 1;
		bool stop = false;
		bool findsummon = false;
		while (!stop) {
			auto nodePointer = ReadMemory<DWORD>(currentNodeAddress);
			if (nodePointer) {
				auto creaturePointer = ReadMemory <CreaturePtr*>(nodePointer + Value);
				if (creaturePointer) {
					if (creaturePointer->isDiff((CreaturePtr*)GamePtr.GetLocalPlayer())) {
						auto pos = creaturePointer->GetPosition();
						if (creaturePointer->isValid()) {
							CreatureCache.push_back(creaturePointer);
							if (creaturePointer->isSummon()) {
								//std::cout << "Summon? :" << creaturePointer->GetName() << "\n";
								findsummon = true;
								mySummon = creaturePointer;
							}
							std::cout << "Pointer: " << creaturePointer << ", Health: " << creaturePointer->getHealthPercent() << ", Name:" << creaturePointer->GetName() << ", Pos:" << creaturePointer->GetPosition() << "\n";
						}
					}
				}
			}

			i++;
			if (i <= count) {
				currentNodeAddress = nodePointer + NextPointer;
			}
			else {
				if (!findsummon) {
					mySummon = nullptr;
				}
				stop = true;
			}
		}

	}
}
bool started = false;
void MainLoop() {

	if (!started) {
		GamePtr = ReadMemory<Game>(baseAddr + gGame);
		LocalPlayer* lp = new LocalPlayer();
		lp->Add();
		Cavebot* cavebot = new Cavebot();
		cavebot->Add();
		AutoMove* automove = new AutoMove();
		automove->Add();
		UseSkill* useskill = new UseSkill();
		useskill->Add();
		UseItem* itemUse = new UseItem();
		itemUse->Add();

		pComponent::ComponentEvents_onStart(GamePtr);
		started = true;
	}


	if (GetAsyncKeyState(VK_F1))
	{
		//useItem(GamePtr, GamePtr.GetLocalPlayer()->getSlotItem(6));
		//Position pos = Position(0xFFFF, 0, 0); // means that is a item in inventory
		//talk(GamePtr, " AS ASJAJSIAJIJS A");
		//Functions.sendUseOnCreature(GamePtr.GetGameProtocol(), pos, 52710, 0, mySummon->GetId());
		//dword_7BCB60

		useOnCreature(GamePtr, 3161, mySummon);
	}

	if (GetAsyncKeyState(VK_F2))
	{
		//useSlotItem(GamePtr, 7);
		//useItem(GamePtr, GamePtr.GetLocalPlayer()->getSlotItem(7));

		//Position pos = Position(0xFFFF, 0, 0); // means that is a item in inventory
		//auto testeee = Functions.findItemTypeByClientId((DWORD*)0x7BCB60, 3666);
		//std::cout << testeee[0] << "\n";
		//Functions.sendUseOnCreature(GamePtr.GetGameProtocol(), pos, 52710, 0, mySummon->GetId());
	}

	if (GetAsyncKeyState(VK_F3))
	{
		//useItem(GamePtr, GamePtr.GetLocalPlayer()->getSlotItem(8));
		//useSlotItem(GamePtr, 8);
		//Position pos = Position(0xFFFF, 0, 0); // means that is a item in inventory

		//Functions.sendUseOnCreature(GamePtr.GetGameProtocol(), pos, 52710, 0, mySummon->GetId());
	}


	if (GamePtr.isOnline() && !GamePtr.isDead()) {
		std::cout << "LocalPlayerPointer:" << GamePtr.GetLocalPlayer() << ", Name:" << GamePtr.GetLocalPlayer()->GetName() << ", game: " << "\n";
		PopulateBattleList();
	}
	pComponent::ComponentsEvent_onUpdate(GamePtr);
}

typedef HRESULT(WINAPI *oEndScene)(LPDIRECT3DDEVICE9);
oEndScene Original_EndScene;
HRESULT WINAPI Hooked_EndScene(LPDIRECT3DDEVICE9 Device) {
	MainLoop();
	HWND hwnd = FindWindow(NULL, "PXG Client");
	ImGuiEx(hwnd, Device);
	return Original_EndScene(Device);
}

DWORD_PTR* FindDevice(DWORD Base, DWORD Len)
{
	unsigned long i = 0, n = 0;

	for (i = 0; i < Len; i++)
	{
		if (*(BYTE *)(Base + i + 0x00) == 0xC7)n++;
		if (*(BYTE *)(Base + i + 0x01) == 0x06)n++;
		if (*(BYTE *)(Base + i + 0x06) == 0x89)n++;
		if (*(BYTE *)(Base + i + 0x07) == 0x86)n++;
		if (*(BYTE *)(Base + i + 0x0C) == 0x89)n++;
		if (*(BYTE *)(Base + i + 0x0D) == 0x86)n++;

		if (n == 6)
			return (DWORD_PTR*)(Base + i + 2); n = 0;
	}
	return(0);
}

int D3Dinit(void)
{
	
	HMODULE hD3D = NULL;


	do
	{
		hD3D = GetModuleHandleA("d3d9.dll");
		Sleep(10);
	} while (!hD3D);


	DWORD_PTR * VTablePtr = FindDevice((DWORD)hD3D, 0x128000);


	if (VTablePtr == NULL)
	{
		MessageBox(NULL, "D3DDevice Pointer Not Found!", 0, MB_ICONSTOP);
		ExitProcess(0);
	}

	DWORD_PTR * VTable = 0;
	*(DWORD_PTR *)&VTable = *(DWORD_PTR *)VTablePtr;
	Original_EndScene = (oEndScene)DetourFunction((PBYTE)VTable[42], (PBYTE)Hooked_EndScene);

	return 0;
}

typedef void(__thiscall* _cancelAttack)(void*, DWORD*);
_cancelAttack cancelAttack;

void __fastcall hk_cancelAttack(void* ecx, void* edx, DWORD* inputMessage)
{
	console.AddLog("AttackFail!");
	ExcludeCreatureCache.push_back(_lastTarget);
	_lastTarget = nullptr;
	WriteMemory<CreaturePtr*>(baseAddr + gGame + 0x4, nullptr);
	return cancelAttack(ecx, inputMessage);
}

typedef void(__thiscall* _onUseItem)(void*, const Position&, int, int, int);
_onUseItem onUseItem;

void __fastcall hk_onUseItem(void* ecx, void* edx, const Position& position, int itemId, int stackpos, int index)
{
	cout << position << "|" << itemId << "|" << stackpos << "|" << index << "\n";
	if (selectedLootPos == position) {
		LootData teste;
		teste.pos = position;
		teste.time = clock();
		CacheLoot.push_back(teste);
		selectedLootPos = Position(65535, 65535, 255);
	}
	console.AddLog("UsedItem (X: %i, Y: %i, Z: %i), Id: %i, StackPos: %i, Index: %i", position.x, position.y, position.z, itemId, stackpos, index);

	return onUseItem(ecx, position, itemId, stackpos, index);
}

typedef void(__thiscall* _onUseItemWith)(void*, const Position&, int, int, const Position&, int, int);
_onUseItemWith onUseItemWith;

void __fastcall hk_onUseItemWith(void* ecx, void* edx, const Position& fromPos, int itemId, int fromStackPos, const Position& toPos, int toThingId, int toStackPos)
{
	cout << fromPos << "|" << itemId <<"|"<< toThingId <<  "|" << toStackPos << "\n";
	console.AddLog("UsedItemWith (X: %i, Y: %i, Z: %i), Id: %i, StackPos: %i", fromPos.x, fromPos.y, fromPos.z, itemId, fromStackPos);
	console.AddLog("UsedItemWith (X: %i, Y: %i, Z: %i), Id: %i, StackPos: %i", toPos.x, toPos.y, toPos.z, toThingId, toStackPos);
	return onUseItemWith(ecx, fromPos, itemId, fromStackPos, toPos, toThingId, toStackPos);
}

typedef void(__thiscall* _onTalk)(void*, int, int, const std::string&, const std::string&);
_onTalk onTalk;

void __fastcall hk_onTalk(void* ecx, void* edx, int mode, int channelId, const std::string& receiver, const std::string& message)
{
	//cout << position << "|" << itemId << "|" << stackpos << "|" << index << "\n";
	//cout << mode << "|" << channelId << "|"  << "|" << message << "\n";
	console.AddLog("Talk: Mode: %i, ChannelId: %i, Message: %s", mode, channelId, message);

	return onTalk(ecx, mode, channelId, receiver, message);
}


typedef void(__thiscall* _Attack)(void*,  DWORD*);
_Attack Attack;
void __fastcall hk_Attack(void* ecx, void* edx,  DWORD* a2)
{
	std::cout << "|" << a2 << "\n";
	return  Attack(ecx, a2);
}


void __stdcall Start() {
	Functions.sendAttack = (Typedefs::sendAttack)((DWORD)GetModuleHandle(NULL) + 0x13D4C0); //13ADA0
	Functions.Attack = (Typedefs::Attack)((DWORD)GetModuleHandle(NULL) + 0xE2540);
	Functions.ForceWalk = (Typedefs::ForceWalk)(baseAddr + 0xDEA20);
	Functions.sendWalkEast = (Typedefs::sendWalkEast)((DWORD)GetModuleHandle(NULL) + 0x138480);
	Functions.GetId = (Typedefs::GetId)((DWORD)GetModuleHandle(NULL) + 0x1FCB70);
	Functions.GetHealthPercent = (Typedefs::GetHealthP)((DWORD)GetModuleHandle(NULL) + 0x230F38);
	Functions.isMonter = (Typedefs::fnIsMonster)((DWORD)GetModuleHandle(NULL) + 0x230F38);
	Functions.autoWalk = (Typedefs::autoWalk)((DWORD)GetModuleHandle(NULL) + 0x138300);
	Functions.autoWalk2 = (Typedefs::autoWalk2)((DWORD)GetModuleHandle(NULL) + 0xEAE50);
	Functions.stopAutoWalk = (Typedefs::stopAutoWalk)((DWORD)GetModuleHandle(NULL) + 0xEA9F0);

	Functions.sendUseItem = (Typedefs::sendUseItem)((DWORD)GetModuleHandle(NULL) + 0x13D160);
	Functions.sendUseOnCreature = (Typedefs::sendUseOnCreature)((DWORD)GetModuleHandle(NULL) + 0x13D430);
	Functions.sendUseItemWith = (Typedefs::sendUseItemWith)((DWORD)GetModuleHandle(NULL) + 0x13D2B0);

	Functions.sendTalk = (Typedefs::sendTalk)((DWORD)GetModuleHandle(NULL) + 0x13A0D0);
	//EA9F0
	//Functions.ForceDisconnect = (Typedefs::ForceDisconnect)(baseAddr + 0xDF650);
	cancelAttack = (_cancelAttack)DetourFunction((PBYTE)((DWORD)GetModuleHandle(NULL) + 0x12DD00), (PBYTE)hk_cancelAttack); //12B6D0
	onUseItem = (_onUseItem)DetourFunction((PBYTE)((DWORD)GetModuleHandle(NULL) + 0x13F750), (PBYTE)hk_onUseItem); //13D160
	onUseItemWith = (_onUseItemWith)DetourFunction((PBYTE)((DWORD)GetModuleHandle(NULL) + 0x13F8A0), (PBYTE)hk_onUseItemWith); //13D2B0
	//getTop = (_getTop)DetourFunction((PBYTE)((DWORD)GetModuleHandle(NULL) + 0x1128B0), (PBYTE)hk_getTop);
	onTalk = (_onTalk)DetourFunction((PBYTE)((DWORD)GetModuleHandle(NULL) + 0x13C6C0), (PBYTE)hk_onTalk); //13A0D0
	//Attack = (_Attack)DetourFunction((PBYTE)((DWORD)GetModuleHandle(NULL) + 0xE2540), (PBYTE)hk_Attack);
	Functions.findPath = (Typedefs::findPath)((DWORD)GetModuleHandle(NULL) + 0xF0910);

	Functions.GetTile = (Typedefs::GetTile)((DWORD)GetModuleHandle(NULL) + 0xEED00);
	Functions.getItems = (Typedefs::getItems)((DWORD)GetModuleHandle(NULL) + 0x1150E0);
	Functions.getTopThing = (Typedefs::getTopThing)((DWORD)GetModuleHandle(NULL) + 0x1128B0);
	Functions.findItemTypeByClientId = (Typedefs::findItemTypeByClientId)((DWORD)GetModuleHandle(NULL) + 0x108380);

	Functions.isContainer = (Typedefs::isContainer)((DWORD)GetModuleHandle(NULL) + 0x1FD290);
	Functions.getStackPos = (Typedefs::getStackPos)((DWORD)GetModuleHandle(NULL) + 0x1076F0);
	// 1128B0 top ting?, get items 1150E0, FINDITEM 108380, stackpos 1076F0, iscontainer 1FD290 
	//EEDF0 gettiles?
	//Turn North 138F80, East 139080, South 138E80, West 138D80
	//13D160 useInv, 13D430 use Inv on creature, 13D2B0 use Inv on item, talk 13A0D0
	D3Dinit();
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);

		std::cout << "[+] Successfully attached to process.\n";

		//CreateThread(0, 0, MainThread, hModule, 0, 0);
		cAL teste = cAL();
		if (teste.Authenticated()) {
			std::cout << "Autenticado com sucesso!. \n";
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
		}
		else {
			std::cout << "Falha de Autenticação!";
		}
		return TRUE;
		// Alternatively just do easy things here if you dont need an own thread,
		// like patching out things etc...

		break;
	case DLL_THREAD_ATTACH:
		return TRUE;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}