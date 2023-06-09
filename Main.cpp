#include <stdlib.h>
#include <raylib.h>
#include <vector>
#include "Entity.hpp"
#include "Ui.hpp"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr int MAX_ENTITIES = 10;

int main(void) {
	InitWindow(WIDTH, HEIGHT, "Agile Battle");

	HideCursor();

	SetTargetFPS(60);

	Ui ui;
	std::vector<Entity*> entities;

	Texture2D deathAnimationTextureImage =
		LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Golem\\GolemDefeated.png");
	
	Vector2 entityPos = { 
		static_cast<float>((WIDTH / 2) - ((deathAnimationTextureImage.width / 4) / 2)), 
		static_cast<float>((HEIGHT / 2) - deathAnimationTextureImage.height / 2) 
	};

	Animation deathAnimation(entityPos, 4, 4, deathAnimationTextureImage);

	Entity golem(10.0f, entityPos, NULL, &deathAnimation, NULL, NULL);
	golem.ChangeCurrentAnimation("Death");

	Texture2D textureDino
		= LoadTexture("D:\\repos\\AgileBattle\\Assets\\Images\\Dino\\DinoSprites - doux.png");

	Vector2 entityPosDino = {
		static_cast<float>((WIDTH / 3) - ((textureDino.width / 24) / 2)),
		static_cast<float>((HEIGHT / 2) - textureDino.height / 2)
	};

	Animation dinoAnimation(entityPosDino, 24, 24, textureDino);

	Entity dino(10.0f, entityPosDino, &dinoAnimation, NULL, NULL, NULL);
	dino.ChangeCurrentAnimation("Idle");

	entities.push_back(&dino);
	entities.push_back(&golem);

	while (!WindowShouldClose()) {

		// TODO: this should be handled by an auxiliary class.
		if (IsKeyPressed(KEY_F)) {
			ToggleFullscreen();
		}

		BeginDrawing();

		ClearBackground(WHITE);

		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] != NULL) {
				entities[i]->Update(entities);
				ui.Update(entities[i]);
			}
		}

		ui.Draw();

		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}