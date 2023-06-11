#pragma once
#include <vector>
#include <raylib.h>
#include "Animation.hpp"
#include "AnimationType.hpp"
#include "EntityType.hpp"

class Entity {
private:
	const char* m_Name;
	EntityType m_EntityType;
	float m_HealthPoints;
	Animation* m_IdleAnimation;
	Animation* m_DeathAnimation;
	Animation* m_AttackAnimation;
	Animation* m_DamageAnimation;
	Vector2 m_Position;
	Animation* m_CurrentAnimation;
public:
	Entity(
		const char* name,
		EntityType entityType,
		float healthPoints,
		Vector2 position, 
		Animation* idleAnimation, 
		Animation* deathAnimation,
		Animation* attackAnimation,
		Animation* damageAnimation);

	~Entity();

	void ChangeCurrentAnimation(AnimationType animationType);

	const EntityType& GetEntityType();

	Vector2 GetPosition();

	const Animation* GetCurrentAnimation();
		
	void Update(std::vector<Entity*>& entities);
};
