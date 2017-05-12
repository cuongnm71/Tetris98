#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Score
{
public:
	Score();
	~Score();

	void drawScore(RenderWindow &window);
	void updateScoreNormalMode(int score, int level);
	void updateScoreBlindMode(int score, int level);

private:
	Font font;
	Text __score[3];
};

#endif
