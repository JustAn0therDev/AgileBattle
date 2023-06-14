#pragma once
#include "Entity.hpp"
#include <raylib.h>

class Ui {
private:
	Vector2 m_CursorPosition;
	Entity* m_SelectedEntity;
	Entity* m_HoveringEntity;
	Font m_Font;
	float m_UpperTextBoxHeightLimit;
	float m_LowerTextBoxHeightLimit;
	float m_TextBoxWidthLimit;
	float m_DefaultFontSize;
	float m_DefaultFontSpacing;
	Texture2D m_HealthBarTexture2D;
	Texture2D m_EmptyHealthBarTexture2D;

	Rectangle GetHealthBarRectangleByEntityHealth(float entityHealth) const;
public:
	Ui();
	const Font& GetFont();
	bool IsCursorOn(Vector2 pos, Rectangle entityAreaRec);
	Vector2 GetCursorPosition();
	void Update(Entity* entity);
	void Draw();
	void DrawHpBar(
		Entity* entity,
		Rectangle entityRectangle,
		Vector2 entityInfoPos) const;
};