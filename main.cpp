#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "circle.hpp"
#include "buttons.hpp"

template <typename T>
std::string to_string(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

const int w = 1600, h = 900;
const float radius = 50.f;
const float drag = 0.997f;

int score = 0;
int moves = 0;

int scene = 0;
int lastscene = 0;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Untitled Moving Circle Game");
    
    sf::Font font;
    if (!font.loadFromFile("SourceCodePro.ttf")) {
        std::cout << "Cant load font";
    }

    // Titlescreen

    sf::Text titletext;
    titletext.setFont(font);
    titletext.setCharacterSize(120);
    titletext.setFillColor(sf::Color::White);
    titletext.setPosition(sf::Vector2f(100.f, 100.f));
    titletext.setString("Untitled\nMoving\nCircle\nGame");

    sf::Vector2f playbtnpos = sf::Vector2f(1000.f, 200.f);
    Button playbutton(playbtnpos, sf::Vector2f(300.f, 100.f));

    sf::Text playtext;
    playtext.setFont(font);
    playtext.setCharacterSize(40);
    playtext.setFillColor(sf::Color::White);
    playtext.setPosition(playbtnpos + sf::Vector2f(90.f, 10.f) + sf::Vector2f(10.f, 10.f));
    playtext.setString("Play");

    sf::Vector2f creditsbtnpos = sf::Vector2f(1000.f, 350.f);
    Button creditsbutton(creditsbtnpos, sf::Vector2f(300.f, 100.f));

    sf::Text creditsbtntext;
    creditsbtntext.setFont(font);
    creditsbtntext.setCharacterSize(40);
    creditsbtntext.setFillColor(sf::Color::White);
    creditsbtntext.setPosition(creditsbtnpos + sf::Vector2f(50.f, 10.f) + sf::Vector2f(10.f, 10.f));
    creditsbtntext.setString("Credits");

    // Credits

    sf::Text creditstext;
    creditstext.setFont(font);
    creditstext.setCharacterSize(40);
    creditstext.setFillColor(sf::Color::White);
    creditstext.setPosition(sf::Vector2f(100.f, 100.f) + sf::Vector2f(10.f, 10.f));
    creditstext.setString("Code:\nNikiTricky\n\nAssets:\nNikiTricky\n\nAudio:\nNikiTricky\n\nFont:\nSource Code Pro by Paul D. Hunt");

    sf::Vector2f backbutton_cr_pos = sf::Vector2f(100.f, 700.f);
    Button backbutton_cr(backbutton_cr_pos, sf::Vector2f(300.f, 100.f));

    sf::Text backbutton_cr_text;
    backbutton_cr_text.setFont(font);
    backbutton_cr_text.setCharacterSize(40);
    backbutton_cr_text.setFillColor(sf::Color::White);
    backbutton_cr_text.setPosition(backbutton_cr_pos + sf::Vector2f(90.f, 10.f) + sf::Vector2f(10.f, 10.f));
    backbutton_cr_text.setString("Back");

    // Game

    Player player(radius, sf::Vector2f(w / 2.f, h / 2.f));

    Food food(radius);
    food.newPos(w, h);
    food.newPos(w, h);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    float fps = 0.f;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    srand(time(NULL)); // Make the pseudorandom engine more random

    bool mouseDown = false;
    while (window.isOpen())
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (scene == 0) {
            window.clear(sf::Color::Black);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                playbutton.collision(mouse);
                creditsbutton.collision(mouse);
            }
            else {
                if (playbutton.pressing)
                {
                    playbutton.pressing = false;
                    scene = 1;
                } else if (creditsbutton.pressing)
                {
                    creditsbutton.pressing = false;
                    scene = 2;
                }
            }

            window.draw(titletext);

            window.draw(playbutton.rect);
            window.draw(playtext);

            window.draw(creditsbutton.rect);
            window.draw(creditsbtntext);

            window.display();

        } else if (scene == 1) {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == 17) { // R(eset)
                        player.center(w, h);
                        player.velocity = sf::Vector2f();
                    }
                }
            }

            window.clear(sf::Color::Black);


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vertex line[] =
                {
                    // sf::Vertex(player.getPos()), This does not work
                    sf::Vertex(player.circle.getPosition() + sf::Vector2f(radius, radius)),
                    sf::Vertex(mouse)
                };

                window.draw(line, 2, sf::Lines);

                rand();

                mouseDown = true;
            }
            else if (mouseDown) { // The frame after the mouse is released
                sf::Vector2f newvelocity = mouse - (player.circle.getPosition() + sf::Vector2f(radius, radius));
                newvelocity /= 200.f;
                player.velocity = -newvelocity; // Invert bc we don't wanting the ball to go towards the cursor

                mouseDown = false;
                moves++;
            }
            else {
                player.update(drag, w, h);
            }

            if (player.collision(food)) {
                food.newPos(w, h);
                score++;
            }

            text.setString(
                "FPS: " + to_string(fps) + "\n" +
                "Score: " + to_string(score) + "\n" +
                "Moves: " + to_string(moves)
            );

            window.draw(food.circle);
            window.draw(player.circle);
            window.draw(text);

            window.display();

            currentTime = clock.getElapsedTime();
            fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
            fps = floor(fps);
            previousTime = currentTime;
        } 
        else if (scene == 2) {
            window.clear(sf::Color::Black);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                backbutton_cr.collision(mouse);
            }
            else {
                if (backbutton_cr.pressing)
                {
                    backbutton_cr.pressing = false;
                    scene = 0;
                }
            }

            window.draw(creditstext);

            window.draw(backbutton_cr.rect);
            window.draw(backbutton_cr_text);

            window.display();
        }

        lastscene = scene;
    }

    return 0;
}