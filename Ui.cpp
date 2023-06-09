#include "Ui.hpp"

Ui::Ui() : m_CursorPosition({ 0.0f, 0.0f })
{

}

Vector2 Ui::GetCursorPosition()
{
	return m_CursorPosition;
}

bool Ui::IsCursorOn(Vector2 pos, Rectangle entityAreaRec) 
{
	return
		m_CursorPosition.x >= pos.x &&
		m_CursorPosition.x <= (pos.x + entityAreaRec.width) &&
		m_CursorPosition.y >= pos.y &&
		m_CursorPosition.y <= (pos.y + entityAreaRec.height);
}

void Ui::Update()
{
	m_CursorPosition = GetMousePosition();

	// Creating the mouse cursor
	Vector2 trianglePoint = { m_CursorPosition.x, m_CursorPosition.y };
	Vector2 trianglePoint2 = { m_CursorPosition.x, m_CursorPosition.y + 15 };
	Vector2 trianglePoint3 = { m_CursorPosition.x + 10, m_CursorPosition.y + 10 };

	// Drawing mouse cursor
	DrawTriangle(trianglePoint, trianglePoint2, trianglePoint3, BLACK);
}
