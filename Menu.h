#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

using namespace sf;

class Menu
{
public:
	Menu();
	~Menu();

	void drawMenu(RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif
