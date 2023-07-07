#include "Animation.hpp"

Animation::Animation(
	Vector2 position,
	int frameSpeed,
	int frameCount,
	Texture2D textureImage,
	AnimationType animationType) {
	m_FrameSpeed = frameSpeed;
	m_FrameCount = frameCount;
	m_CurrentFrame = 0;
	m_FrameCounter = 0;
	m_TextureImage = textureImage;
	m_FrameRectangle = {
		0.0f,
		0.0f,
		static_cast<float>(textureImage.width / frameCount),
		static_cast<float>(textureImage.height)
	};
	m_Position = position;
	m_PlayedAnimationOnce = false;
	m_AnimationType = animationType;
}

void Animation::Update(Color color) {
	m_FrameCounter++;

	if (m_FrameCounter >= (60 / m_FrameSpeed)) {
		m_FrameCounter = 0;

		if (m_CurrentFrame > m_FrameCount - 1) {
			if (m_AnimationType != AnimationType::Idle) {
				m_PlayedAnimationOnce = true;
			}

			m_CurrentFrame = 0;
		}
		else {
			m_CurrentFrame++;
		}

		m_FrameRectangle.x = static_cast<float>(m_CurrentFrame) * static_cast<float>(m_TextureImage.width / m_FrameCount);
	}

	DrawTextureRec(m_TextureImage, m_FrameRectangle, m_Position, color);
}

Rectangle Animation::GetAnimationRectangle() const
{
	return m_FrameRectangle;
}

bool Animation::PlayedAnimationOnce() const {
	return m_PlayedAnimationOnce;
}

AnimationType Animation::GetAnimationType() const {
	return m_AnimationType;
}

void Animation::ResetState()
{
	m_CurrentFrame = 0;
	m_FrameRectangle.x = 0;
	m_FrameCounter = 0;
	m_PlayedAnimationOnce = false;
}

Animation::~Animation() {
	UnloadTexture(m_TextureImage);
}