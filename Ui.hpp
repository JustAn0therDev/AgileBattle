#pragma once
#include <raylib.h>

class Ui {
private:
	Vector2 m_CursorPosition;
public:
	Ui();
	bool IsCursorOn(Vector2 pos, Rectangle entityAreaRec);
	Vector2 GetCursorPosition();
	void Update();
};