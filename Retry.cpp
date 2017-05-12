#include <SFML/Graphics.hpp>
#include "Retry.h"

using namespace sf;

Retry::Retry()
{
	if (!font.loadFromFile("font/animeace2_reg.ttf"))
	{
		// handle error
	}

	retry[0].setFont(font);
	retry[0].setColor(Color::Red);
	retry[0].setString("Yes");
	retry[0].setCharacterSize(24);
	retry[0].setPosition(202, 365);

	retry[1].setFont(font);
	retry[1].setColor(Color::White);
	retry[1].setString("No");
	retry[1].setCharacterSize(24);
	retry[1].setPosition(222, 418);

	selectedItemIndex = 0;
}

Retry::~Retry()
{
}

void Retry::MoveLeft()
{
	if (selectedItemIndex - 1 >= 0)
	{
		retry[selectedItemIndex].setColor(Color::White);
		selectedItemIndex--;
		retry[selectedItemIndex].setColor(Color::Red);
	}
}

void Retry::MoveRight()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		retry[selectedItemIndex].setColor(Color::White);
		selectedItemIndex++;
		retry[selectedItemIndex].setColor(Color::Red);
	}
}

void Retry::drawRetry(RenderWindow &window)
{
    Texture t1, t2;
    t1.loadFromFile("images/retry.png");
    t2.loadFromFile("images/button.png");
    Sprite Retry(t1), button(t2);
    window.draw(Retry);
    Retry.setPosition(187, 357);
    window.draw(button);
    button.setPosition(187, 410);
    window.draw(button);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(retry[i]);
	}
}
