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
	bool m_RunningDamageAnimation;
	int m_DamageDrawValue;
	bool m_DamageHasModifier;
	Vector2 m_DesiredDrawDamagePos;
	Vector2 m_CurrentDrawDamagePos;
	bool m_Locked;
	bool m_PlayerWon;
	bool m_PlayerLost;

	void UpdateContextMenu();
	void ExecuteDrawDamageAnimation();
	void DrawWinText() const;
	void DrawLoseText() const;
public:
	Ui();

	const Font& GetFont();

	bool IsCursorOn(Vector2 pos, Rectangle entityAreaRec);

	bool IsCursorOn(Vector2 pos);

	Vector2 GetCursorPosition();
	
	void SetupDrawDamageAnimation();

	void Update(Entity* entity);

	void Draw();

	void DrawHpBar(
		Entity* entity,
		Rectangle entityRectangle,
		Vector2 entityInfoPos) const;

	void DrawEntityInformation(Entity* entity) const;

	Entity* GetSelectedTarget() const;

	Entity* GetSelectedEntity() const;

	const Move* GetSelectedMove() const;

	void SetSelectedEntity(Entity* entity);

	void SetSelectedTarget(Entity* entity);

	void SetSelectedMove(Move* move);

	void RemoveSelectedMove();

	void RemoveSelectedTarget();

	void RemoveHoveringEntity();

	void RemoveSelectedEntity();

	void ChangeUiState(ActiveUiState activeUiState);

	void ResetUiState();

	void Lock();

	void ReleaseLock();

	bool IsLocked() const;

	void SetPlayerWon();

	void SetPlayerLost();
};