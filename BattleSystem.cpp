#include "BattleSystem.hpp"

BattleSystem::BattleSystem(std::vector<Entity*> teamMembers, std::vector<Entity*> enemies, Ui* ui)
{
	m_TeamMembers = teamMembers;
	m_Enemies = enemies;
	m_Ui = ui;

	// The max actions we can have is one action per team member.
	m_Actions.reserve(teamMembers.size());
}

BattleState BattleSystem::GetBattleState() const {
	return m_BattleState;
}

void BattleSystem::Update() {
	switch (m_BattleState)
	{
	case SELECTING_ACTIONS:

		break;
	case PLAYER_TURN:
		break;
	case ENEMY_TURN:
		break;
	default:
		break;
	}
}