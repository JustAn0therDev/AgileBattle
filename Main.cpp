#include <stdlib.h>
#include <raylib.h>
#include <vector>
#include "Entity.hpp"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr int MAX_ENTITIES = 10;

int main(void) {
	InitWindow(WIDTH, HEIGHT, "Agile Battle");

	HideCursor();

	SetTargetFPS(60);

	Ui ui;

	std::vector<Entity*> entities;

	Texture2D deathAnimationTextureImage = LoadTexture("Assets/GolemDefeated.png");
	Vector2 pos = { static_cast<float>((WIDTH / 2) - ((deathAnimationTextureImage.width / 4) / 2)), static_cast<float>((HEIGHT / 2) - deathAnimationTextureImage.height / 2) };

	Animation deathAnimation(pos, 4, 4, deathAnimationTextureImage);

	Entity golem(10.0f, pos, NULL, &deathAnimation, NULL, NULL);
	golem.ChangeCurrentAnimation("Death");

	entities.push_back(&golem);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] != NULL) {
				entities[i]->Update(entities, ui);
			}
		}

		ui.Update();

		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}