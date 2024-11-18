#include <iostream>

#include "Functions.h"
#include "gui/Grapher.h"

using namespace std;

int main()
{
    string image_route;
    int number_classes;
    vector<pair<sf::Vector2i, sf::Vector2i>> class_limits;
    vector<vector<sf::Vector2i>> class_points;
    vector<vector<Color>> samples;
    int sample_size;

    // Select an image
    image_route = readFile();

    // Number of classes
    cout << "Number of classes: ";
    cin >> number_classes;
    class_limits.resize(number_classes);
    class_points.resize(number_classes);
    samples.resize(number_classes);

    // Plot image (First time)
    Grapher grapher(image_route, image_route);
    grapher.mainLoop(class_limits);

    // Generate random points
    cout << "Sample size per class: ";
    cin >> sample_size;

    std::vector<RectangleShape> rectangles = grapher.getRectangles();
    for (int i = 0; i < number_classes; i++)
    {
        int x_min = min(class_limits[i].first.x, class_limits[i].second.x);
        int x_max = max(class_limits[i].first.x, class_limits[i].second.x);
        int y_min = min(class_limits[i].first.y, class_limits[i].second.y);
        int y_max = max(class_limits[i].first.y, class_limits[i].second.y);

        for (int j = 0; j < sample_size; j++)
        {
            sf::Vector2i pos = sf::Vector2i(randomInt(x_min, x_max), randomInt(y_min, y_max));
            class_points[i].push_back(pos);
            grapher.drawCircle(pos, 2, rectangles[i].getOutlineColor());
            samples[i].push_back(grapher.getPixelColor(pos));
        }
    }

    grapher.mainLoop();

    // Seleccionar puntos o método adicional

    return 0;
}
