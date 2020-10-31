#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <time.h>  
#include <random>
#include <vector>
#include <string>
#include <iomanip>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Zombie.hpp"
using namespace std;
int main()
{
    //--------------------------------------------------------
    //Sound Files (Music,Sound Effects, Sound Buffers)

    //Music
    sf::Music music;
    if (!music.openFromFile("Sounds/music.ogg"))
        return -1; // error
    music.play();
    //Sound Buffers
    sf::SoundBuffer shootbuffer;
    if (!shootbuffer.loadFromFile("Sounds/shoot.wav"))
        return -1;
 
    sf::SoundBuffer noAmmobuffer;
    if (!noAmmobuffer.loadFromFile("Sounds/noAmmo.wav"))
        return -1;

    sf::SoundBuffer reloadbuffer;
    if (!reloadbuffer.loadFromFile("Sounds/Reload.wav"))
        return -1;

    sf::SoundBuffer reloadvoicebuffer;
    if (!reloadvoicebuffer.loadFromFile("Sounds/reloadvoice.wav"))
        return -1;

    sf::SoundBuffer hitbuffer;
    if (!hitbuffer.loadFromFile("Sounds/hit1.wav"))
        return -1;

    sf::SoundBuffer deadbuffer;
    if (!deadbuffer.loadFromFile("Sounds/dead2.wav"))
        return -1;

    sf::SoundBuffer dyingbuffer;
    if (!dyingbuffer.loadFromFile("Sounds/dead1.wav"))
        return -1;

    sf::SoundBuffer gameoverbuffer;
    if (!gameoverbuffer.loadFromFile("Sounds/gameover.wav"))
        return -1;

//--------------------------------------------------------
    //Sounds
    sf::Sound shoot;
    shoot.setBuffer(shootbuffer);

    sf::Sound noAmmo;
    noAmmo.setBuffer(noAmmobuffer);

    sf::Sound reload;
    reload.setBuffer(reloadbuffer);

    sf::Sound reloadvoice;
    reloadvoice.setBuffer(reloadvoicebuffer);

    sf::Sound hit;
    hit.setBuffer(hitbuffer);

    sf::Sound dead;
    dead.setBuffer(deadbuffer);

    sf::Sound dying;
    dying.setBuffer(dyingbuffer);

    sf::Sound gameover;
    gameover.setBuffer(gameoverbuffer);
 //--------------------------------------------------------





 
//-----------------------------------------------
    //Window (1280 x 720)
    sf::RenderWindow window(sf::VideoMode(1280,720), "Zombie Massacre", sf::Style::Close | sf::Style::Fullscreen);
//-----------------------------------------------
    //Player Modela
    sf::Texture playerTexture; 
    playerTexture.loadFromFile("Textures/Player.png");
    Player player(&playerTexture, sf::Vector2u(20, 2), 0.03f, 200.0f);
 //-----------------------------------------------
    //Zombie Model
    sf::Texture zombieTexture;
    zombieTexture.loadFromFile("Textures/Zombie.png");
    std::vector<Zombie> zombs;
    float speedzomb = 100.0f;
    Zombie zombies(&zombieTexture, sf::Vector2u(17, 1), 0.03f, speedzomb);
    int zombiekill = 0;
    bool over = false;
   
 //----------------------------------------------
    //Bullet Model / Firing
    std::vector<Bullet> bulletVec;
    bool isFiring = false;
    int clip = 30;
    int magazine = 90;

 //-----------------------------------------------
    //Text/Font Initizalizers
    sf::Font font;
    if (!font.loadFromFile("DESIB.ttf"))
    {
        // error...
    }
    sf::Text stats;
    stats.setFont(font);
    stats.setCharacterSize(42);
    stats.setFillColor(sf::Color::Red);
    stats.setStyle(sf::Text::Regular);
    stats.setPosition(190.0f, 0.0f);

    sf::Text Gameover;
    Gameover.setFont(font);
    Gameover.setCharacterSize(72);
    Gameover.setFillColor(sf::Color::Red);
    Gameover.setStyle(sf::Text::Regular);
    Gameover.setPosition(400.0f, 200.0f);


//-----------------------------------------------
    //Background
    sf::Texture textureBackground;
    textureBackground.loadFromFile("Textures/Background.png");
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);
//-----------------------------------------------



//-----------------------------------------------
    //Clock Time
    float deltaTime = 0.0f;
    sf::Clock clock;
    int count = 0;
    int gameovercount = 0;
 //-----------------------------------------------

    

 //-----------------------------------------------
    //Event Update and Inputs
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        count++;
        bool spawn;
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                window.setKeyRepeatEnabled(false);
                //--------------------------------------
                //Shoot Algorithm
                if (evnt.key.code == sf::Keyboard::Space) {
                        isFiring = true;

                        if (clip > 0) {
                            shoot.play();

                        }
                        if (clip <= 0) {
                            noAmmo.play();
                        }   
                    break;
                }
                //--------------------------------------
                //Reload Algorithm
                if (evnt.key.code == sf::Keyboard::R) {
                    int difference = (30 - clip);
                    int offset = (difference - magazine);
                    if (magazine > 0 && clip < 30) {
                        if (magazine > difference) {
                            magazine -= difference;
                                clip += difference;

    
                        }
                        else {
                            magazine = 0;
                            clip += (difference+offset);
                        }
                        reloadvoice.play();
                        reload.play();
                    }
                }
            }
        }
        //Drawing Models (Zombies,Player,Background)
        player.update(deltaTime);
     
        //Spawning Zombies
        if (count <= 15000) {
            spawn = true;
        }
        else {
            spawn = false;
        }

        if (spawn == true)
        {
            if ((count % 1000) == 0)
            {
                zombs.push_back(zombies);
            }
        }
        //Updating Movement Of Zombies
        for (int i = 0; i < zombs.size(); i++) {
            float y = rand() % 480 + 1;
            zombies.setPos(sf::Vector2f(1280, y));
            zombs[i].update(deltaTime);
        }

        //Background and CLearing
        window.clear();
        window.draw(spriteBackground);

        //-----------------------------------------------
        //Bullet Algorithm
        if (isFiring == true && clip > 0) {
            Bullet newBullet(sf::Vector2f(15, 3));
            newBullet.setPos(sf::Vector2f(player.getX() + 142, player.getY() + 70));
            bulletVec.push_back(newBullet);
            clip -= 1;
            isFiring = false;
        }
        for (int i = 0; i < bulletVec.size(); i++) {
            bulletVec[i].fire(3);
            bulletVec[i].draw(window);
        }
        //-----------------------------------------------
        //Draw Zombies
        for (int i = 0; i < zombs.size(); i++) {
            zombs[i].draw(window);
        }
        //Collision Check bullets to Zombies
        for (int i = 0; i < bulletVec.size(); i++) {
            for (int j = 0; j < zombs.size(); j++) {
                zombs[j].checkColl(bulletVec[i], j);
                if (zombs[j].checkhit() == true) {
                    hit.play();
                }
                if (zombs[j].checkdead() == true) {
                    magazine += 5;
                    speedzomb++;
                    zombiekill += 1;
                    dead.play();
                    dying.play();   
                }
            }
        }
        //Check if Pass
        int zombiepass = 5;
        for (int j = 0; j < zombs.size(); j++) {
            if (zombs[j].checkpass() == true) {
                zombiepass -= 1;
                if (zombiepass <= 0) {
                    zombiepass = 0;
                }
            }
        }
        //---------------------------------------------------
        //GAME HUD | GAMEOVER HUD
        string clipstr = to_string(clip);
        string magazinestr = to_string(magazine);
        string zombiekillstr = to_string(zombiekill);
        string zombiepassstr = to_string(zombiepass);
        string score = "Zombies Killed: " + zombiekillstr
            + "         Ammo: " + clipstr + " | " + magazinestr
            + "         Lives : " + zombiepassstr;

        stats.setString(score);
        Gameover.setString("Game Over\nZombies Killed: " + zombiekillstr);
        player.draw(window);
        window.draw(stats);
        if (zombiepass == 0)
        {
            window.draw(Gameover);
            gameovercount++;
            music.stop();
                if (gameovercount % 5000 == 0) {
                    window.close();
                }
        }
        //---------------------------------------------------
        //Game Update
        window.display();
    }
    return 0;
}
//-----------------------------------------------
