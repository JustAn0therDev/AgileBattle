#include <stdlib.h>
#include <raylib.h>
#include <vector>
#include "Entity.hpp"
#include "Ui.hpp"
#include "BattleScene.hpp"
#include "Constants.hpp"
#include "TitleScene.hpp"
#include <clocale>

int main(void) {
	InitWindow(Constants::DEFAULT_WIDTH, Constants::DEFAULT_HEIGHT, "Agile Battle");

	HideCursor();

	SetTargetFPS(60);

	bool triggredBattleScene = false;

	TitleScene* titleScene = new TitleScene();

	BattleScene* battleScene = NULL;

	while (!WindowShouldClose()) {
		// TODO: this should be handled by an auxiliary class.
		if (IsKeyPressed(KEY_F)) {
			ToggleFullscreen();
		}

		BeginDrawing();

		ClearBackground(WHITE);

		if (IsKeyPressed(KEY_ENTER) && !triggredBattleScene) {
			battleScene = new BattleScene();
			triggredBattleScene = true;
			delete titleScene;
			titleScene = NULL;
		}

		if (titleScene != NULL) {
			titleScene->Update();
		}
		else if (battleScene != NULL) {
			battleScene->Update();
		}


		EndDrawing();
	}

	if (battleScene != NULL) {
		delete battleScene;
	}

	CloseWindow();

	return EXIT_SUCCESS;
}