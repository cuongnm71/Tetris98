#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Menu.h"
#include "Score.h"

using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{
    int x,y;
} tetro[4], illu[4];

int figures[7][4] =
{
	4,9,14,19,
	3,8,9,14,
	4,9,8,13,
	3,8,9,13,
	3,4,9,14,
	4,9,14,13,
	3,4,8,9,
};

bool check()
{
    for (int i = 0; i < 4; i++)
        if (tetro[i].x < 0 || tetro[i].x >= N || tetro[i].y >= M)
            return 0;
        else if (field[tetro[i].y][tetro[i].x])
            return 0;
    return 1;
};

bool isGameOver()
{
    for (int i = 0; i < N; i++)
        if(field[0][i]) return true;
    return false;
}

int main()
{
    srand(time(0));

	RenderWindow window(VideoMode(535, 535), "Tetris");

    // Load menu game
	Menu menu;

	while (window.isOpen())
	{
		Event e1;
		while (window.pollEvent(e1))
		{
			switch (e1.type)
			{
			case Event::KeyReleased:
				switch (e1.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;

				case Keyboard::Return:
					switch (menu.GetPressedItem())
					{
                        case 0: // Normal Mode
                        {
                            window.clear();

                            int score = 0;
                            float level = 0;
                            Score score0;
                            score0.updateScoreNormalMode(score, level);

                            // Load images
                            Texture t1, t2;
                            if (!t1.loadFromFile("images/background.png")) return -1;
                            if(!t2.loadFromFile("images/tiles.png")) return -2;
                            Sprite background(t1), s(t2);

                            // Initialize
                            bool gamePlay = true;
                            int move = 0;
                            bool rotate = 0;
                            float timer = 0, delay = 1;
                            Clock clock;

                            // Random for first Tetromino
                            int colorNum = 1 + rand()%7;
                            int n = colorNum - 1;
                            for (int i = 0; i < 4; i++)
                            {
                                tetro[i].x = figures[n][i] % 5;
                                tetro[i].y = figures[n][i] / 5;
                            }

                            // Main game loop
                            while (gamePlay)
                            {
                                float time = clock.getElapsedTime().asSeconds();
                                clock.restart();
                                timer += time;

                                Event e2;
                                while (window.pollEvent(e2))
                                {
                                    if (e2.type == Event::Closed)
                                        {
                                            window.close();
                                            return 0;
                                        }

                                    if (e2.type == Event::KeyPressed)
                                        if (e2.key.code == Keyboard::Up) rotate = true;
                                        else if (e2.key.code == Keyboard::Left) move = -1;
                                        else if (e2.key.code == Keyboard::Right) move = 1;
                                }

                                if ( Keyboard::isKeyPressed( Keyboard::Key::F10 ) )
                                {
                                    Image screenshot = window.capture();
                                    screenshot.saveToFile( "screenshotNormalMode.png" );
                                }
                                if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.005 * (10 - level);

                                // Move
                                for (int i = 0; i < 4; i++)
                                {
                                    illu[i] = tetro[i];
                                    tetro[i].x += move;
                                }
                                if (!check())
                                    for (int i = 0; i < 4; i++)
                                        tetro[i] = illu[i];

                                // Rotate
                                // Choose tetro[1] to be the center of the rotation
                                if (rotate == true && n != 6)
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        int x = tetro[i].y - tetro[1].y;
                                        int y = tetro[i].x - tetro[1].x;
                                        tetro[i].x = tetro[1].x - x;
                                        tetro[i].y = tetro[1].y + y;
                                    }
                                    if (!check())
                                        for (int i = 0; i < 4; i++)
                                            tetro[i] = illu[i];
                                }

                                // Drop
                                if (timer > delay)
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        illu[i] = tetro[i];
                                        tetro[i].y ++;
                                    }

                                    if (!check())
                                    {
                                        for (int i = 0; i < 4; i++)
                                            field[illu[i].y][illu[i].x] = colorNum;

                                        colorNum = 1 + rand()%7;
                                        n = colorNum - 1;
                                        for (int i = 0; i < 4; i++)
                                        {
                                            tetro[i].x = figures[n][i] % 5;
                                            tetro[i].y = figures[n][i] / 5;
                                        }
                                    }
                                    timer = 0;
                                }

                                if (!isGameOver())
                                {
                                    // Check lines
                                    int k = M - 1, countLineDeleted = 0;
                                    for (int i = M - 1; i > 0; i--)
                                    {
                                        int count = 0;
                                        for (int j = 0; j < N; j++)
                                        {
                                            if (field[i][j])
                                                count++;
                                            field[k][j] = field[i][j];
                                        }
                                        if (count < N)
                                            k--;
                                        else if (count == N)
                                        {
                                            countLineDeleted++;
                                        }
                                    }
                                    if (countLineDeleted == 1)      score += 40 * (level + 1);
                                    else if (countLineDeleted == 2) score += 100 * (level + 1);
                                    else if (countLineDeleted == 3) score += 300 * (level + 1);
                                    else if (countLineDeleted == 4)    score += 1200 * (level + 1);
                                    level = score / 1000;
                                    score0.updateScoreNormalMode(score, level);

                                    // Draw background
                                    window.clear();
                                    window.draw(background);

                                    // Draw stand still Tetrominos
                                    for (int i = 0; i < M; i++)
                                        for (int j = 0; j < N; j++)
                                        {
                                            if (field[i][j] == 0)
                                                continue;
                                            s.setTextureRect(IntRect(field[i][j]*20, 0, 20, 20));
                                            s.setPosition(j*20, i*20);
                                            s.move(135, 65);
                                            window.draw(s);
                                        }

                                    // Draw new Tetromino
                                    for (int i = 0; i < 4; i++)
                                    {
                                        s.setTextureRect(IntRect(colorNum*20, 0, 20, 20));
                                        s.setPosition(tetro[i].x*20, tetro[i].y*20);
                                        s.move(135, 65);
                                        window.draw(s);
                                    }
                                    score0.drawScore(window);
                                    window.display();

                                    // Refresh
                                    move = 0;
                                    rotate = 0;
                                    delay = 0.1 * (10 - level);
                                }
                                else
                                {
                                    Texture t3;
                                    if(!t3.loadFromFile("images/retry.png")) return  -3;
                                    Sprite retry(t3);

                                    Event e3;
                                    while (window.pollEvent(e3))
                                    {
                                        if (e3.type == Event::Closed)
                                            {
                                                window.close();
                                                return 0;
                                            }

                                        if (e3.type == Event::KeyPressed)
                                            if (e3.key.code == Keyboard::Escape)
                                            {
                                                window.close();
                                                return 0;
                                            }
                                    }

                                    retry.setPosition(133, 205);
                                    window.draw(retry);
                                    window.display();
                                }
                            }
                            break;
                        }
                        case 1:
                        {
                            window.clear();

                            int score = 0, level = 0;
                            Score score0;
                            score0.updateScoreBlindMode(score, level);

                            // Load images
                            Texture t1, t2;
                            if (!t1.loadFromFile("images/background.png")) return -1;
                            if(!t2.loadFromFile("images/tiles.png")) return -2;
                            Sprite background(t1), s(t2);

                            // Initialize
                            bool gamePlay = true;
                            int move = 0;
                            bool rotate = 0;
                            float timer = 0, delay = 1;
                            Clock clock;

                            // Random for first Tetromino
                            int colorNum = 1 + rand()%7;
                            int n = colorNum - 1;
                            for (int i = 0; i < 4; i++)
                            {
                                tetro[i].x = figures[n][i] % 5;
                                tetro[i].y = figures[n][i] / 5;
                            }

                            // Main game loop
                            while (gamePlay)
                            {
                                float time = clock.getElapsedTime().asSeconds();
                                clock.restart();
                                timer += time;

                                Event e2;
                                while (window.pollEvent(e2))
                                {
                                    if (e2.type == Event::Closed)
                                        {
                                            window.close();
                                            return 0;
                                        }

                                    if (e2.type == Event::KeyPressed)
                                        if (e2.key.code == Keyboard::Up) rotate = true;
                                        else if (e2.key.code == Keyboard::Left) move = -1;
                                        else if (e2.key.code == Keyboard::Right) move = 1;
                                }

                                if ( Keyboard::isKeyPressed( Keyboard::Key::F10 ) )
                                {
                                    Image screenshot = window.capture();
                                    screenshot.saveToFile("screenshotBlindMode.png");
                                }

                                if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.005 * (10 - level);

                                // Move
                                for (int i = 0; i < 4; i++)
                                {
                                    illu[i] = tetro[i];
                                    tetro[i].x += move;
                                }
                                if (!check())
                                    for (int i = 0; i < 4; i++)
                                        tetro[i] = illu[i];

                                // Rotate
                                // Choose tetro[1] to be the center of the rotation
                                if (rotate == true && n != 6)
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        int x = tetro[i].y - tetro[1].y;
                                        int y = tetro[i].x - tetro[1].x;
                                        tetro[i].x = tetro[1].x - x;
                                        tetro[i].y = tetro[1].y + y;
                                    }
                                    if (!check())
                                        for (int i = 0; i < 4; i++)
                                            tetro[i] = illu[i];
                                }

                                // Drop
                                if (timer > delay)
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        illu[i] = tetro[i];
                                        tetro[i].y ++;
                                    }

                                    if (!check())
                                    {
                                        for (int i = 0; i < 4; i++)
                                            field[illu[i].y][illu[i].x] = colorNum;

                                        colorNum = 1 + rand()%7;
                                        n = colorNum - 1;
                                        for (int i = 0; i < 4; i++)
                                        {
                                            tetro[i].x = figures[n][i] % 5;
                                            tetro[i].y = figures[n][i] / 5;
                                        }
                                    }
                                    timer = 0;
                                }

                                if (!isGameOver())
                                {
                                   // Check lines
                                    int k = M - 1, countLineDeleted = 0;
                                    for (int i = M - 1; i > 0; i--)
                                    {
                                        int count = 0;
                                        for (int j = 0; j < N; j++)
                                        {
                                            if (field[i][j])
                                                count++;
                                            field[k][j] = field[i][j];
                                        }
                                        if (count < N)
                                            k--;
                                        else if (count == N)
                                        {
                                            countLineDeleted++;
                                        }
                                    }
                                    if (countLineDeleted == 1)      score += 40 * (level + 1);
                                    else if (countLineDeleted == 2) score += 100 * (level + 1);
                                    else if (countLineDeleted == 3) score += 300 * (level + 1);
                                    else if (countLineDeleted == 4)    score += 1200 * (level + 1);
                                    level = score / 1000;
                                    score0.updateScoreBlindMode(score, level);

                                    // Draw background
                                    window.clear();
                                    window.draw(background);

                                    // Draw stand still Tetrominos
                                    for (int i = 0; i < M; i++)
                                        for (int j = 0; j < N; j++)
                                        {
                                            if (field[i][j] == 0)
                                                continue;
                                            s.setTextureRect(IntRect(field[i][j]*20, 0, 20, 20));
                                            s.setPosition(j*20, i*20);
                                            s.move(135, 65);
                                        }

                                    // Draw new Tetromino
                                    for (int i = 0; i < 4; i++)
                                    {
                                        s.setTextureRect(IntRect(colorNum*20, 0, 20, 20));
                                        s.setPosition(tetro[i].x*20, tetro[i].y*20);
                                        s.move(135, 65);
                                        window.draw(s);
                                    }
                                    score0.drawScore(window);
                                    window.display();

                                    // Refresh
                                    move = 0;
                                    rotate = 0;
                                    delay = 0.1 * (10 - level);
                                }
                                else
                                {
                                    Texture t3;
                                    if(!t3.loadFromFile("images/retry.png")) return  -3;
                                    Sprite retry(t3);

                                    Event e3;
                                    while (window.pollEvent(e3))
                                    {
                                        if (e3.type == Event::Closed)
                                            {
                                                window.close();
                                                return 0;
                                            }

                                        if (e3.type == Event::KeyPressed)
                                            if (e3.key.code == Keyboard::Escape)
                                            {
                                                window.close();
                                                return 0;
                                            }
                                    }

                                    retry.setPosition(133, 205);
                                    window.draw(retry);
                                    window.display();
                                }
                            }
                            break;
                        }
                        case 2:
                        {
                            window.close();
                            return 0;
                        }
					}
					break;
				}
				break;
			case Event::Closed:
				{
                    window.close();
                    return 0;
                }
			}
		}
        //Draw button start game
		window.clear();
        menu.drawMenu(window);
		window.display();

	}
	return 0;
}
