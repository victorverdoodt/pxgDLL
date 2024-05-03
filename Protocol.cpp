#include "stdafx.h"
#include "Protocol.h"
#include "Hooks.h"

bool ProtocolGamePtr::doAttackCreature(int creature) {
	Functions.sendAttack(this, creature, 0);
}