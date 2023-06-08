#pragma once
#include <vector>
#include <raylib.h>
#include "Animation.hpp"

class Entity {
private:
	float m_HealthPoints;
	Animation* m_IdleAnimation;
	Animation* m_DeathAnimation;
	Animation* m_AttackAnimation;
	Animation* m_DamageAnimation;
	Vector2 m_Position;
	Animation* m_CurrentAnimation;
public:
	Entity(
		float healthPoints,
		Vector2 position, 
		Animation* idleAnimation, 
		Animation* deathAnimation,
		Animation* attackAnimation,
		Animation* damageAnimation);

	void ChangeCurrentAnimation(const char* animationName);
		
	void Update(std::vector<Entity*>& entities);
};
