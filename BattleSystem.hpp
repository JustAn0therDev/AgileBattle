#pragma once
#include "BattleState.hpp"
#include "Ui.hpp"
#include "Entity.hpp"
#include <vector>
#include "Action.hpp"

class BattleSystem {
private:
	BattleState m_BattleState;
	Ui* m_Ui;
	std::vector<Entity*> m_TeamMembers;
	std::vector<Entity*> m_Enemies;
	std::vector<Action*> m_Actions;
public:
	BattleSystem(
		std::vector<Entity*> teamMembers,
		std::vector<Entity*> enemies,
		Ui* ui
	);

	BattleState GetBattleState() const;
	void Update();
};