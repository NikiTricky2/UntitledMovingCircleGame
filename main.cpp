#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

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

void updateDragVelocity(sf::Vector2f& vel, float drag) {
    vel.x *= drag;
    vel.y *= drag;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Moving Circle");
    
    sf::Font font;
    if (!font.loadFromFile("SourceCodePro.ttf")) {
        std::cout << "Cant load font";
    }

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(50.f, 50.f);
    circle.setPosition(w/2.f, h/2.f);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::Vector2f velocity(0.f, 0.f);

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
            sf::Vertex line[] =
            {
                sf::Vertex(circle.getPosition()),
                sf::Vertex(mouse)
            };

            window.draw(line, 2, sf::Lines);

            mouseDown = true;
        }
        else if (mouseDown) { // The frame after the mouse is released
            sf::Vector2f newvelocity = mouse - circle.getPosition();
            newvelocity /= 200.f;
            velocity = -newvelocity; // Invert bc we don't wanting the ball to go towards the cursor

            mouseDown = false;
        } else {
            circle.move(velocity);
            updateDragVelocity(velocity, drag);

            // Bounce off the wall
            if (circle.getPosition().x > w || circle.getPosition().x < 0) {
                velocity.x = -velocity.x;
            }
            if (circle.getPosition().y > h || circle.getPosition().y < 0) {
                velocity.y = -velocity.y;
            }
        }

        text.setString(to_string(fps));

        window.draw(circle);
        window.draw(text);

        window.display();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        fps = floor(fps);
        previousTime = currentTime;
    }

    return 0;
}
