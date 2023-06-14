#pragma once
#include "Entity.hpp"
#include <raylib.h>
#include <vector>
#include <string>

class Ui {
private:
	const std::string m_MoveText = "Atacar";
	const std::string m_PassText = "Passar";

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

	void DrawContextMenu();
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