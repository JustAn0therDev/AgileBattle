#include <stdlib.h>
#include <raylib.h>
#include <vector>
#include "Entity.hpp"
#include "Ui.hpp"
#include "BattleScene.hpp"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr int MAX_ENTITIES = 10;

int main(void) {
	InitWindow(WIDTH, HEIGHT, "Agile Battle");

	HideCursor();

	SetTargetFPS(60);

	BattleScene battleScene;

	while (!WindowShouldClose()) {

		// TODO: this should be handled by an auxiliary class.
		if (IsKeyPressed(KEY_F)) {
			ToggleFullscreen();
		}

		BeginDrawing();

		ClearBackground(WHITE);

		battleScene.Update();

		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}