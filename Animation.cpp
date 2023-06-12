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

	Rectangle rec = { 
		0.0f, 
		0.0f, 
		static_cast<float>(m_TextureImage.width / m_FrameCount), 
		static_cast<float>(m_TextureImage.height) };

	DrawTextureRec(m_TextureImage, m_FrameRectangle, m_Position, WHITE);
}

Rectangle Animation::GetAnimationRectangle() const
{
	return m_FrameRectangle;
}

Animation::~Animation() {
	UnloadTexture(m_TextureImage);
}