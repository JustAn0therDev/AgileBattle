#pragma once
#include "Entity.hpp"
#include <raylib.h>

class Ui {
private:
	Vector2 m_CursorPosition;
	Entity* m_SelectedEntity;
	Entity* m_HoveringEntity;
	Font m_Font;
public:
	Ui();
	const Font& GetFont();
	bool IsCursorOn(Vector2 pos, Rectangle entityAreaRec);
	Vector2 GetCursorPosition();
	void Update(Entity* entity);
	void Draw();
};