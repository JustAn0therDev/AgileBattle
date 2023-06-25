#pragma once
#include "BattleState.hpp"
#include "Ui.hpp"
#include "Entity.hpp"
#include <map>
#include "Action.hpp"
#include <vector>

class BattleSystem {
private:
	Ui* m_Ui;
	std::vector<Entity*> m_TeamMembers;
	std::vector<Entity*> m_Enemies;
	double m_LastTime;
	bool m_EnemyAttacking;
	Entity* m_Attacking;
	Entity* m_Target;
	const Move* m_SelectedMove;
public:
	BattleSystem(Ui* ui, std::vector<Entity*> enemies, std::vector<Entity*> teamMembers);

	void Update();
};