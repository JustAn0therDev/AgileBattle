#include "Entity.hpp"
#include <iostream>
#include <raymath.h>
#include "Constants.hpp"

Entity::Entity(
	const char* name,
	EntityType entityType,
	float healthPoints,
	Vector2 position,
	Animation* idleAnimation,
	Animation* deathAnimation,
	Animation* attackAnimation,
	Animation* damageAnimation,
	MoveType weakness) {
	m_Name = name;
	m_EntityType = entityType;
	m_HealthPoints = healthPoints;
	m_Position = position;
	m_IdleAnimation = idleAnimation;
	m_DeathAnimation = deathAnimation;
	m_AttackAnimation = attackAnimation;
	m_DamageAnimation = damageAnimation;
	m_Movements.reserve(Constants::MAX_MOVEMENTS);
	m_Weakness = weakness;

	// The current animation is always "idle", unless another
	// system actively changes it.
	m_CurrentAnimation = m_IdleAnimation;
}

Entity::~Entity() {
	// Freeing all the animations
	if (m_IdleAnimation != NULL) {
		delete m_IdleAnimation;
	}

	if (m_DeathAnimation != NULL) {
		delete m_DeathAnimation;
	}

	if (m_AttackAnimation != NULL) {
		delete m_AttackAnimation;
	}

	if (m_DamageAnimation != NULL) {
		delete m_DamageAnimation;
	}

	// Freeing the movements
	for (const Move* move : m_Movements) {
		delete move;
	}
}

float Entity::GetHealthPoints() const {
	return m_HealthPoints;
}

const char* Entity::GetName() const {
	return m_Name;
}

Vector2 Entity::GetPosition() const {
	return m_Position;
}

const EntityType& Entity::GetEntityType() const {
	return m_EntityType;
}

void Entity::PlayAnimation(AnimationType animationType) {
	// The animation that is currently playing should have its
	// state reset so that, when played again,
	// it should always start at the first frame.
	m_CurrentAnimation->ResetState();

	switch (animationType)
	{
	case Idle:
		m_CurrentAnimation = m_IdleAnimation;
		break;
	case Attack:
		m_CurrentAnimation = m_AttackAnimation;
		break;
	case Damage:
		m_CurrentAnimation = m_DamageAnimation;
		break;
	case Death:
		m_CurrentAnimation = m_DeathAnimation;
		break;
	}
}

const Animation* Entity::GetCurrentAnimation() const {
	return m_CurrentAnimation;
}

void Entity::Update() {
	if (m_CurrentAnimation != NULL) {
		if (m_CurrentAnimation->GetAnimationType() != AnimationType::Idle &&
			m_CurrentAnimation->PlayedAnimationOnce()) {
			PlayAnimation(AnimationType::Idle);
		}

		m_CurrentAnimation->Update(GetHealthPoints() > 0 ? WHITE : GRAY);
	}
}

void Entity::AddMove(Move* move) {
	m_Movements.push_back(move);
}

const std::vector<Move*>& Entity::GetMoves() const {
	return m_Movements;
}

void Entity::RemoveHealth(float damage)
{
	m_HealthPoints -= damage;
}

void Entity::AddHealth(float healing) {
	m_HealthPoints += Clamp(m_HealthPoints + healing, 0, 98);
}

void Entity::SetHealth(float healthPoints)
{
	m_HealthPoints = healthPoints;
}

MoveType Entity::GetWeakness() const
{
	return m_Weakness;
}