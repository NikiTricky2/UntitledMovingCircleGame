#include <iostream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "circle.hpp"

template <typename T>
std::string to_string(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

const int w = 1600, h = 900;
const float radius = 50.f;
const float drag = 0.997;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Moving Circle");
    
    sf::Font font;
    if (!font.loadFromFile("SourceCodePro.ttf")) {
        std::cout << "Cant load font";
    }

    //sf::CircleShape circle(radius);
    //circle.setFillColor(sf::Color::White);
    //circle.setOrigin(50.f, 50.f);
    //circle.setPosition(w/2.f, h/2.f);
    Player player(radius, sf::Vector2f(w / 2.f, h / 2.f));

    sf::Text fps_text;
    fps_text.setFont(font);
    fps_text.setCharacterSize(24);
    fps_text.setFillColor(sf::Color::White);

    float fps = 0.f;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    bool mouseDown = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // std::cout << to_string(player.getPos().x); // Magic line of code that fixes everything sometimes
            sf::Vertex line[] =
            {
                // sf::Vertex(player.getPos()), This does not work
                sf::Vertex(player.circle.getPosition() + sf::Vector2f(radius, radius)),
                sf::Vertex(mouse)
            };

            window.draw(line, 2, sf::Lines);

            mouseDown = true;
        }
        else if (mouseDown) { // The frame after the mouse is released
            sf::Vector2f newvelocity = mouse - (player.circle.getPosition() + sf::Vector2f(radius, radius));
            newvelocity /= 200.f;
            player.velocity = -newvelocity; // Invert bc we don't wanting the ball to go towards the cursor

            mouseDown = false;
        } else {
            player.update(drag, w, h);
        }

        fps_text.setString(to_string(fps));

        window.draw(player.circle);
        window.draw(fps_text);

        window.display();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        fps = floor(fps);
        previousTime = currentTime;
    }

    return 0;
}
