#include "Ui.hpp"
#include "Animation.hpp"

Ui::Ui() : m_CursorPosition({ 0.0f, 0.0f })
{
	m_Font = LoadFontEx("Assets\\Fonts\\Cloude_Regular_Bold_1.03.otf", 72, 0, 256);
	m_SelectedEntity = NULL;
	m_HoveringEntity = NULL;
	m_UpperTextBoxHeightLimit = 570.0f;
	m_LowerTextBoxHeightLimit = 794.0f;
	m_TextBoxWidthLimit = 35.0f;
	m_DefaultFontSize = 72.0f;
	m_DefaultFontSpacing = 2.0f;
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
	if (m_SelectedEntity != NULL) {
		Color color = m_SelectedEntity->GetEntityType() == EntityType::Enemy ? RED : GREEN;

		Vector2 entityPos = m_SelectedEntity->GetPosition();
		Rectangle rec = m_SelectedEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, color);
		
		const char* entityName = m_SelectedEntity->GetName();

		Vector2 textSize = MeasureTextEx(m_Font, entityName, m_DefaultFontSize, m_DefaultFontSpacing);
		
		Vector2 entityNamePos = {
			static_cast<float>((entityPos.x + (rec.width / 2)) - (textSize.x / 2)),
			entityPos.y - 90.0f };

		DrawTextEx(m_Font,
			entityName,
			entityNamePos,
			m_DefaultFontSize,
			m_DefaultFontSpacing,
			WHITE);
	}

	if (m_HoveringEntity != NULL && m_SelectedEntity != m_HoveringEntity) {
		Vector2 entityPos = m_HoveringEntity->GetPosition();
		Rectangle rec = m_HoveringEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, BLACK);

		const char* entityName = m_HoveringEntity->GetName();

		Vector2 textSize = MeasureTextEx(m_Font, entityName, m_DefaultFontSize, m_DefaultFontSpacing);

		Vector2 entityNamePos = { 
			static_cast<float>((entityPos.x + (rec.width / 2)) - (textSize.x / 2)),
			entityPos.y - 90.0f };

		DrawTextEx(m_Font,
			entityName,
			entityNamePos,
			m_DefaultFontSize,
			m_DefaultFontSpacing,
			WHITE);
	}

	m_CursorPosition = GetMousePosition();

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
