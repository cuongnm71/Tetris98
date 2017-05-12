#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "Score.h"

using namespace sf;

Score::Score()
{
	if (!font.loadFromFile("font/animeace2_reg.ttf"))
	{
		// handle error
	}

	__score[0].setFont(font);
	__score[0].setColor(Color::White);
	__score[0].setCharacterSize(12);
	__score[0].setPosition(350, 247);

	__score[1].setFont(font);
	__score[1].setColor(Color::White);
	__score[1].setCharacterSize(12);
	__score[1].setPosition(350, 335);

	__score[2].setFont(font);
	__score[2].setColor(Color::White);
	__score[2].setCharacterSize(12);
	__score[2].setPosition(350, 420);
}

Score::~Score()
{
}

void Score::drawScore(RenderWindow &window)
{
    for (int i = 0; i < 3; i++)
		window.draw(__score[i]);
}

void Score::updateScoreNormalMode(int score, int level)
{
    std::ifstream _highscore ("highscore_normalmode.txt");
    int highscore;
    if(_highscore.is_open())
    {
        _highscore >> highscore;
        _highscore.close();
    }
    std::ofstream __highscore ("highscore_normalmode.txt");
    if(__highscore.is_open())
    {
        if (score > highscore)
            highscore = score;
            __highscore << highscore;
        __highscore.close();
    }

    std::stringstream _Score, _HighScore, _Level;

    _Score << score;
    _HighScore << highscore;
    _Level << level;

    __score[0].setString(_HighScore.str().c_str());
    __score[1].setString(_Score.str().c_str());
    __score[2].setString(_Level.str().c_str());
}

void Score::updateScoreBlindMode(int score, int level)
{
    std::ifstream _highscore ("highscore_blindmode.txt");
    int highscore;
    if(_highscore.is_open())
    {
        _highscore >> highscore;
        _highscore.close();
    }
    std::ofstream __highscore ("highscore_blindmode.txt");
    if(__highscore.is_open())
    {
        if (score > highscore)
            highscore = score;
            __highscore << highscore;
        __highscore.close();
    }

    std::stringstream _Score, _HighScore, _Level;

    _Score << score;
    _HighScore << highscore;
    _Level << level;

    __score[0].setString(_HighScore.str().c_str());
    __score[1].setString(_Score.str().c_str());
    __score[2].setString(_Level.str().c_str());
}


