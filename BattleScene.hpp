#pragma once
#include "Scene.hpp"
#include <vector>
#include "BattleSystem.hpp"

class BattleScene : public Scene {
private:
	std::vector<Entity*> m_Entities;
	Ui m_Ui;
	Texture2D m_BackgroundTexture;
	BattleSystem* m_BattleSystem;
	Sound m_BackgroundMusicSound;
public:
	BattleScene();
	void Update();
	~BattleScene();
};