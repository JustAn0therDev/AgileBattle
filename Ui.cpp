#include "Ui.hpp"
#include "Animation.hpp"
#include <string>
#include <raymath.h>

Rectangle Ui::GetHealthBarRectangleByEntityHealth(float entityHealth) const {
	Rectangle healthBarRectangle = { 
		0.0f,
		0.0f,
		Clamp(entityHealth, 0, 98),
		m_HealthBarTexture2D.height / 4
	};

	return healthBarRectangle;
}

Ui::Ui() : m_CursorPosition({ 0.0f, 0.0f })
{
	m_Font = LoadFontEx("Assets\\Fonts\\Cloude_Regular_Bold_1.03.otf", 72, 0, 256);
	m_SelectedEntity = NULL;
	m_HoveringEntity = NULL;
	m_UpperTextBoxHeightLimit = 590.0f;
	m_LowerTextBoxHeightLimit = 794.0f;
	m_TextBoxWidthLimit = 35.0f;
	m_DefaultFontSize = 72.0f;
	m_DefaultFontSpacing = 2.0f;
	m_HealthBarTexture2D = LoadTexture("Assets\\Images\\Health\\health_bar.png");
	m_EmptyHealthBarTexture2D = LoadTexture("Assets\\Images\\Health\\empty_bar.png");
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
			else if (!isCursorOn && entity == m_SelectedEntity) {
				m_SelectedEntity = NULL;
			}
		}
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

		// Draw the entity's health bar.
		// Both bars have to be drawn at the same position;
		// The empty bar should always be BEHIND (drawn first)
		// As health gets lower, the original health bar should have
		// only parts of it being drawn.
		// TODO: this position might have to be adjusted.
		Rectangle emptyBarRectangle = { 
			0.0f,
			0.0f,
			m_EmptyHealthBarTexture2D.width,
			m_EmptyHealthBarTexture2D.height / 4
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

	std::string actionText = "Atacar";
	std::string arrow = "->";

	// TODO: all this code down here is just a test
	Vector2 actionTextPos = { m_TextBoxWidthLimit, m_UpperTextBoxHeightLimit };
	Vector2 actionTextSize = MeasureTextEx(m_Font, "Atacar", m_DefaultFontSize, m_DefaultFontSpacing);
	Rectangle rec = { 0.0f, 0.0f, actionTextSize.x, actionTextSize.y };

	if (IsCursorOn(actionTextPos, rec)) {
		DrawRectangleLines((int)actionTextPos.x, (int)actionTextPos.y, (int)rec.width, (int)rec.height, WHITE);
		DrawTextEx(m_Font, arrow.append(actionText).c_str(), actionTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
	}
	else {
		DrawTextEx(m_Font, actionText.c_str(), actionTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
	}

	actionTextPos.y += 50;

	DrawTextEx(m_Font, "Atacar", actionTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);

	actionTextPos.y += 50;

	DrawTextEx(m_Font, "Atacar", actionTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);

	// Creating the mouse cursor
	Vector2 mouseCursorTrianglePoint = { m_CursorPosition.x, m_CursorPosition.y };
	Vector2 mouseCursorTrianglePoint2 = { m_CursorPosition.x, m_CursorPosition.y + 15 };
	Vector2 mouseCursorTrianglePoint3 = { m_CursorPosition.x + 10, m_CursorPosition.y + 10 };

	// Drawing mouse cursor
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
		m_EmptyHealthBarTexture2D.width,
		m_EmptyHealthBarTexture2D.height / 4
	};

	Rectangle healthBarRectangle = GetHealthBarRectangleByEntityHealth(entity->GetHealthPoints());

	DrawTextureRec(m_EmptyHealthBarTexture2D, emptyBarRectangle, position, WHITE);
	DrawTextureRec(m_HealthBarTexture2D, healthBarRectangle, position, WHITE);
}
