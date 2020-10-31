#pragma once

#include <SFML/Graphics.hpp>
class Bullet {
public:
	Bullet(sf::Vector2f size);
//---------------------------------------
	void fire(int speed);
	void draw(sf::RenderWindow& window);
	void setPos(sf::Vector2f newPos);
//---------------------------------
	int getRight();
	int getLeft();
	int getTop();
	int getBottom();
	void setbullets(bool b) { bullets = b; }

private:
	sf::RectangleShape bullet;
	bool bullets;

};