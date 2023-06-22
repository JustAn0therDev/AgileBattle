#pragma once
#include "BattleState.hpp"
#include "Ui.hpp"
#include "Entity.hpp"
#include <vector>
#include "Action.hpp"

class BattleSystem {
private:
	Ui* m_Ui;
	float m_LowerHealthLerp;
	bool m_ProcessingMove;
public:
	BattleSystem(
		Ui* ui
	);

	void Update();
};