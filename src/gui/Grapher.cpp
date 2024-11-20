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
    window.create(sf::VideoMode(size.x, size.y), title, Style::Close);

    // Configurar el sprite con la textura cargada
    backgroundSprite.setTexture(backgroundTexture);
    backgroundImage = backgroundTexture.copyToImage();
}

// Main Loop
void Grapher::mainLoop(std::vector<std::pair<Vector2i, Vector2i>> &class_limits)
{
    Clock clock;

    int count = 0;
    std::cout << "size: " << class_limits.size() << "\n";
    int classes = class_limits.size();

    std::pair<Vector2i, Vector2i> square;

    Vector2i init_mouse_pos, deinit_mouse_pos;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Manejar el clic del botón
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                init_mouse_pos = Vector2i(event.mouseButton.x, event.mouseButton.y);
            }

            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
            {
                deinit_mouse_pos = Vector2i(event.mouseButton.x, event.mouseButton.y);
                class_limits[count++] = std::make_pair(init_mouse_pos, deinit_mouse_pos);

                drawRectangle(init_mouse_pos, deinit_mouse_pos, randomColor());

                if (count == class_limits.size())
                    return;
            }
        }

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

void Grapher::mainLoop(std::vector<float> weights)
{
    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                Vector2i mouse_pos(event.mouseButton.x, event.mouseButton.y);
                std::vector<float> color = getPixelColor(mouse_pos);

                float clas = weights[0]*color[0] + weights[1]*color[1] + weights[2]*color[2]+ weights[3];
                if (clas < 0)
                    drawCircle(mouse_pos, 5, rectangles[0].getOutlineColor());
                else
                    drawCircle(mouse_pos, 5, rectangles[1].getOutlineColor());
            }
        }

        window.clear();
        window.draw(backgroundSprite);

        // draw static elements
        if (!rectangles.empty())
            for (RectangleShape rectangle : rectangles)
                window.draw(rectangle);

        if (!circles.empty())
            for (Circle circle : circles)
                window.draw(circle.shape);

        if (!lines.empty())
            for (VertexArray line : lines)
                window.draw(line);

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
    circle.image_rgb = getPixelColor(pos);

    this->circles.push_back(circle);
}

void Grapher::drawLine(Vector2i pos_i, Vector2i pos_j, Color color)
{

    VertexArray line(Lines, 2);

    line[0].position = Vector2f(pos_i.x, pos_i.y);
    line[1].position = Vector2f(pos_j.x, pos_j.y);

    line[0].color = line[1].color = color;

    this->lines.push_back(line);
}

Color Grapher::randomColor()
{
    return Color(randomInt(0, 255), randomInt(0, 255), randomInt(0, 255));
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