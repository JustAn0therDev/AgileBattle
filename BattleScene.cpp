#include "Constants.hpp"
#include <math.h>
#include "BattleScene.hpp"
#include <iostream>

BattleScene::BattleScene() {
	m_Entities.reserve(Constants::MAX_ENTITIES);

	m_BackgroundTexture =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Backgrounds\\battle.png");

	Texture2D deathAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemDeath.png");

	Texture2D idleAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemIdle.png");

	Texture2D attackAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemAttack.png");

	Texture2D damageAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemDamaged.png");


	Vector2 entityPos = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 1.5f) - ((deathAnimationTextureImage.width / 4) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - deathAnimationTextureImage.height / 2)
	};

	Animation* deathAnimation = new Animation(entityPos, 5, 8, deathAnimationTextureImage, AnimationType::Death);
	Animation* idleAnimation = new Animation(entityPos, 5, 5, idleAnimationTextureImage, AnimationType::Idle);
	Animation* damageAnimation = new Animation(entityPos, 5, 8, damageAnimationTextureImage, AnimationType::Damage);
	Animation* attackAnimation = new Animation(entityPos, 5, 6, attackAnimationTextureImage, AnimationType::Attack);

	Entity* golem = new Entity(
		"Tarefa: Desenv. Interface",
		EntityType::Enemy,
		100.0f,
		entityPos,
		idleAnimation,
		deathAnimation,
		attackAnimation,
		damageAnimation,
		MoveType::FrontEnd);

	Move* golemMove = new Move(10.0f, 10.0f, "COMPLEXIDADE DE RESOLUÇÃO", "Cansa o membro do time durante a resolução da tarefa.", MoveType::None);

	golem->AddMove(golemMove);
	
	Texture2D idleTextureDino
		= LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Dino\\idle.png");

	Vector2 entityPosDino = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 3) - ((idleTextureDino.width / 24) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - idleTextureDino.height / 2)
	};

	Animation* idleDinoAnimation = new Animation(entityPosDino, 5, 4, idleTextureDino, AnimationType::Idle);

	Texture2D attackTextureDino
		= LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Dino\\attack.png");

	Animation* attackDinoAnimation = new Animation(entityPosDino, 3, 3, attackTextureDino, AnimationType::Attack);

	Texture2D damageTextureDino
		= LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Dino\\damage.png");

	Animation* damageDinoAnimation = new Animation(entityPosDino, 5, 4, damageTextureDino, AnimationType::Damage);

	Entity* dino = new Entity(
		"Front-end",
		EntityType::TeamMember,
		100.0f,
		entityPosDino,
		idleDinoAnimation,
		NULL,
		attackDinoAnimation,
		damageDinoAnimation,
		MoveType::ProductOwner);

	Move* move = new Move(10.0f, 10.0f, "Resolver - Front", "Resolve tarefa com habilidades de front-end.", MoveType::FrontEnd);
	Move* move2 = new Move(10.0f, 10.0f, "Resolver", "Resolve tarefa sem habilidade especifica", MoveType::None);
	
	dino->AddMove(move);
	dino->AddMove(move2);

	m_Entities.emplace_back(dino);
	m_Entities.emplace_back(golem);

	std::vector<Entity*> teamMembers;
	teamMembers.push_back(dino);

	std::vector<Entity*> enemies;
	enemies.push_back(golem);

	m_BattleSystem = new BattleSystem(&m_Ui, enemies, teamMembers);
}

void BattleScene::Update() {
	DrawTextureEx(m_BackgroundTexture,
		{ static_cast<float>((Constants::DEFAULT_WIDTH / 2) - (m_BackgroundTexture.width / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - (m_BackgroundTexture.height / 2)) },
		0.0f,
		1.0f,
		WHITE);
	
	for (size_t i = 0; i < m_Entities.size(); i++) {
		if (m_Entities[i] != NULL) {
			m_Entities[i]->Update();
			m_Ui.Update(m_Entities[i]);
		}
	}

	m_BattleSystem->Update();

#ifdef _DEBUG
	DrawFPS(0, 0);
#endif
}

BattleScene::~BattleScene() {
	for (size_t i = 0; i < m_Entities.size(); i++) {
		if (m_Entities[i] != NULL) {
			delete m_Entities[i];
		}
	}

	UnloadTexture(m_BackgroundTexture);
	delete m_BattleSystem;
}

