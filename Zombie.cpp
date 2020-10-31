#include "Zombie.hpp"


Zombie::Zombie(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)

{
	this->speed = speed;
	row = 0;
	faceRight = true;
	hp = 100;

	body.setSize(sf::Vector2f(140.0f, 100.0f));
	body.setPosition(1280.0f, 206.0f);
	body.setTexture(texture);

	bool hit = false;
	bool dead = false;
	bool pass = false;

}

Zombie::~Zombie() 
{

}


void Zombie::update(float deltaTime) 
{
	sf::Vector2f movement(0.0f, 0.0f);
	movement.x -= speed * deltaTime;
	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 0;
		if (movement.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if ( body.getPosition().x <= -100) {
		pass = true;
		body.setPosition(sf::Vector2f(1280,100000));
	}
	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

}



void Zombie::draw(sf::RenderWindow& window) 
{
		window.draw(body);
}



void Zombie::checkColl(Bullet& bullet, int num)
{
	 hit = false;
	 dead = false;
	 srand(time(NULL));
	int y = ((rand() % 80 + 20) + (40 + 20 * num));
	int x = rand() % 1400 + 1280;
	if (bullet.getRight() > body.getPosition().x &&
		bullet.getTop() < body.getPosition().y + body.getSize().y &&
		bullet.getBottom() > body.getPosition().y) {
		hp -= 20;
		bullet.setbullets(true);
		bullet.setPos(sf::Vector2f(50444, 4123123));
		hit = true;
	}
	if (hp == 0)
	{
	body.setPosition(sf::Vector2f(x, y));
	hp = 100;
	dead = true;
	}
}


void Zombie::setPos(sf::Vector2f newPos)
{
	body.setPosition(newPos);
}
bool Zombie::checkhit() 
{
	return hit;
}
bool Zombie::checkdead() 
{
	return dead;
}

bool Zombie::checkpass()
{
	return pass;
}