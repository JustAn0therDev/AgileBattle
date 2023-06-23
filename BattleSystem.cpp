#include "BattleSystem.hpp"
#include <raymath.h>
#include <vector>
#include <map>

BattleSystem::BattleSystem(Ui* ui, std::vector<Entity*> enemies, std::vector<Entity*> teamMembers)
{
	m_Ui = ui;
	m_TeamMembers = teamMembers;
	m_Enemies = enemies;
}

void BattleSystem::Update() {
	Entity* target = m_Ui->GetSelectedTarget();
	Entity* attacking = m_Ui->GetSelectedEntity();

	if (attacking != NULL && target != NULL) {
		const Move* move = m_Ui->GetSelectedMove();

		target->RemoveHealth(move->GetDamage());

		attacking->PlayAnimation(AnimationType::Attack);
		target->PlayAnimation(AnimationType::Damage);

		m_Ui->ResetUiState();

		attacking->SetAttackedThisTurn(true);
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

	if (enemyTurn) {
		size_t rndIndex = static_cast<size_t>(GetRandomValue(0, static_cast<int>(m_TeamMembers.size() - 1)));
		
		Entity* teamMemberTarget = m_TeamMembers[rndIndex];

		for (const auto enemy : m_Enemies) {
			if (teamMemberTarget != NULL) {
				teamMemberTarget->RemoveHealth(enemy->GetMoves()[0]->GetDamage());
			}
		}

		enemyTurn = false;

		for (const auto teamMember : m_TeamMembers) {
			teamMember->SetAttackedThisTurn(false);
		}
	}
}