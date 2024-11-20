#include <iostream>

#include "Functions.h"
#include "gui/Grapher.h"
#include "Perceptron.h"
#include "NeuronalNetwork.h"
#include <json.hpp>

using namespace std;

void print(vector<float> vec)
{
    for (auto &&v : vec)
        cout << v << "\t";
    cout << endl;
}

std::vector<float> graph(vector<vector<vector<float>>> points, Grapher &grapher)
{
    std::vector<float> weights(4, 1);
    Perceptron perceptron(weights, 1);

    NeuronalNetwork neuronal_network(points[0], points[1], perceptron);
    std::cout << "1";
    neuronal_network.calculate();

    nlohmann::json j;
    j["firstClass"] = points[0];
    j["secondClass"] = points[1];
    j["weights"] = neuronal_network.getPerceptron().getWeights();

    ofstream file("build/data.json");
    file << j.dump(4);
    file.close();

    int result = std::system("python python/Grapher.py");
    // grapher.mainLoop();
    return neuronal_network.getPerceptron().getWeights();
}

int main()
{
    string image_route;
    int number_classes = 2;
    vector<pair<sf::Vector2i, sf::Vector2i>> class_limits;
    vector<vector<sf::Vector2i>> class_points;
    vector<vector<vector<float>>> points;
    vector<vector<vector<float>>> points2;
    int sample_size;

    // Select an image
    image_route = readFile();

    // Number of classes
    class_limits.resize(number_classes);
    class_points.resize(number_classes);
    points.resize(number_classes);
    points2.resize(number_classes);

    // Plot image (First time)
    Grapher grapher(image_route, image_route);
    grapher.mainLoop(class_limits);

    // Generate random points
    cout << "Sample size per class: ";
    cin >> sample_size;

    cout << ".";
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
            cout << "Generando punto en posición: (" << pos.x << ", " << pos.y << ")\n";
            class_points[i].push_back(pos);
            grapher.drawCircle(pos, 4, rectangles[i].getOutlineColor());

            vector<float> pixel_color = (grapher.getPixelColor(pos));
            points[i].push_back(pixel_color);
            points2[i].push_back({
                static_cast<float>(pos.x),
                static_cast<float>(pos.y),
            });
            //   float(pixel_color[0] / 255.0),
            //   float(pixel_color[1] / 255.0),
            //   float(pixel_color[2] / 255.0)});
        }
    }

    std::vector<float> weights(3, 1);
    Perceptron perceptron(weights, 0.1);

    NeuronalNetwork neuronal_network(points2[0], points2[1], perceptron);
    neuronal_network.calculate();
    print(neuronal_network.getPerceptron().getWeights());

    std::vector<float> new_wiehts = graph(points, grapher);

    // Graficar la línea basada en los pesos
    std::vector<float> final_weights = neuronal_network.getPerceptron().getWeights();

    // Primer peso, segundo peso y último peso
    float w0 = final_weights[0];
    float w1 = final_weights[1];
    float w_last = final_weights[final_weights.size() - 1];

    // Dimensiones de la imagen
    // Dimensiones de la imagen
    int img_width = grapher.getWidth();
    int img_height = grapher.getHeight();

    // Variables para los extremos
    sf::Vector2i point1, point2;

    // Caso general: calcular puntos extremos
    if (w1 != 0)
    {
        // Para x = 0
        float y1 = -w_last / w1;
        if (y1 >= 0 && y1 <= img_height)
        {
            point1 = sf::Vector2i(0, y1);
        }
        else
        {
            // Si está fuera del rango, ajustar con límites
            y1 = std::clamp(y1, 0.0f, static_cast<float>(img_height));
            point1 = sf::Vector2i(0, y1);
        }

        // Para x = img_width
        float y2 = -(w_last + w0 * img_width) / w1;
        if (y2 >= 0 && y2 <= img_height)
        {
            point2 = sf::Vector2i(img_width, y2);
        }
        else
        {
            // Si está fuera del rango, ajustar con límites
            y2 = std::clamp(y2, 0.0f, static_cast<float>(img_height));
            point2 = sf::Vector2i(img_width, y2);
        }
    }
    else if (w0 != 0)
    {
        // Caso especial: línea vertical
        float x_pos = -w_last / w0;
        if (x_pos >= 0 && x_pos <= img_width)
        {
            point1 = sf::Vector2i(x_pos, 0);
            point2 = sf::Vector2i(x_pos, img_height);
        }
        else
        {
            std::cerr << "Error: Línea fuera de los límites de la imagen.\n";
            return 1;
        }
    }
    else
    {
        std::cerr << "Error: No se puede calcular una línea válida.\n";
        return 1;
    }

    // Dibujar la línea en la imagen
    print(new_wiehts);
    grapher.drawLine(point1, point2, sf::Color::Yellow);

    grapher.mainLoop(new_wiehts);
    return 0;
}
