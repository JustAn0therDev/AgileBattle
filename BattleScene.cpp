#include "BattleScene.hpp"
#include "Constants.hpp"
#include <math.h>

BattleScene::BattleScene() {
	m_Entities.reserve(Constants::MAX_ENTITIES);

	m_BackgroundTexture =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Backgrounds\\desert.png");

	Texture2D deathAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemDefeated.png");

	Vector2 entityPos = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 2) - ((deathAnimationTextureImage.width / 4) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - deathAnimationTextureImage.height / 2)
	};

	Animation* deathAnimation = new Animation(entityPos, 5, 4, deathAnimationTextureImage);

	Entity* golem = new Entity(
		"Tarefa #3",
		EntityType::Enemy,
		10.0f,
		entityPos,
		NULL,
		deathAnimation,
		NULL,
		NULL);
	
	golem->ChangeCurrentAnimation(AnimationType::Death);

	Texture2D textureDino
		= LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Dino\\DinoSprites - doux.png");

	Vector2 entityPosDino = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 3) - ((textureDino.width / 24) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - textureDino.height / 2)
	};

	Animation* dinoAnimation = new Animation(entityPosDino, 5, 24, textureDino);

	Entity* dino = new Entity(
		"Front-end",
		EntityType::TeamMember,
		10.0f,
		entityPosDino,
		dinoAnimation,
		NULL,
		NULL,
		NULL);

	dino->ChangeCurrentAnimation(AnimationType::Idle);

	m_Entities.emplace_back(dino);
	m_Entities.emplace_back(golem);
}

void BattleScene::Update() {
	DrawTextureEx(m_BackgroundTexture,
		{ static_cast<float>((Constants::DEFAULT_WIDTH / 2) - ((m_BackgroundTexture.width / 1.5f))),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - m_BackgroundTexture.height / 1.5f) },
		0.0f,
		1.5f,
		WHITE);
	
	for (size_t i = 0; i < m_Entities.size(); i++) {
		if (m_Entities[i] != NULL) {
			m_Entities[i]->Update(m_Entities);
			m_Ui.Update(m_Entities[i]);
		}
	}

	m_Ui.Draw();
}

BattleScene::~BattleScene() {
	for (size_t i = 0; i < m_Entities.size(); i++) {
		if (m_Entities[i] != NULL) {
			delete m_Entities[i];
		}
	}

	UnloadTexture(m_BackgroundTexture);
}