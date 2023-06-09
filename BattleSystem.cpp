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
	m_PlayerLost = false;
	m_PlayerWon = false;

	m_DamageSound = LoadSound("Assets\\Audio\\Sound Effects\\Damage Sound Effect.wav");
	m_BiggerDamageSound = LoadSound("Assets\\Audio\\Sound Effects\\Impact Sound Effect.wav");

	SetSoundVolume(m_DamageSound, Constants::SOUND_VOLUME);
	SetSoundVolume(m_BiggerDamageSound, Constants::SOUND_VOLUME);
}

BattleSystem::~BattleSystem()
{
	UnloadSound(m_DamageSound);
	UnloadSound(m_BiggerDamageSound);
}

void BattleSystem::Update() {
	Entity* attacking = m_Ui->GetSelectedEntity();
	Entity* target = m_Ui->GetSelectedTarget();

	if (attacking != NULL &&
		target != NULL &&
		GetTime() - m_LastTime > 1 &&
		m_Ui->GetLockContext() == LockContext::NoLocks) {
		const Move* move = m_Ui->GetSelectedMove();

		float modifier = 1;

		if (move->GetMoveType() == target->GetWeakness()) {
			modifier = Constants::DAMAGE_MODIFIER; // weakness takes damage * modifier
			PlaySound(m_BiggerDamageSound);
		}
		else {
			PlaySound(m_DamageSound);
		}

		target->RemoveHealth(move->GetDamage() * modifier);

		attacking->PlayAnimation(AnimationType::Attack);
		target->PlayAnimation(AnimationType::Damage);

		m_Ui->Lock(LockContext::PlayerAttack);

		m_LastTime = GetTime();
	}

	// checks if player won

	m_PlayerWon = true;

	for (const auto enemy : m_Enemies) {
		if (enemy->GetHealthPoints() > 0) {
			m_PlayerWon = false;
			break;
		}
	}

	if (m_PlayerWon) {
		m_Ui->SetPlayerWon();
	}

	// checks if player lost

	m_PlayerLost = true;

	for (const auto teamMember : m_TeamMembers) {
		if (teamMember->GetHealthPoints() > 0) {
			m_PlayerLost = false;
			break;
		}
	}

	if (m_PlayerLost) {
		m_Ui->SetPlayerLost();
	}

	if (GetTime() - m_LastTime > 1 &&
		target != NULL &&
		m_Ui->GetLockContext() == LockContext::PlayerAttack) {
		// Process enemy attacks
		if (target->GetHealthPoints() > 0) {
			Entity* teamMemberTarget = NULL;

			// TODO: refactor
			while (teamMemberTarget == NULL) {
				size_t rndIndex =
					static_cast<size_t>(GetRandomValue(0, static_cast<int>(m_TeamMembers.size() - 1)));

				if (m_TeamMembers[rndIndex]->GetHealthPoints() > 0) {
					teamMemberTarget = m_TeamMembers[rndIndex];
				}
			}

			if (teamMemberTarget != NULL) {
				Move* enemyMove = target->GetMoves()[0];
				teamMemberTarget->RemoveHealth(enemyMove->GetDamage());
					
				// Change the UI State in such a way that it simulates a player event.
				m_Ui->ReleaseLock();
				m_Ui->ResetUiState();
				m_Ui->ChangeUiState(ActiveUiState::MOVE);
				m_Ui->SetSelectedEntity(target);
				m_Ui->SetSelectedMove(enemyMove);
				m_Ui->SetSelectedTarget(teamMemberTarget);
				m_Ui->SetupDrawDamageAnimation();

				target->PlayAnimation(AnimationType::Attack);
				teamMemberTarget->PlayAnimation(AnimationType::Damage);

				PlaySound(m_DamageSound);

				m_Ui->Lock(LockContext::EnemyAttack);

				m_LastTime = GetTime();
			}
		}
	}

	if (GetTime() - m_LastTime > 1 && (m_Ui->GetLockContext() == LockContext::EnemyAttack || m_Ui->GetLockContext() == LockContext::PlayerAttack)) {
		m_Ui->ReleaseLock();
		m_Ui->ResetUiState();
	}
}

bool BattleSystem::GetPlayerWon() const
{
	return m_PlayerWon;
}

bool BattleSystem::GetPlayerLost() const
{
	return m_PlayerLost;
}
