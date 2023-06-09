#pragma once
#include <raylib.h>

class Animation {
private:
	int m_FrameSpeed;
	int m_FrameCount;
	int m_CurrentFrame;
	int m_FrameCounter;
	Rectangle m_FrameRectangle;
	Texture2D m_TextureImage;
	Vector2 m_Position;
public:
	Animation() = default;
	Animation(Vector2 position, int frameSpeed, int frameCount, Texture2D textureImage);

	void Update();
	Rectangle GetAnimationRectangle();

	~Animation();
};
