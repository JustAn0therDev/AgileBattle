#include "BattleSystem.hpp"
#include "Constants.hpp"
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
	Entity* attacking = m_Ui->GetSelectedEntity();
	Entity* target = m_Ui->GetSelectedTarget();

	if (attacking != NULL && target != NULL && GetTime() - m_LastTime > 1 && !m_Ui->IsLocked()) {
		const Move* move = m_Ui->GetSelectedMove();

		float modifier = 1;

		if (move->GetMoveType() == target->GetWeakness()) {
			modifier *= Constants::DAMAGE_MODIFIER; // weakness takes damage * modifier
		}

		target->RemoveHealth(move->GetDamage() * modifier);

		attacking->PlayAnimation(AnimationType::Attack);
		target->PlayAnimation(AnimationType::Damage);

		m_Ui->Lock();

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
		m_Ui->SetPlayerWon();
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
		m_Ui->SetPlayerLost();
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
					
					// Change the UI State in such a way that it simulates a player event.
					m_Ui->ReleaseLock();
					m_Ui->ResetUiState();
					m_Ui->ChangeUiState(ActiveUiState::MOVE);
					m_Ui->SetSelectedEntity(enemy);
					m_Ui->SetSelectedMove(enemyMove);
					m_Ui->SetSelectedTarget(teamMemberTarget);
					m_Ui->SetupDrawDamageAnimation();

					enemy->PlayAnimation(AnimationType::Attack);
					teamMemberTarget->PlayAnimation(AnimationType::Damage);

					m_Ui->Lock();

					m_LastTime = GetTime();
				}
			}
		}

		enemyTurn = false;

		for (const auto teamMember : m_TeamMembers) {
			teamMember->SetAttackedThisTurn(false);
		}
	}

	if (GetTime() - m_LastTime > 1 && m_Ui->IsLocked()) {
		m_Ui->ReleaseLock();
		m_Ui->ResetUiState();
	}
}