#include "Ui.hpp"
#include "Animation.hpp"

Ui::Ui() : m_CursorPosition({ 0.0f, 0.0f })
{
	m_SelectedEntity = NULL;
	m_HoveringEntity = NULL;
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

void Ui::Update(Entity* entity)
{
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
		Vector2 entityPos = m_SelectedEntity->GetPosition();
		Rectangle rec = m_SelectedEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, RED);
	}

	if (m_HoveringEntity != NULL && m_SelectedEntity != m_HoveringEntity) {
		Vector2 entityPos = m_HoveringEntity->GetPosition();
		Rectangle rec = m_HoveringEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, BLACK);
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
