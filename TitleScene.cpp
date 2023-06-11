#include "TitleScene.hpp"
#include "Constants.hpp"
#include <string>
#include <fstream>

void TitleScene::Update()
{
	m_Ui.Update(NULL);

	const Font font = m_Ui.GetFont();

	std::string titleText = "Agile Battle!";

	std::string enterToBeginInstructionText = "Pressione enter para iniciar";

	Vector2 titleTextPos = { (Constants::DEFAULT_WIDTH / 2) - 90, (Constants::DEFAULT_HEIGHT / 2) - 36 };

	Vector2 enterToBeginInstructionTextPos = { 
	  (Constants::DEFAULT_WIDTH / 2) - 210,
	  (Constants::DEFAULT_HEIGHT / 2) + 30
	};

	DrawTextEx(font,
		titleText.c_str(),
		titleTextPos,
		72,
		2,
		BLACK);

	DrawTextEx(font,
		enterToBeginInstructionText.c_str(),
		enterToBeginInstructionTextPos,
		72,
		2,
		BLACK);
}
