#ifndef RETRY_H
#define RETRY_H

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 2


using namespace sf;

class Retry
{
public:
	Retry();
	~Retry();

	void drawRetry(RenderWindow &window);
	void MoveLeft();
	void MoveRight();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	Font font;
	Text retry[MAX_NUMBER_OF_ITEMS];
};


#endif
