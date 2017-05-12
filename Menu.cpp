#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace sf;

Menu::Menu()
{
	if (!font.loadFromFile("font/animeace2_reg.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setColor(Color::Red);
	menu[0].setString("Normal");
	menu[0].setCharacterSize(24);
	menu[0].setPosition(202, 365);

	menu[1].setFont(font);
	menu[1].setColor(Color::White);
	menu[1].setString("Blind");
	menu[1].setCharacterSize(24);
	menu[1].setPosition(222, 418);

	menu[2].setFont(font);
	menu[2].setColor(Color::White);
	menu[2].setString("Quit");
	menu[2].setCharacterSize(24);
	menu[2].setPosition(230, 470);
	selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(Color::Red);
	}
}

void Menu::drawMenu(RenderWindow &window)
{
    Texture t1, t2;
    t1.loadFromFile("images/start.jpg");
    t2.loadFromFile("images/button.png");
    Sprite start(t1), button(t2);
    window.draw(start);
    button.setPosition(187, 357);
    window.draw(button);
    button.setPosition(187, 410);
    window.draw(button);
    button.setPosition(187, 463);
    window.draw(button);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		window.draw(menu[i]);
}
