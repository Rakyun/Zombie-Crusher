#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <time.h>  
#include <random>
#include "Animation.hpp"
#include "Bullet.hpp"

class Zombie 
{
public:
	Zombie(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Zombie();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void setPos(sf::Vector2f newPos);

	int getX() { return body.getPosition().x; }
	int getY() { return body.getPosition().y; }

	void checkColl(Bullet& bullet, int num);

	bool checkhit();
	bool checkdead();
	bool checkpass();

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	int hp;
	bool hit;
	bool dead;
	bool pass;
};