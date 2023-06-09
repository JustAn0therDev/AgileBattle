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

void Entity::ChangeCurrentAnimation(const char* animationName) {
	if (animationName == "Death") {
		m_CurrentAnimation = m_DeathAnimation;
	}
}

void Entity::Update(std::vector<Entity*>& entities, Ui& ui) {
	if (m_CurrentAnimation != NULL) {
		m_CurrentAnimation->Update();
	}

	if (ui.IsCursorOn(m_Position, m_CurrentAnimation->GetAnimationRectangle())) {
		std::cout << "CURSOR IS ON!!1\n";
	}
	else {
		std::cout << "CURSOR IS OFF!\n";
	}
}
