#include "BattleSystem.hpp"
#include <raymath.h>
#include <vector>
#include <map>

BattleSystem::BattleSystem(Ui* ui)
{
	m_Ui = ui;
	m_LowerHealthLerp = static_cast<float>(INT_MAX);
	m_ProcessingMove = false;
}

void BattleSystem::Update() {
	Entity* target = m_Ui->GetSelectedTarget();
	Entity* attacking = m_Ui->GetSelectedEntity();

	if (m_ProcessingMove) {
		if (target->GetHealthPoints() != m_LowerHealthLerp) {
			target->SetHealth(floorf(Lerp(target->GetHealthPoints(), m_LowerHealthLerp, 0.1f)));
		}
		else {
			m_Ui->ResetUiState();
			
			attacking->SetAttackedThisTurn(true);

			m_ProcessingMove = false;
			m_LowerHealthLerp = static_cast<float>(INT_MAX);
		}
	} else if (attacking != NULL && target != NULL && !m_ProcessingMove) {
		const Move* move = m_Ui->GetSelectedMove();

		m_LowerHealthLerp = target->GetHealthPoints() - move->GetDamage();

		m_ProcessingMove = true;
	}
}