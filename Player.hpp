#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	int getX() { return body.getPosition().x; }
	int getY() { return body.getPosition().y; }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};
