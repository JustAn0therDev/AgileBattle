#pragma once
#include <raylib.h>
#include "AnimationType.hpp"

class Animation {
private:
	int m_FrameSpeed;
	int m_FrameCount;
	int m_CurrentFrame;
	int m_FrameCounter;
	bool m_PlayedAnimationOnce;
	Rectangle m_FrameRectangle;
	Texture2D m_TextureImage;
	Vector2 m_Position;
	AnimationType m_AnimationType;
public:
	Animation() = default;
	Animation(
		Vector2 position, 
		int frameSpeed, 
		int frameCount, 
		Texture2D textureImage,
		AnimationType animationType);

	void Update(Color color);
	Rectangle GetAnimationRectangle() const;

	bool PlayedAnimationOnce() const;
	AnimationType GetAnimationType() const;
	void ResetState();

	~Animation();
};
