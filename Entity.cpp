#include "Entity.hpp"
#include <iostream>
#include <raymath.h>

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

	// The current animation is always "idle", unless another
	// system actively changes it.
	m_CurrentAnimation = m_IdleAnimation; 
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

const EntityType& Entity::GetEntityType() const {
	return m_EntityType;
}

void Entity::PlayAnimation(AnimationType animationType) {
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

	// This is not checked in the idle animation set.
	// Outside of it, any animation is only played once.
	m_CurrentAnimation->SetPlayedAnimationOnce(false);
}

const Animation* Entity::GetCurrentAnimation() const {
	return m_CurrentAnimation;
}

void Entity::Update(std::vector<Entity*>& entities) {
	// TODO: The animation will also be handled by the 
	// battle system, when a character attacks, takes damage or 
	// perishes in battle.
	if (IsKeyPressed(KEY_A)) {
		PlayAnimation(AnimationType::Death);
	}

	if (m_CurrentAnimation != NULL) {
		m_CurrentAnimation->Update();

		if (m_CurrentAnimation->GetAnimationType() != AnimationType::Idle &&
			m_CurrentAnimation->PlayedAnimationOnce()) {
			PlayAnimation(AnimationType::Idle);
		}
	}

    // TODO: This should be set in the BattleSystem.cpp
    // m_HealthPoints = Lerp(m_HealthPoints, m_LowTargetHealthPoints, 0.1f);
}
