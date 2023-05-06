#include <SFML/Graphics.hpp>
#include <string>

int main()
{
    // Create the main window
    int width = 400, height = 400;
    sf::RenderWindow app(sf::VideoMode(width, height), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    sf::Vector2f spriteScale = sprite.getScale();

    // Debugging
    sf::Font font;
    if(!font.loadFromFile("arial.ttf")){
        throw std::invalid_argument("Unable to load the font");
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    std::string xText;
    std::string yText;

    // Constants
    float offset = 120;
    float xEConstraint = width+spriteScale.x-offset;
    float xBConstraint = 90-spriteScale.x-offset;
    float yTConstraint = height+spriteScale.y-offset;
    float yBConstraint = 100-spriteScale.y-offset;

    // Physics variables
    float spriteAngle = 0;
    float x = 0, y = 0;
    float xSpeed = 0.1;
    float ySpeed = 0.1;


	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Debugging coordinates
        xText = std::to_string(sprite.getPosition().x);
        yText = std::to_string(sprite.getPosition().y);

        text.setString("x: " + xText + ", y: " + yText);

        // Draw the sprite
        app.draw(sprite);
        app.draw(text);

        // Sprite Physics
        if(x >= xEConstraint || x <= xBConstraint ){
            xSpeed *= -1;
        }
        if(y >= yTConstraint || y <= yBConstraint){
            ySpeed *= -1;
        }

        x += xSpeed;
        y += ySpeed;
        sprite.setPosition(x,y);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
