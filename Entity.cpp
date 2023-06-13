#include "Entity.hpp"
#include <iostream>

Entity::Entity(
	const char* name,
	EntityType entityType,
	float healthPoints,
	Vector2 position,
	Animation* idleAnimation,
	Animation* deathAnimation,
	Animation* attackAnimation,
	Animation* damageAnimation) {
	m_Name = name;
	m_EntityType = entityType;
	m_HealthPoints = healthPoints;
	m_Position = position;
	m_IdleAnimation = idleAnimation;
	m_DeathAnimation = deathAnimation;
	m_AttackAnimation = attackAnimation;
	m_DamageAnimation = damageAnimation;
	m_CurrentAnimation = NULL;
}

Entity::~Entity() {
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

void Entity::ChangeCurrentAnimation(AnimationType animationType) {
	switch (animationType)
	{
	case Idle:
		m_CurrentAnimation = m_IdleAnimation;
		break;
	case Attack:
		break;
	case Damage:
		break;
	case Death:
		m_CurrentAnimation = m_DeathAnimation;
		break;
	default:
		break;
	}
}

const EntityType& Entity::GetEntityType() const {
	return m_EntityType;
}

const Animation* Entity::GetCurrentAnimation() const {
	return m_CurrentAnimation;
}

void Entity::Update(std::vector<Entity*>& entities) {
	if (m_CurrentAnimation != NULL) {
		m_CurrentAnimation->Update();
	}

	// TODO: TEMPORARY
	if (IsKeyPressed(KEY_DOWN)) {
		m_HealthPoints -= 8;
	}
	else if (IsKeyPressed(KEY_UP)) {
		m_HealthPoints += 8;
	}
}
