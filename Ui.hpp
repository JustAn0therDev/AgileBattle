#pragma once
#include "Entity.hpp"
#include <raylib.h>

class Ui {
private:
	Vector2 m_CursorPosition;
	Entity* m_SelectedEntity;
public:
	Ui();
	bool IsCursorOn(Vector2 pos, Rectangle entityAreaRec);
	Vector2 GetCursorPosition();
	void SetSelectedEntity(Entity* entity);
	void Update(Entity* entity);
	void Draw();
};