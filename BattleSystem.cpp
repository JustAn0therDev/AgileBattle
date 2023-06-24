#include "BattleSystem.hpp"
#include <raymath.h>
#include <vector>
#include <map>

BattleSystem::BattleSystem(Ui* ui, std::vector<Entity*> enemies, std::vector<Entity*> teamMembers)
{
	m_Ui = ui;
	m_TeamMembers = teamMembers;
	m_Enemies = enemies;
	m_LastTime = GetTime();
}

void BattleSystem::Update() {
	Entity* target = m_Ui->GetSelectedTarget();
	Entity* attacking = m_Ui->GetSelectedEntity();

	if (attacking != NULL && target != NULL) {
		const Move* move = m_Ui->GetSelectedMove();

		float modifier = 1;

		if (move->GetMoveType() == target->GetWeakness()) {
			modifier *= 2;
		}

		target->RemoveHealth(move->GetDamage() * modifier);

		attacking->PlayAnimation(AnimationType::Attack);
		target->PlayAnimation(AnimationType::Damage);

		m_Ui->ResetUiState();

		attacking->SetAttackedThisTurn(true);

		m_LastTime = GetTime();
	}

	// checks if player won

	bool playerWins = true;

	for (const auto enemy : m_Enemies) {
		if (enemy->GetHealthPoints() > 0) {
			playerWins = false;
			break;
		}
	}

	if (playerWins) {
		exit(1); // close the gaem.
	}

	// checks if player lost

	bool playerLost = true;

	for (const auto teamMember : m_TeamMembers) {
		if (teamMember->GetHealthPoints() > 0) {
			playerLost = false;
			break;
		}
	}

	if (playerLost) {
		exit(1); // close the gaem.
	}

	bool enemyTurn = true;

	for (const auto teamMember : m_TeamMembers) {
		if (teamMember != NULL && !teamMember->HasAttackedThisTurn()) {
			enemyTurn = false;
		}
	}

	if (enemyTurn && GetTime() - m_LastTime > 1) {
		for (const auto enemy : m_Enemies) {
			if (enemy->GetHealthPoints() > 0) {
				size_t rndIndex =
					static_cast<size_t>(GetRandomValue(0, static_cast<int>(m_TeamMembers.size() - 1)));

				Entity* teamMemberTarget = m_TeamMembers[rndIndex];

				if (teamMemberTarget != NULL) {
					Move* enemyMove = enemy->GetMoves()[0];
					teamMemberTarget->RemoveHealth(enemyMove->GetDamage());
				
					m_Ui->ChangeUiState(ActiveUiState::SELECTING_TARGET);
					m_Ui->SetSelectedEntity(enemy);
					m_Ui->SetSelectedMove(enemyMove);
					m_Ui->SetSelectedTarget(teamMemberTarget);

					enemy->PlayAnimation(AnimationType::Attack);
					teamMemberTarget->PlayAnimation(AnimationType::Damage);

					m_Ui->ResetUiState();
				}
			}
		}

		enemyTurn = false;

		for (const auto teamMember : m_TeamMembers) {
			teamMember->SetAttackedThisTurn(false);
		}
	}
}