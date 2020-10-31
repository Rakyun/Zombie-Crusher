#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f size)
{
	bullet.setSize(size);
	bullet.setFillColor(sf::Color::Yellow);
	bullets = false;
	int clip = 30;
	int magazine = 90;
}

void Bullet::fire(int speed)
{
	bullet.move(speed, 0);
}

int Bullet::getRight() 
{
	return bullet.getPosition().x + bullet.getSize().x;
}

int Bullet::getLeft() 
{ 
	return bullet.getPosition().x;
}

int Bullet::getTop() 
{ 
	return bullet.getPosition().y; 
}

int Bullet::getBottom()
{ 
	return bullet.getPosition().y + bullet.getSize().y; 
}

void Bullet::draw(sf::RenderWindow& window) 
{ 
	if (bullets == false) {
		window.draw(bullet);
	}
}

void Bullet::setPos(sf::Vector2f newPos) 
{ 
	bullet.setPosition(newPos); 
}
