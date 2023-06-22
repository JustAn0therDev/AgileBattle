#pragma once
#include "Entity.hpp"
#include <raylib.h>
#include <vector>
#include <string>
#include "ActiveUiState.hpp"

class Ui {
private:
	const std::string m_MoveText = "Atacar";
	const std::string m_PassText = "Passar";

	Vector2 m_CursorPosition;
	Entity* m_SelectedEntity;
	Entity* m_HoveringEntity;
	Entity* m_SelectedTarget;
	Font m_Font;
	float m_UpperTextBoxHeightLimit;
	float m_LowerTextBoxHeightLimit;
	float m_TextBoxWidthLimit;
	float m_DefaultFontSize;
	float m_DefaultFontSpacing;
	Texture2D m_HealthBarTexture2D;
	Texture2D m_EmptyHealthBarTexture2D;
	Vector2 m_MoveTextPos;
	ActiveUiState m_ActiveUiState;
	Move* m_SelectedMove;

	void DrawContextMenu();
public:
	Ui();

	const Font& GetFont();

	bool IsCursorOn(Vector2 pos, Rectangle entityAreaRec);

	bool IsCursorOn(Vector2 pos);

	Vector2 GetCursorPosition();

	void Update(Entity* entity);

	void Draw();

	void DrawHpBar(
		Entity* entity,
		Rectangle entityRectangle,
		Vector2 entityInfoPos) const;

	const Move* GetSelectedMove() const;

	void RemoveSelectedMove();
};