#include "stdafx.h"
#include <Game/Settings/GameConfig.h>

void CGameConfig::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "lives", _lives);
	SERIALIZE(node, "towerStartZPos", _towerStartZPos);
	SERIALIZE(node, "TowerBlockDescriptor", _towerBlockDescriptor);
}
