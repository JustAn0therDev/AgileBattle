#include "BattleScene.hpp"
#include "Constants.hpp"

BattleScene::BattleScene() {
	Texture2D deathAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemDefeated.png");

	Vector2 entityPos = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 2) - ((deathAnimationTextureImage.width / 4) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - deathAnimationTextureImage.height / 2)
	};

	Animation* deathAnimation = new Animation(entityPos, 4, 4, deathAnimationTextureImage);

	Entity* golem = new Entity(10.0f, entityPos, NULL, deathAnimation, NULL, NULL);
	golem->ChangeCurrentAnimation(AnimationType::Death);

	Texture2D textureDino
		= LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Dino\\DinoSprites - doux.png");

	Vector2 entityPosDino = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 3) - ((textureDino.width / 24) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - textureDino.height / 2)
	};

	Animation* dinoAnimation = new Animation(entityPosDino, 24, 24, textureDino);

	Entity* dino = new Entity(10.0f, entityPosDino, dinoAnimation, NULL, NULL, NULL);
	dino->ChangeCurrentAnimation(AnimationType::Idle);

	m_Entities.push_back(dino);
	m_Entities.push_back(golem);
}

void BattleScene::Update() {
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
}