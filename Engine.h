#pragma once
#include "stdafx.h"
#include "Console.h"

bool debug = true;
CreaturePtr* _lastTarget;
std::vector<CreaturePtr*> ExcludeCreatureCache;
int enemiesToStop = 1;
std::vector<Position> WayPoints;
char target[128] = "Dummy";
std::vector<CreaturePtr*> CreatureCache;
Position selectedLootPos;
class LootData
{
public:
	Position pos;
	DWORD time;
};

std::vector<LootData> CacheLoot;




std::vector<CreaturePtr*> getEnemiesRange(Game proto, CreaturePtr* cid, int range, bool filter = true) {

	std::vector<CreaturePtr*> list;
	auto creatures = CreatureCache;
	for (int i = 0; i < creatures.size(); i++) {
		CreaturePtr* pCreature = creatures[i];
		if (pCreature) {
			if (pCreature->isValid() && pCreature->isDiff((CreaturePtr*)proto.GetLocalPlayer())) {
				if (pCreature->GetPosition().distance(cid->GetPosition()) <= range) {
					if (filter && isPartOf(target, pCreature->GetName())) {
						list.push_back(pCreature);
					}
					else {
						list.push_back(pCreature);
					}

				}
			}
		}
	}
	return list;
}

bool doAttackCreature(Game proto, CreaturePtr * creature) {
	if (proto.GetAttackTarget() == (CreaturePtr*)proto.GetLocalPlayer())
		return false;

	if (creature && proto.GetAttackTarget())
		return false;

	auto it = std::find(ExcludeCreatureCache.begin(), ExcludeCreatureCache.end(), creature);
	if (it != ExcludeCreatureCache.end())
	{
		return false;
	}

	WriteMemory<CreaturePtr*>(baseAddr + gGame + 0x4, creature);
	Functions.sendAttack(proto.GetGameProtocol(), creature->GetId(), 0);
	if (getEnemiesRange(proto, (CreaturePtr*)proto.GetLocalPlayer(), 5).size() >= enemiesToStop) {
		Functions.stopAutoWalk((DWORD*)proto.GetLocalPlayer());
	}
	//Functions.Attack((DWORD*)proto.GetLocalPlayer(), (DWORD*)creature);
	_lastTarget = creature;
	if (debug) {
		//addLog("Attacking: %s \n", s);
		//console.AddLog("Attacking: %s \n", creature->GetName());
		//std::cout << "Attacking: " << creature->GetName() << "\n";
	}
	return true;
}

void SendKeyStroke(WPARAM key)
{

	//PostMessage(FindWindow(NULL, "pxgclient_dx9"), WM_KEYDOWN, key, MapVirtualKey(key, MAPVK_VK_TO_VSC));
	//PostMessage(FindWindow(NULL, "pxgclient_dx9"), WM_KEYUP, key, MapVirtualKey(key, MAPVK_VK_TO_VSC));
	// "e" key press
	keybd_event(key, 0x9C, 0, 0);
	// "e" key release
	keybd_event(key, 0x9C, KEYEVENTF_KEYUP, 0);
}

bool isContainer(int thing) {
	return Functions.isContainer(thing);
}

int getStackPos(int thing) {
	return Functions.getStackPos(thing);
}


void useInventoryItem(Game proto, int itemId) {
	Position pos = Position(0xFFFF, 0, 0); // means that is a item in inventory
	Functions.sendUseItem(proto.GetGameProtocol(), pos, itemId, 0, 0);
}

void useItem(Game proto, ItemPtr* item)
{
	Functions.sendUseItem(proto.GetGameProtocol(), item->getPosition(), item->getServerId(), item->getPosition().z, 1);
}

void use(Game proto, int thing)
{
	ItemPtr item = ReadMemory<ItemPtr>(thing);
	Position pos = item.getPosition();
	if (!pos.isValid()) // virtual item
		pos = Position(0xFFFF, 0, 0); // inventory item
	
	console.AddLog("Try use");
	// m_protocolGame->sendUseItem(pos, thing->getId(), thing->getStackPos(), findEmptyContainerId());
	Functions.sendUseItem(proto.GetGameProtocol(), item.getPosition(), item.getServerId(), getStackPos(thing), 1);
}

void useOnCreature(Game proto, int itemId, CreaturePtr * creature)
{
	if (!creature)
		return;


	Position pos = Position(0xFFFF, 0, 0); // means that is a item in inventory

	if (creature)
		// m_protocolGame->sendUseOnCreature(pos, item->getId(), item->getStackPos(), toThing->getId());
		Functions.sendUseOnCreature(proto.GetGameProtocol(), pos, itemId, 0, creature->GetId());

	//m_protocolGame->sendUseOnCreature(pos, itemId, 0, toThing->getId());
	//Functions.sendUseItem(proto.GetGameProtocol(), item->getPosition(), item->getServerId(), item->getPosition().z, 1);
}

int GetTile(Position toPos) {
	return Functions.GetTile((DWORD*)0x7BC560, toPos);
}

int getTopThing(Position toPos) {
	int item = 0;
	auto Tile = GetTile(toPos);
	auto a3 = ReadMemory<int>(Tile);
	auto v4 = *(unsigned __int8 *)(a3 + 22);
	if ((BYTE)v4) {
		auto v6 = *(int **)(a3 + 23);
		auto  v7 = (int)&v6[v4];


		auto v16 = *(DWORD *)(*(DWORD *)(a3 + 23) + 4 * (unsigned __int8)(*(BYTE *)(a3 + 22) - 1));
		return v16;
	}

	return item;
}

ItemPtr getTopItem(Position toPos) {
	auto TopThing = getTopThing(toPos);
	ItemPtr item;
	if (TopThing > 0) {
		item = ReadMemory<ItemPtr>(TopThing);
	}
	return item;
}

void useOnItem(Game proto, int itemId, ItemPtr toItem) {


	Position pos = Position(0xFFFF, 0, 0); // means that is a item in inventory
		
	Functions.sendUseItemWith(proto.GetGameProtocol(), pos, itemId, 0, toItem.getPosition(), toItem.getServerId(), getStackPos(getTopThing(toItem.getPosition())));
	//m_protocolGame->sendUseItemWith(pos, itemId, 0, toThing->getPosition(), toThing->getId(), toThing->getStackPos());
	//m_protocolGame->sendUseItemWith(pos, item->getId(), item->getStackPos(), toThing->getPosition(), toThing->getId(), toThing->getStackPos());

}


void talkChannel(Game proto, Otc::MessageMode mode, int channelId, const char* message)
{
	Functions.sendTalk(proto.GetGameProtocol(), mode, channelId, "", message);
}

void talk(Game proto, const char* message) {
	talkChannel(proto, Otc::MessageSay, 0, message);
}

// m_protocolGame->sendUseItem(pos, thing->getId(), thing->getStackPos(), findEmptyContainerId());

void useSlotItem(Game proto, int slot) {
	auto slotItem = proto.GetLocalPlayer()->getSlotItem(slot);
	if (slotItem) {
		useInventoryItem(proto, slotItem->getSlotItem());
	}
}

void doWalkToPosition(Game proto, Position toPos) {
	if (!proto.GetLocalPlayer()->isWalking()) {
		Functions.autoWalk2((DWORD*)proto.GetLocalPlayer(), toPos);
		if (debug) {
			console.AddLog("Walk to : ( x: %i, y: %i, z: %i) \n", toPos.x, toPos.y, toPos.z);
		}
	}
}


std::vector<Position> getPosfromArea(CreaturePtr* cid, int area[13][13]) {

	int icenter = floor(12 / 2);
	int jcenter = floor(12 / 2);
	
	auto center = area[icenter];

	int ivar = 12;
	int jvar = 12;

	int i = pow(12, 2);
	int j = pow(12, 2);

	auto mydir = cid->GetLookDirection();
	int signal[4];
	signal[0] = -1;
	signal[1] = 1;
	signal[2] = 0;
	signal[3] = 1;
	if (center[jcenter] == 3) {
		if (mydir == 0) {
			signal[0] = -1;
			signal[1] = 1;
			signal[2] = 0;
			signal[3] = 1;
		}
		else if(mydir == 1){
			signal[0] = 1;
			signal[1] = -1;
			signal[2] = 1;
			signal[3] = 0;
		}
		else if (mydir == 2) {
			signal[0] = 1;
			signal[1] = -1;
			signal[2] = 0;
			signal[3] = 1;
		}
		else if (mydir == 3) {
			signal[0] = -1;
			signal[1] = 1;
			signal[2] = 1;
			signal[3] = 0;
		}
	}

	std::vector<Position> PosList;
	while (i >= 0 && j >= 0){
		int pvar[2];
		pvar[0] = 0;
		pvar[1] = 0;
		auto I = area[ivar];
		auto J = I[jvar];
		if (J == 1) {
			if (jvar < jcenter) {
				pvar[signal[2]] = signal[0]*abs((jcenter - jvar));
			}
			else if(jvar > jcenter){
				pvar[signal[2]] = signal[1]*abs((jcenter - jvar));
			}

			if (ivar < icenter) {
				pvar[signal[3]] = signal[0]*abs((icenter - ivar));
			}
			else if (ivar > icenter) {
				pvar[signal[3]] = signal[1]*abs((icenter - ivar));
			}
		}

		if (jvar > 1) {
			jvar = (jvar - 1);
		}
		else if (ivar > 1) {
			jvar = 12;
			ivar = (ivar - 1);
		}

		Position pos = cid->GetPosition();
		Position areapos = Position(pos.x + (pvar[0]), pos.y + (pvar[1]), pos.z);
		if (pos.x != areapos.x || pos.y != areapos.y) {
			PosList.push_back(areapos);
		}

		i = i - 1;
		j = j - 1;
	}

	return PosList;
}

std::vector<Position> getPosfromArea2(LocalPLayerPtr* cid, int area[13][13]) {

	int icenter = floor(12 / 2);
	int jcenter = floor(12 / 2);

	auto center = area[icenter];

	int ivar = 12;
	int jvar = 12;

	int i = pow(12, 2);
	int j = pow(12, 2);

	auto mydir = cid->GetLookDirection();
	int signal[4];
	signal[0] = -1;
	signal[1] = 1;
	signal[2] = 0;
	signal[3] = 1;
	if (center[jcenter] == 3) {
		if (mydir == 0) {
			signal[0] = -1;
			signal[1] = 1;
			signal[2] = 0;
			signal[3] = 1;
		}
		else if (mydir == 1) {
			signal[0] = 1;
			signal[1] = -1;
			signal[2] = 1;
			signal[3] = 0;
		}
		else if (mydir == 2) {
			signal[0] = 1;
			signal[1] = -1;
			signal[2] = 0;
			signal[3] = 1;
		}
		else if (mydir == 3) {
			signal[0] = -1;
			signal[1] = 1;
			signal[2] = 1;
			signal[3] = 0;
		}
	}

	std::vector<Position> PosList;
	while (i >= 0 && j >= 0) {
		int pvar[2];
		pvar[0] = 0;
		pvar[1] = 0;
		auto I = area[ivar];
		auto J = I[jvar];
		if (J == 1) {
			if (jvar < jcenter) {
				pvar[signal[2]] = signal[0] * abs((jcenter - jvar));
			}
			else if (jvar > jcenter) {
				pvar[signal[2]] = signal[1] * abs((jcenter - jvar));
			}

			if (ivar < icenter) {
				pvar[signal[3]] = signal[0] * abs((icenter - ivar));
			}
			else if (ivar > icenter) {
				pvar[signal[3]] = signal[1] * abs((icenter - ivar));
			}
		}

		if (jvar > 1) {
			jvar = (jvar - 1);
		}
		else if (ivar > 1) {
			jvar = 12;
			ivar = (ivar - 1);
		}

		Position pos = cid->GetPosition();
		Position areapos = Position(pos.x + (pvar[0]), pos.y + (pvar[1]), pos.z);
		if (pos.x != areapos.x || pos.y != areapos.y) {
			PosList.push_back(areapos);
		}

		i = i - 1;
		j = j - 1;
	}

	return PosList;
}


int* getItems(Position toPos) {
	auto Tile = GetTile(toPos);
	return Functions.getItems(ReadMemory<DWORD*>(Tile), ReadMemory<int>(Tile));
}
//4029 ratta
void useTopItem(Game proto, Position toPos) {
	auto TopItem = getTopThing(toPos);
	use(proto, TopItem);
}

std::vector<ItemPtr> getContainers(Game proto) {
	int32_t Area1[13][13] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	auto PosList = getPosfromArea2(proto.GetLocalPlayer(), Area1);
	std::vector<ItemPtr> tiles;
	for (auto &i : PosList) {
		auto TopThing = getTopThing(i);

		if (TopThing > 0) {
			if (isContainer(TopThing)) {
				console.AddLog("Loot found");
				ItemPtr item = ReadMemory<ItemPtr>(TopThing);
				tiles.push_back(item);
			}
		}
	}

	return tiles;
}

template <class Container>
const bool contains(Container container, typename Container::value_type element)
{
	return std::find(container.begin(), container.end(), element) != container.end();
}

std::vector<ItemPtr> haveLootToGet(Game proto) {
	std::vector<ItemPtr> tile;
	auto teste = getContainers(proto);
	for (auto i : teste) {
		bool found = false;
		for (auto e : CacheLoot) {
			if (e.pos == i.getPosition()) {
				found = true;
			}
		}

		if (!found) {
			tile.push_back(i);
		}

	}
	return tile;
}

ItemPtr getClosestLoot(Game proto) {
	int Dist = 1000;
	auto teste = haveLootToGet(proto);
	ItemPtr Selected;
	for (auto &i : teste) {
		auto newDist = i.getPosition().distance(proto.GetLocalPlayer()->GetPosition());
		if (newDist < Dist) {
			Dist = newDist;
			Selected = i;
		}
		//use(GamePtr, getTopThing(i.getPosition()));
	}
	return Selected;
}


