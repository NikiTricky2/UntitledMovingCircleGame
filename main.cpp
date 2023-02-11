#include <SFML/Graphics.hpp>

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
    sf::CircleShape circle(radius);

    circle.setFillColor(sf::Color::White);
    circle.setOrigin(50.f, 50.f);
    circle.setPosition(400.f, 300.f);

    sf::Vector2f velocity(10.f, 10.f);

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

        window.draw(circle);

        window.display();
    }

    return 0;
}
