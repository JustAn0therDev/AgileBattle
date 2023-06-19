#include "Ui.hpp"
#include "Animation.hpp"
#include <string>
#include <raymath.h>
#include <vector>

void Ui::DrawContextMenu()
{
	std::string arrowBuffer = "->";

	if (m_ActiveMenu == ActiveMenuState::NONE) {
		if (IsCursorOn(m_MoveTextPos, m_MoveRec)) {
			DrawTextEx(m_Font, arrowBuffer.append(m_MoveText).c_str(), m_MoveTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
		}
		else {
			DrawTextEx(m_Font, m_MoveText.c_str(), m_MoveTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
		}

		if (IsCursorOn(m_PassTextPos, m_PassRec)) {
			DrawTextEx(m_Font, arrowBuffer.append(m_PassText).c_str(), m_PassTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
		}
		else {
			DrawTextEx(m_Font, m_PassText.c_str(), m_PassTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
		}
	}
	else if (m_ActiveMenu == ActiveMenuState::MOVE) {
		std::vector<Move*> entityMovements = m_SelectedEntity->GetMoves();

		Vector2 moveOptionPos = m_MoveTextPos;

		int moveOptionY = 0;

		for (const auto& move : entityMovements) {
			moveOptionPos.y += moveOptionY;

			const char* name = move->GetName();
			const char* details = move->GetDetails();

			Vector2 nameTextSize = MeasureTextEx(m_Font, name, m_DefaultFontSize, m_DefaultFontSpacing);
			Vector2 detailsTextSize = MeasureTextEx(m_Font, details, m_DefaultFontSize, m_DefaultFontSpacing);

			Rectangle nameRec = { 0.0f, 0.0f, nameTextSize.x, nameTextSize.y - 30 };
			Rectangle detailsRec = { 0.0f, 0.0f, detailsTextSize.x, detailsTextSize.y - 30 };

			if (IsCursorOn(moveOptionPos, nameRec)) {
				DrawTextEx(m_Font, arrowBuffer.append(name).c_str(), moveOptionPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
			}
			else {
				DrawTextEx(m_Font, name, moveOptionPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
			}

			Vector2 moveDescriptionPos = { moveOptionPos.x + 400, moveOptionPos.y };

			DrawTextEx(m_Font, details, moveDescriptionPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);

			moveOptionY += 50;
		}
	}

}

Ui::Ui() : m_CursorPosition({ 0.0f, 0.0f })
{
	m_DefaultFontSize = 72.0f;
	m_DefaultFontSpacing = 2.0f;
	m_Font = LoadFontEx("Assets\\Fonts\\Cloude_Regular_Bold_1.03.otf", m_DefaultFontSize, 0, 256);
	m_SelectedEntity = NULL;
	m_HoveringEntity = NULL;
	m_UpperTextBoxHeightLimit = 590.0f;
	m_LowerTextBoxHeightLimit = 794.0f;
	m_TextBoxWidthLimit = 35.0f;
	m_HealthBarTexture2D = LoadTexture("Assets\\Images\\Health\\health_bar.png");
	m_EmptyHealthBarTexture2D = LoadTexture("Assets\\Images\\Health\\empty_bar.png");
	m_MoveTextSize = MeasureTextEx(m_Font, m_MoveText.c_str(), m_DefaultFontSize, m_DefaultFontSpacing);
	m_MoveRec = { 0.0f, 0.0f, m_MoveTextSize.x, m_MoveTextSize.y - 30 };
	m_PassTextSize = MeasureTextEx(m_Font, m_PassText.c_str(), m_DefaultFontSize, m_DefaultFontSpacing);
	m_PassRec = { 0.0f, 0.0f, m_PassTextSize.x, m_PassTextSize.y - 30 };
	m_MoveTextPos = { m_TextBoxWidthLimit, m_UpperTextBoxHeightLimit };
	m_PassTextPos = { m_TextBoxWidthLimit, m_UpperTextBoxHeightLimit + 50 };
	m_ActiveMenu = ActiveMenuState::NONE;
}

const Font& Ui::GetFont() {
	return m_Font;
}

bool Ui::IsCursorOn(Vector2 pos, Rectangle entityAreaRec)
{
	return m_CursorPosition.x >= pos.x &&
		   m_CursorPosition.x <= (pos.x + entityAreaRec.width) &&
		   m_CursorPosition.y >= pos.y &&
		   m_CursorPosition.y <= (pos.y + entityAreaRec.height);
}

Vector2 Ui::GetCursorPosition()
{
	return m_CursorPosition;
}

void Ui::Update(Entity* entity) {
	m_CursorPosition = GetMousePosition();

	if (entity != NULL) {
		Vector2 entityPos = entity->GetPosition();
		Rectangle rec = entity->GetCurrentAnimation()->GetAnimationRectangle();

		bool isCursorOn = IsCursorOn(entityPos, rec);

		bool isCursorOnOption = IsCursorOn(m_MoveTextPos, m_MoveRec) || IsCursorOn(m_PassTextPos, m_PassRec);

		if (isCursorOn) {
			m_HoveringEntity = entity;
		}
		else if (!isCursorOn && entity == m_HoveringEntity) {
			m_HoveringEntity = NULL;
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (isCursorOn) {
				m_SelectedEntity = entity;
			}
			else if (!isCursorOn && entity == m_SelectedEntity && !isCursorOnOption) {
				m_SelectedEntity = NULL;
				// The player is not selecting anything, so there is no way to show the character's moves.
				m_ActiveMenu = ActiveMenuState::NONE;
			}
		}
	}

	// After checking an entity, we should check whether the player has clicked on an option 
	// in the context menu.
	if (IsCursorOn(m_MoveTextPos, m_MoveRec) && m_SelectedEntity != NULL && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		m_ActiveMenu = ActiveMenuState::MOVE;
	}
	else if (IsCursorOn(m_PassTextPos, m_PassRec)) {
		// In this case, nothing should be done with the current character
		// and we should pass.
		// m_ActiveMenu = ActiveMenuState::PASS;
	}
}

void Ui::Draw() {
	// TODO: the entities' hp will stay here for now.
	// We know that entities have health;
	// so all entities should have their health drawn on screen.
	if (m_SelectedEntity != NULL) {
		Color color = m_SelectedEntity->GetEntityType() == EntityType::Enemy ? RED : GREEN;

		Vector2 entityPos = m_SelectedEntity->GetPosition();
		Rectangle rec = m_SelectedEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, color);
		
		// Draw the entity's name.
		const char* entityName = m_SelectedEntity->GetName();

		Vector2 textSize = MeasureTextEx(m_Font, entityName, m_DefaultFontSize, m_DefaultFontSpacing);
		
		Vector2 entityInfoPos = {
			static_cast<float>((entityPos.x + (rec.width / 2)) - (textSize.x / 2)),
			entityPos.y - 90.0f };

		DrawTextEx(m_Font,
			entityName,
			entityInfoPos,
			m_DefaultFontSize,
			m_DefaultFontSpacing,
			WHITE);

		Rectangle emptyBarRectangle = { 
			0.0f,
			0.0f,
			static_cast<float>(m_EmptyHealthBarTexture2D.width),
			static_cast<float>(m_EmptyHealthBarTexture2D.height / 4.0f)
		};

		entityInfoPos.x =
			static_cast<float>(entityPos.x + (rec.width / 2)) - static_cast<float>((m_EmptyHealthBarTexture2D.width / 2));
		entityInfoPos.y -= 10.0f;

		DrawHpBar(m_SelectedEntity, rec, entityInfoPos);
	}

	if (m_HoveringEntity != NULL && m_SelectedEntity != m_HoveringEntity) {
		Vector2 entityPos = m_HoveringEntity->GetPosition();
		Rectangle rec = m_HoveringEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, BLACK);

		// Draw the entity's name.
		const char* entityName = m_HoveringEntity->GetName();

		Vector2 textSize = MeasureTextEx(m_Font, entityName, m_DefaultFontSize, m_DefaultFontSpacing);

		Vector2 entityInfoPos = { 
			static_cast<float>((entityPos.x + (rec.width / 2)) - (textSize.x / 2)),
			entityPos.y - 90.0f };

		DrawTextEx(m_Font,
			entityName,
			entityInfoPos,
			m_DefaultFontSize,
			m_DefaultFontSpacing,
			WHITE);

		entityInfoPos.x =
			static_cast<float>(entityPos.x + (rec.width / 2)) - static_cast<float>((m_EmptyHealthBarTexture2D.width / 2));
		entityInfoPos.y -= 10.0f;

		DrawHpBar(m_HoveringEntity, rec, entityInfoPos);
	}

	DrawContextMenu();

	// Creating the mouse cursor
	Vector2 mouseCursorTrianglePoint = { m_CursorPosition.x, m_CursorPosition.y };
	Vector2 mouseCursorTrianglePoint2 = { m_CursorPosition.x, m_CursorPosition.y + 15 };
	Vector2 mouseCursorTrianglePoint3 = { m_CursorPosition.x + 10, m_CursorPosition.y + 10 };

	// Drawing mouse cursor. It should be always drawn after everything, so it stays
	// on top of all the game's content.
	DrawTriangle(
		mouseCursorTrianglePoint,
		mouseCursorTrianglePoint2,
		mouseCursorTrianglePoint3,
		BLACK);
}

void Ui::DrawHpBar(Entity* entity, Rectangle entityRectangle, Vector2 position) const {
	Rectangle emptyBarRectangle = {
		0.0f,
		0.0f,
		static_cast<float>(m_EmptyHealthBarTexture2D.width),
		static_cast<float>(m_EmptyHealthBarTexture2D.height / 4)
	};

	Rectangle healthBarRectangle = {
	0.0f,
	0.0f,
	static_cast<float>(Clamp(entity->GetHealthPoints(), 0, 98)),
	static_cast<float>(m_HealthBarTexture2D.height / 4)
	};

	DrawTextureRec(m_EmptyHealthBarTexture2D, emptyBarRectangle, position, WHITE);
	DrawTextureRec(m_HealthBarTexture2D, healthBarRectangle, position, WHITE);
}
