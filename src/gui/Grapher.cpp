#include "gui/Grapher.h"

// Constructor
Grapher::Grapher(const std::string &title, const std::string &file_route)
    : title(title)
{
    // Obtener imagen
    if (!backgroundTexture.loadFromFile(file_route))
    {
        std::cerr << "Error: No se pudo cargar la imagen desde " << file_route << std::endl;
        return;
    }

    sf::Vector2u size = backgroundTexture.getSize(); // Obtiene las dimensiones de la imagen
    width = size.x;
    height = size.y;

    // Crear la ventana
    window.create(sf::VideoMode(width, height), title, Style::Close);

    // Configurar el sprite con la textura cargada
    backgroundSprite.setTexture(backgroundTexture);
    backgroundImage = backgroundTexture.copyToImage();
}

// Main Loop
void Grapher::mainLoop(bool auto_return, float time)
{
    Clock clock;
    float delta_time;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
                return;
        }

        delta_time += clock.restart().asMilliseconds();
        if (auto_return && delta_time > time)
            return;

        window.clear();
        window.draw(backgroundSprite);

        // draw static elements
        if (!rectangles.empty())
            for (RectangleShape rectangle : rectangles)
                window.draw(rectangle);

        if (!circles.empty())
            for (Circle circle : circles)
                window.draw(circle.shape);

        window.display();
    }
}

void Grapher::drawRectangle(Vector2i init_pos, Vector2i deinit_pos, Color color)
{
    int width = std::abs(init_pos.x - deinit_pos.x);
    int height = std::abs(init_pos.y - deinit_pos.y);

    int pos_x = std::min(init_pos.x, deinit_pos.x);
    int pos_y = std::min(init_pos.y, deinit_pos.y);

    RectangleShape rectangle(Vector2f(width, height));
    rectangle.setPosition(pos_x, pos_y);
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(color);

    this->rectangles.push_back(rectangle);
}

void Grapher::drawCircle(Vector2i pos, float radius, Color color)
{
    CircleShape circle_shape(radius);
    circle_shape.setPosition(pos.x - radius, pos.y - radius);
    circle_shape.setFillColor(color);

    Circle circle;
    circle.shape = circle_shape;
    circle.pixel_rgb = getPixelColor(pos);

    this->circles.push_back(circle);
}

Color Grapher::randomColor()
{
    return Color(randomInt(1, 254), randomInt(1, 254), randomInt(1, 254));
}

std::vector<float> Grapher::getPixelColor(Vector2i pos)
{
    if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
    {
        std::cerr << "Error: Coordenadas fuera de los límites (" << pos.x << ", " << pos.y << ")" << std::endl;
        return {0.0f, 0.0f, 0.0f}; // Devuelve un color por defecto (negro)
    }

    Color color = backgroundImage.getPixel(pos.x, pos.y);

    std::vector<float> rgb = {
        static_cast<float>(color.r),
        static_cast<float>(color.g),
        static_cast<float>(color.b)};

    return rgb;
}