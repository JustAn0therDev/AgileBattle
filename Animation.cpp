#include "Animation.hpp"

Animation::Animation(Vector2 position, int frameSpeed, int frameCount, Texture2D textureImage) {
	m_FrameSpeed = frameSpeed;
	m_FrameCount = frameCount;
	m_CurrentFrame = 1;
	m_FrameCounter = 0;
	m_TextureImage = textureImage;
	m_FrameRectangle = {
		0.0f,
		0.0f,
		static_cast<float>(textureImage.width / frameCount),
		static_cast<float>(textureImage.height)
	};
	m_Position = position;
}

void Animation::Update() {
	m_FrameCounter++;

	if (m_FrameCounter >= (60 / m_FrameSpeed)) {
		m_FrameCounter = 0;

		if (m_CurrentFrame > m_FrameCount) {
			m_CurrentFrame = 1;
		}
		else {
			m_CurrentFrame++;
		}

		m_FrameRectangle.x = static_cast<float>(m_CurrentFrame) * static_cast<float>(m_TextureImage.width / m_FrameCount);
	}

	Rectangle rec = { 0.0f, 0.0f, m_TextureImage.width / m_FrameCount, m_TextureImage.height };

	Vector2 mousePosition = GetMousePosition();

	bool mouseInRect =
		mousePosition.x >= m_Position.x &&
		mousePosition.x <= (m_Position.x + rec.width) &&
		mousePosition.y >= m_Position.y &&
		mousePosition.y <= (m_Position.y + rec.height);

	if (mouseInRect) {
		DrawRectangle(m_Position.x, m_Position.y, rec.width, rec.height, BLUE);
	}
	else {
		DrawRectangleLines(m_Position.x, m_Position.y, rec.width, rec.height, BLACK);
	}

	DrawTextureRec(m_TextureImage, m_FrameRectangle, m_Position, WHITE);

	// Creating the mouse cursor
	Vector2 trianglePoint = { mousePosition.x - 10, mousePosition.y - 10 };
	Vector2 trianglePoint2 = { mousePosition.x - 10, mousePosition.y + 10 };
	Vector2 trianglePoint3 = { mousePosition.x + 6, mousePosition.y + 5 };

	// Drawing mouse cursor
	DrawTriangle(trianglePoint, trianglePoint2, trianglePoint3, BLACK);
}

Animation::~Animation() {
	UnloadTexture(m_TextureImage);
}