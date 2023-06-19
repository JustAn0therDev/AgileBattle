#pragma once
#include "Entity.hpp"
#include <raylib.h>
#include <vector>
#include <string>
#include "ActiveMenuState.hpp"

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
	Vector2 m_MoveTextPos;
	Vector2 m_PassTextPos;
	Vector2 m_MoveTextSize;
	Vector2 m_PassTextSize;
	Rectangle m_MoveRec;
	Rectangle m_PassRec;
	ActiveMenuState m_ActiveMenu;

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