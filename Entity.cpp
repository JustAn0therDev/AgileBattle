#include "Entity.hpp"
#include <iostream>

Entity::Entity(
	float healthPoints,
	Vector2 position,
	Animation* idleAnimation,
	Animation* deathAnimation,
	Animation* attackAnimation,
	Animation* damageAnimation) {
	m_HealthPoints = healthPoints;
	m_Position = position;
	m_IdleAnimation = idleAnimation;
	m_DeathAnimation = deathAnimation;
	m_AttackAnimation = attackAnimation;
	m_DamageAnimation = damageAnimation;
	m_CurrentAnimation = NULL;
}

Vector2 Entity::GetPosition() {
	return m_Position;
}

void Entity::ChangeCurrentAnimation(const char* animationName) {
	if (animationName == "Death") {
		m_CurrentAnimation = m_DeathAnimation;
	} else if (animationName == "Idle") {
		m_CurrentAnimation = m_IdleAnimation;
	}
}

const Animation* Entity::GetCurrentAnimation()
{
	return m_CurrentAnimation;
}

void Entity::Update(std::vector<Entity*>& entities) {
	if (m_CurrentAnimation != NULL) {
		m_CurrentAnimation->Update();
	}
}
