#ifndef GRAPHER_H
#define GRAPHER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Functions.h"

using namespace sf;

class Grapher
{
private:
    int width;
    int height;
    RenderWindow window;

    std::string title;

    Texture backgroundTexture;
    Image backgroundImage;
    Sprite backgroundSprite;

    std::vector<RectangleShape> rectangles;
    std::vector<CircleShape> circles;

public:
    // Constructor
    Grapher(const std::string &title, const std::string &file_route);

    // Drawers
    void mainLoop();
    void mainLoop(std::vector<std::pair<Vector2i, Vector2i>> &class_limits);
    void drawRectangle(Vector2i init_pos, Vector2i deinit_pos, Color color);
    void drawCircle(Vector2i pos, float radius, Color color);
    // Functions
    Color randomColor();
    std::vector<float> getPixelColor(Vector2i);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    std::vector<CircleShape> &getCircles() { return circles; }
    std::vector<RectangleShape> getRectangles() const { return rectangles; }

    // Settters
};

#endif // GRAPHER_H