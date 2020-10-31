#pragma once
#include <SFML\Graphics.hpp>
class Animation 
{
public:
    Animation(sf::Texture* texture, sf::Vector2u iamgeCount,float switchTime);
    ~Animation();

    void update(int row, float deltaTime,bool faceRight);
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

 };