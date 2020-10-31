#include "Player.hpp"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
		animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(150.0f, 100.0f));
	body.setPosition(0.0f, 206.0f);
	body.setTexture(texture);


}


Player::~Player() 
{

}



void Player::update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime;
		
	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		faceRight = true;
	}
	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}




void Player::draw(sf::RenderWindow& window) 
{
	window.draw(body);
}

