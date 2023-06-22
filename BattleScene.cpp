#include "Constants.hpp"
#include <math.h>
#include "BattleScene.hpp"
#include <iostream>

BattleScene::BattleScene() {
	m_Entities.reserve(Constants::MAX_ENTITIES);

	m_BackgroundTexture =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Backgrounds\\battle.png");

	Texture2D deathAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemDefeated.png");

	Texture2D idleAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemIdle.png");

	Vector2 entityPos = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 2) - ((deathAnimationTextureImage.width / 4) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - deathAnimationTextureImage.height / 2)
	};

	Animation* deathAnimation = new Animation(entityPos, 4, 4, deathAnimationTextureImage, AnimationType::Death);
	Animation* idleAnimation = new Animation(entityPos, 3, 8, idleAnimationTextureImage, AnimationType::Idle);

	Entity* golem = new Entity(
		"Tarefa #1",
		EntityType::Enemy,
		100.0f,
		entityPos,
		idleAnimation,
		deathAnimation,
		NULL,
		NULL);

	Move* golemMove = new Move(10.0f, 10.0f, "COMPLEXIDADE DE RESOLUÇÃO", "Cansa o membro do time durante a resolução da tarefa.");

	golem->AddMove(golemMove);
	
	Texture2D textureDino
		= LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Dino\\DinoSprites - doux.png");

	Vector2 entityPosDino = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 3) - ((textureDino.width / 24) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - textureDino.height / 2)
	};

	Animation* dinoAnimation = new Animation(entityPosDino, 5, 24, textureDino, AnimationType::Idle);

	Entity* dino = new Entity(
		"Front-end",
		EntityType::TeamMember,
		100.0f,
		entityPosDino,
		dinoAnimation,
		dinoAnimation,
		dinoAnimation,
		dinoAnimation);

	Move* move = new Move(10.0f, 10.0f, "Resolver - Front", "Resolve tarefa com habilidades de front-end.");
	
	dino->AddMove(move);

	m_Entities.emplace_back(dino);
	m_Entities.emplace_back(golem);

	m_BattleSystem = new BattleSystem(&m_Ui);
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
			m_Entities[i]->Update(m_Entities);
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

