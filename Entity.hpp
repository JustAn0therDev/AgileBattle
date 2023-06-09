#pragma once
#include <vector>
#include <raylib.h>
#include "Animation.hpp"
#include "AnimationType.hpp"
#include "EntityType.hpp"
#include "Move.hpp"
#include "MoveType.hpp"

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
	std::vector<Move*> m_Movements;
	MoveType m_Weakness;
public:
	Entity(
		const char* name,
		EntityType entityType,
		float healthPoints,
		Vector2 position, 
		Animation* idleAnimation, 
		Animation* deathAnimation,
		Animation* attackAnimation,
		Animation* damageAnimation,
		MoveType m_Weakness);

	~Entity();

	float GetHealthPoints() const;

	const EntityType& GetEntityType() const;

	void PlayAnimation(AnimationType animationType);

	const char* GetName() const;

	Vector2 GetPosition() const;

	const Animation* GetCurrentAnimation() const;
		
	void Update();

	void AddMove(Move* move);

	const std::vector<Move*>& GetMoves() const;

	void RemoveHealth(float damage);

	void AddHealth(float healing);

	void SetHealth(float healthPoints);

	MoveType GetWeakness() const;
};
