#ifndef GRAPHER_H
#define GRAPHER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Functions.h"

using namespace sf;

struct Circle
{
    CircleShape shape;
    std::vector<float> pixel_rgb;
};

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
    std::vector<Circle> circles;

public:
    // Constructor
    Grapher(const std::string &title, const std::string &file_route);

    // Drawers
    void mainLoop(bool auto_return, float time = 1.0);
    void drawRectangle(Vector2i init_pos, Vector2i deinit_pos, Color color);
    void drawCircle(Vector2i pos, float radius, Color color);
    // Functions
    Color randomColor();
    std::vector<float> getPixelColor(Vector2i);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    std::vector<Circle> &getCircles() { return circles; }
    std::vector<RectangleShape> getRectangles() const { return rectangles; }

    // Settters
};

#endif // GRAPHER_H