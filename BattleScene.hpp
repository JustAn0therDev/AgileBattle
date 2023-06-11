#pragma once
#include "Scene.hpp"
#include <vector>

class BattleScene : public Scene {
private:
	std::vector<Entity*> m_Entities;
	Ui m_Ui;
	Texture2D m_BackgroundTexture;
public:
	BattleScene();
	void Update();
	~BattleScene();
};