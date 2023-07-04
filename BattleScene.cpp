#include "Constants.hpp"
#include <math.h>
#include "BattleScene.hpp"
#include <iostream>
#include <raylib.h>

BattleScene::BattleScene() {
	m_BackgroundMusicSound = LoadSound("Assets\\Audio\\Songs\\xDeviruchi - Decisive Battle.wav");

	SetSoundVolume(m_BackgroundMusicSound, Constants::SOUND_VOLUME);

	// Play the main battle theme song 
	PlaySound(m_BackgroundMusicSound);
	
	m_Entities.reserve(Constants::MAX_ENTITIES);

	m_BackgroundTexture =
		LoadTexture("Assets\\Images\\Backgrounds\\battle.png");

	Texture2D deathAnimationTextureImage =
		LoadTexture("Assets\\Images\\Golem\\GolemDeath.png");

	Texture2D idleAnimationTextureImage =
		LoadTexture("Assets\\Images\\Golem\\GolemIdle.png");

	Texture2D attackAnimationTextureImage =
		LoadTexture("Assets\\Images\\Golem\\GolemAttack.png");

	Texture2D damageAnimationTextureImage =
		LoadTexture("Assets\\Images\\Golem\\GolemDamaged.png");

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
	
	// Setting Front-end
	Texture2D idleTextureDinoFrontEnd
		= LoadTexture("Assets\\Images\\Dino - Front\\idle.png");

	Vector2 entityPosDino = {
		static_cast<float>((Constants::DEFAULT_WIDTH / 3) - ((idleTextureDinoFrontEnd.width / 24) / 2)),
		static_cast<float>((Constants::DEFAULT_HEIGHT / 2) - idleTextureDinoFrontEnd.height / 2)
	};

	Animation* idleDinoFrontEndAnimation = new Animation(entityPosDino, 5, 4, idleTextureDinoFrontEnd, AnimationType::Idle);

	Texture2D attackTextureDinoFrontEnd
		= LoadTexture("Assets\\Images\\Dino - Front\\attack.png");

	Animation* attackDinoFrontEndAnimation = new Animation(entityPosDino, 3, 3, attackTextureDinoFrontEnd, AnimationType::Attack);

	Texture2D damageTextureDinoFrontEnd
		= LoadTexture("Assets\\Images\\Dino - Front\\damage.png");

	Animation* damageDinoFrontEndAnimation = new Animation(entityPosDino, 5, 4, damageTextureDinoFrontEnd, AnimationType::Damage);

	Entity* dinoFrontEnd = new Entity(
		"Front-end",
		EntityType::TeamMember,
		100.0f,
		entityPosDino,
		idleDinoFrontEndAnimation,
		NULL,
		attackDinoFrontEndAnimation,
		damageDinoFrontEndAnimation,
		MoveType::ProductOwner);

	Move* moveFrontEnd = new Move(10.0f, 10.0f, "Resolver - Front", "Resolve tarefa com habilidades de front-end.", MoveType::FrontEnd);
	Move* moveFrontEnd2 = new Move(10.0f, 10.0f, "Resolver", "Resolve tarefa sem habilidade especifica", MoveType::None);
	
	dinoFrontEnd->AddMove(moveFrontEnd);
	dinoFrontEnd->AddMove(moveFrontEnd2);

	// Setting Scrum Master
	Texture2D idleTextureDinoSM
		= LoadTexture("Assets\\Images\\Dino - SM\\idle.png");

	entityPosDino.y += 100.0f;

	Animation* idleDinoSMAnimation = new Animation(entityPosDino, 5, 4, idleTextureDinoSM, AnimationType::Idle);

	Texture2D attackTextureDinoSM
		= LoadTexture("Assets\\Images\\Dino - SM\\attack.png");

	Animation* attackDinoSMAnimation = new Animation(entityPosDino, 3, 3, attackTextureDinoSM, AnimationType::Attack);

	Texture2D damageTextureDinoSM
		= LoadTexture("Assets\\Images\\Dino - SM\\damage.png");

	Animation* damageDinoSMAnimation = new Animation(entityPosDino, 5, 3, damageTextureDinoSM, AnimationType::Damage);

	Entity* dinoSM = new Entity(
		"Scrum Master",
		EntityType::TeamMember,
		100.0f,
		entityPosDino,
		idleDinoSMAnimation,
		NULL,
		attackDinoSMAnimation,
		damageDinoSMAnimation,
		MoveType::ProductOwner);

	Move* moveSM = new Move(10.0f, 10.0f, "Corrigir Sprint", "Corrige problemas na sprint (REVISAR).", MoveType::ScrumMaster);

	dinoSM->AddMove(moveSM);

	m_Entities.emplace_back(dinoFrontEnd);
	m_Entities.emplace_back(dinoSM);
	m_Entities.emplace_back(golem);

	std::vector<Entity*> teamMembers;
	teamMembers.push_back(dinoFrontEnd);
	teamMembers.push_back(dinoSM);

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

	// Unloading textures
	UnloadTexture(m_BackgroundTexture);
	delete m_BattleSystem;

	// Unloading Background Music
	UnloadSound(m_BackgroundMusicSound);
}

