#include "TitleScene.hpp"
#include "Constants.hpp"
#include <string>
#include <fstream>

void TitleScene::Update()
{
	m_Ui.Update(NULL);

	const Font font = m_Ui.GetFont();

	const float fontSize = m_Ui.GetFontSize();
	
	const float fontSpacing = m_Ui.GetFontSpacing();

	const char* titleText = "Agile Battle!";

	const char* enterToBeginInstructionText = "Pressione enter ou clique para iniciar!";

	const char* pressFInstructionText = "Pressione a tecla F para deixar o jogo em tela cheia.";

	Vector2 titleTextSize = MeasureTextEx(font, titleText, fontSize, fontSpacing);

	Vector2 enterToBeginInstructionTextSize = MeasureTextEx(font, enterToBeginInstructionText, fontSize, fontSpacing);

	Vector2 pressFInstructionTextSize = MeasureTextEx(font, pressFInstructionText, fontSize - 24, fontSpacing);

	Vector2 titleTextPos = { (Constants::DEFAULT_WIDTH / 2) - (titleTextSize.x / 2), (Constants::DEFAULT_HEIGHT / 2) - (titleTextSize.y / 2) };

	Vector2 enterToBeginInstructionTextPos = { 
	  (Constants::DEFAULT_WIDTH / 2) - (enterToBeginInstructionTextSize.x / 2),
	  (Constants::DEFAULT_HEIGHT / 2) + (enterToBeginInstructionTextSize.y / 2)
	};

	Vector2 pressFInstructionTextPos = {
	  (Constants::DEFAULT_WIDTH / 2) - (pressFInstructionTextSize.x / 2),
	  (Constants::DEFAULT_HEIGHT / 2) + (pressFInstructionTextSize.y / 2) + 100.0f
	};

	DrawTextEx(font,
		titleText,
		titleTextPos,
		fontSize,
		fontSpacing,
		BLACK);

	DrawTextEx(font,
		enterToBeginInstructionText,
		enterToBeginInstructionTextPos,
		fontSize,
		fontSpacing,
		BLACK);

	DrawTextEx(font,
		pressFInstructionText,
		pressFInstructionTextPos,
		fontSize - 24,
		fontSpacing,
		BLACK);
}
