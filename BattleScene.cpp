﻿#include "Constants.hpp"
#include <math.h>
#include "BattleScene.hpp"
#include <iostream>
#include <raylib.h>

BattleScene::BattleScene() {
	m_BackgroundMusicSound = LoadSound("Assets\\Audio\\Songs\\xDeviruchi - Decisive Battle.wav");
	m_BattleWon = LoadSound("Assets\\Audio\\Songs\\Gym Leader Victory.wav");
	m_BattleLost = LoadSound("Assets\\Audio\\Songs\\Determination.wav");

	SetSoundVolume(m_BackgroundMusicSound, Constants::SOUND_VOLUME);
	SetSoundVolume(m_BattleWon, Constants::SOUND_VOLUME);
	SetSoundVolume(m_BattleLost, Constants::SOUND_VOLUME);

	// Play the main battle theme song
	PlaySound(m_BackgroundMusicSound);

	// Reserve the max space for the entities list of the game
	m_Entities.reserve(Constants::MAX_ENTITIES);

	// Set background
	m_BackgroundTexture =
		LoadTexture("Assets\\Images\\Backgrounds\\battle.png");
	
	// Set all team members:

	// Setting Front-end
	Texture2D idleTextureDinoFrontEnd
		= LoadTexture("Assets\\Images\\Dino - Front\\idle.png");

	Vector2 entityPosDino = { 200.0f, 225.0f };

	Animation* idleDinoFrontEndAnimation = new Animation(entityPosDino, 5, 4, idleTextureDinoFrontEnd, AnimationType::Idle);

	Texture2D attackTextureDinoFrontEnd
		= LoadTexture("Assets\\Images\\Dino - Front\\attack.png");

	Animation* attackDinoFrontEndAnimation = new Animation(entityPosDino, 3, 3, attackTextureDinoFrontEnd, AnimationType::Attack);

	Texture2D damageTextureDinoFrontEnd
		= LoadTexture("Assets\\Images\\Dino - Front\\damage.png");

	Animation* damageDinoFrontEndAnimation = new Animation(entityPosDino, 5, 3, damageTextureDinoFrontEnd, AnimationType::Damage);

	Entity* dinoFrontEnd = new Entity(
		"Front-end",
		EntityType::TeamMember,
		100.0f,
		entityPosDino,
		idleDinoFrontEndAnimation,
		NULL,
		attackDinoFrontEndAnimation,
		damageDinoFrontEndAnimation,
		MoveType::None);

	Move* moveFrontEnd = new Move(5.0f, 10.0f, "Resolver - Front", "Resolve tarefa com habilidades de front-end.", MoveType::FrontEnd);
	
	dinoFrontEnd->AddMove(moveFrontEnd);

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
		MoveType::None);

	Move* moveSM = new Move(5.0f, 10.0f, "Corrigir Sprint", "Corrige problemas na sprint.", MoveType::ScrumMaster);

	dinoSM->AddMove(moveSM);

	// Setting Back-end
	Texture2D idleTextureDinoBack
		= LoadTexture("Assets\\Images\\Dino - Back\\idle.png");

	entityPosDino.y += 100.0f;

	Animation* idleDinoBackAnimation = new Animation(entityPosDino, 5, 4, idleTextureDinoBack, AnimationType::Idle);

	Texture2D attackTextureDinoBack
		= LoadTexture("Assets\\Images\\Dino - Back\\attack.png");

	Animation* attackDinoBackAnimation = new Animation(entityPosDino, 3, 3, attackTextureDinoBack, AnimationType::Attack);

	Texture2D damageTextureDinoBack
		= LoadTexture("Assets\\Images\\Dino - Back\\damage.png");

	Animation* damageDinoBackAnimation = new Animation(entityPosDino, 5, 3, damageTextureDinoBack, AnimationType::Damage);

	Entity* dinoBackEnd = new Entity(
		"Back-end",
		EntityType::TeamMember,
		100.0f,
		entityPosDino,
		idleDinoBackAnimation,
		NULL,
		attackDinoBackAnimation,
		damageDinoBackAnimation,
		MoveType::None);

	Move* moveBack = new Move(5.0f, 10.0f, "Resolver - Back", "Resolve tarefa com habilidades de back-end.", MoveType::BackEnd);

	dinoBackEnd->AddMove(moveBack);

	// Setting Product Owner
	Texture2D idleTextureDinoPO
		= LoadTexture("Assets\\Images\\Dino - PO\\idle.png");

	entityPosDino.y += 100.0f;

	Animation* idleDinoPOAnimation = new Animation(entityPosDino, 5, 4, idleTextureDinoPO, AnimationType::Idle);

	Texture2D attackTextureDinoPO
		= LoadTexture("Assets\\Images\\Dino - PO\\attack.png");

	Animation* attackDinoPOAnimation = new Animation(entityPosDino, 3, 3, attackTextureDinoPO, AnimationType::Attack);

	Texture2D damageTextureDinoPO
		= LoadTexture("Assets\\Images\\Dino - PO\\damage.png");

	Animation* damageDinoPOAnimation = new Animation(entityPosDino, 5, 3, damageTextureDinoPO, AnimationType::Damage);

	Entity* dinoPO = new Entity(
		"Product Owner",
		EntityType::TeamMember,
		100.0f,
		entityPosDino,
		idleDinoPOAnimation,
		NULL,
		attackDinoPOAnimation,
		damageDinoPOAnimation,
		MoveType::None);

	Move* movePO = new Move(5.0f, 10.0f, "Priorizar Backlog", "Prioriza os itens no backlog.", MoveType::ProductOwner);

	dinoPO->AddMove(movePO);

	// And now, set all enemies:

	// Interface
	Texture2D idleTextureTaskInterface =
		LoadTexture("Assets\\Images\\Task - Interface\\idle.png");

	Texture2D attackTextureTaskInterface =
		LoadTexture("Assets\\Images\\Task - Interface\\attack.png");

	Texture2D damageTextureTaskInterface = LoadTexture("Assets\\Images\\Task - Interface\\damage.png");

	Vector2 entityPosTask = { 900.0f, 225.0f };

	Animation* idleAnimationTaskInterface = new Animation(entityPosTask, 2, 2, idleTextureTaskInterface, AnimationType::Idle);
	Animation* damageAnimationTaskInterface = new Animation(entityPosTask, 3, 4, damageTextureTaskInterface, AnimationType::Damage);
	Animation* attackAnimationTaskInterface = new Animation(entityPosTask, 5, 8, attackTextureTaskInterface, AnimationType::Attack);

	Entity* taskInterface = new Entity(
		"Tarefa: Desenv. Interface",
		EntityType::Enemy,
		100.0f,
		entityPosTask,
		idleAnimationTaskInterface,
		NULL,
		attackAnimationTaskInterface,
		damageAnimationTaskInterface,
		MoveType::FrontEnd);

	Move* taskMove = new Move(15.0f, 10.0f, "", "", MoveType::Task);

	taskInterface->AddMove(taskMove);

	// WebAPI - BackEnd task
	Texture2D idleTextureTaskWebApi =
		LoadTexture("Assets\\Images\\Task - WebAPI\\idle.png");

	Texture2D attackTextureTaskWebApi =
		LoadTexture("Assets\\Images\\Task - WebAPI\\attack.png");

	Texture2D damageTextureTaskWebApi = LoadTexture("Assets\\Images\\Task - WebAPI\\damage.png");

	entityPosTask.y += 100.0f;

	Animation* idleAnimationTaskWebApi = new Animation(entityPosTask, 2, 2, idleTextureTaskWebApi, AnimationType::Idle);
	Animation* damageAnimationTaskWebApi = new Animation(entityPosTask, 3, 4, damageTextureTaskWebApi, AnimationType::Damage);
	Animation* attackAnimationTaskWebApi = new Animation(entityPosTask, 5, 8, attackTextureTaskWebApi, AnimationType::Attack);

	Entity* taskWebApi = new Entity(
		"Tarefa: Desenv. WebAPI",
		EntityType::Enemy,
		100.0f,
		entityPosTask,
		idleAnimationTaskWebApi,
		NULL,
		attackAnimationTaskWebApi,
		damageAnimationTaskWebApi,
		MoveType::BackEnd);

	Move* taskMoveWebApi = new Move(15.0f, 10.0f, "", "", MoveType::Task);

	taskWebApi->AddMove(taskMoveWebApi);

	// PO - Prioritize Backlog
	Texture2D idleTextureTaskBacklog =
		LoadTexture("Assets\\Images\\Task - Prioritize Backlog\\idle.png");

	Texture2D attackTextureTaskBacklog =
		LoadTexture("Assets\\Images\\Task - Prioritize Backlog\\attack.png");

	Texture2D damageTextureTaskBacklog = LoadTexture("Assets\\Images\\Task - Prioritize Backlog\\damage.png");

	entityPosTask.y += 100.0f;

	Animation* idleAnimationTaskBacklog = new Animation(entityPosTask, 2, 2, idleTextureTaskBacklog, AnimationType::Idle);
	Animation* damageAnimationTaskBacklog = new Animation(entityPosTask, 3, 4, damageTextureTaskBacklog, AnimationType::Damage);
	Animation* attackAnimationTaskBacklog = new Animation(entityPosTask, 5, 8, attackTextureTaskBacklog, AnimationType::Attack);

	Entity* taskSprintBacklog = new Entity(
		"Backlog",
		EntityType::Enemy,
		100.0f,
		entityPosTask,
		idleAnimationTaskBacklog,
		NULL,
		attackAnimationTaskBacklog,
		damageAnimationTaskBacklog,
		MoveType::ProductOwner);

	Move* taskMoveBacklog = new Move(15.0f, 10.0f, "", "", MoveType::Task);

	taskSprintBacklog->AddMove(taskMoveBacklog);

	// Sprint Issues
	Texture2D idleTextureTaskSprintIssues =
		LoadTexture("Assets\\Images\\Task - Sprint Issues\\idle.png");

	Texture2D attackTextureTaskSprintIssues =
		LoadTexture("Assets\\Images\\Task - Sprint Issues\\attack.png");

	Texture2D damageTextureTaskSprintIssues = LoadTexture("Assets\\Images\\Task - Sprint Issues\\damage.png");

	entityPosTask.y += 100.0f;

	Animation* idleAnimationTaskSprintIssues = new Animation(entityPosTask, 2, 2, idleTextureTaskSprintIssues, AnimationType::Idle);
	Animation* damageAnimationTaskSprintIssues = new Animation(entityPosTask, 3, 4, damageTextureTaskSprintIssues, AnimationType::Damage);
	Animation* attackAnimationTaskSprintIssues = new Animation(entityPosTask, 5, 8, attackTextureTaskSprintIssues, AnimationType::Attack);

	Entity* taskSprintIssues = new Entity(
		"Problemas na Sprint",
		EntityType::Enemy,
		100.0f,
		entityPosTask,
		idleAnimationTaskSprintIssues,
		NULL,
		attackAnimationTaskSprintIssues,
		damageAnimationTaskSprintIssues,
		MoveType::ScrumMaster);

	Move* taskMoveSprintIssues = new Move(15.0f, 10.0f, "", "", MoveType::Task);

	taskSprintIssues->AddMove(taskMoveSprintIssues);

	// Finishing the entity list
	m_Entities.emplace_back(dinoFrontEnd);
	m_Entities.emplace_back(dinoSM);
	m_Entities.emplace_back(dinoBackEnd);
	m_Entities.emplace_back(dinoPO);
	m_Entities.emplace_back(taskInterface);
	m_Entities.emplace_back(taskSprintIssues);
	m_Entities.emplace_back(taskWebApi);
	m_Entities.emplace_back(taskSprintBacklog);

	// Setting who are the team members
	std::vector<Entity*> teamMembers;
	teamMembers.reserve(4);
	teamMembers.emplace_back(dinoFrontEnd);
	teamMembers.emplace_back(dinoSM);
	teamMembers.emplace_back(dinoBackEnd);
	teamMembers.emplace_back(dinoPO);

	// And their enemies, since the battle system
	// must be capable of differentiating between them.
	std::vector<Entity*> enemies;
	enemies.reserve(4);
	enemies.emplace_back(taskInterface);
	enemies.emplace_back(taskSprintIssues);
	enemies.emplace_back(taskWebApi);
	enemies.emplace_back(taskSprintBacklog);

	m_BattleSystem = new BattleSystem(&m_Ui, enemies, teamMembers);
}

void BattleScene::Update() {
	// Making sure that the background music is always being played
	// on repeat.
	if (!IsSoundPlaying(m_BackgroundMusicSound) && !m_BattleSystem->GetPlayerLost() && !m_BattleSystem->GetPlayerWon()) {
		PlaySound(m_BackgroundMusicSound);
	}
	
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

	if (m_BattleSystem->GetPlayerWon() && IsSoundPlaying(m_BackgroundMusicSound)) {
		// Play "player won" song
		StopSound(m_BackgroundMusicSound);
		PlaySound(m_BattleWon);
	}
	else if (m_BattleSystem->GetPlayerLost() && IsSoundPlaying(m_BackgroundMusicSound)) {
		// Play "player lost" song
		StopSound(m_BackgroundMusicSound);
		PlaySound(m_BattleLost);
	}

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
	
	// Unloading themes
	UnloadSound(m_BattleWon);
	UnloadSound(m_BattleLost);
}

