#include <iostream>
#include "Functions.h"
#include "gui/Grapher.h"

#include "clustering/KMeans.h"
#include "clustering/AgglomerativeHierarchical.h"

using namespace std;

// Inicializa los datos
void initializeData(vector<vector<float>> &data, Grapher &grapher, int sample_size)
{

    for (int j = 0; j < sample_size; j++)
    {
        sf::Vector2i pos = sf::Vector2i(
            randomInt(0 + 2, grapher.getWidth() - 1),
            randomInt(0 + 2, grapher.getHeight() - 1));

        grapher.drawCircle(pos, 2, {0, 0, 0});
        data.push_back(grapher.getPixelColor(pos));
    }
    grapher.mainLoop();
}

// Aplica K-Means y actualiza la visualización
void applyKMeans(const vector<vector<float>> &data, Grapher &grapher, int number_classes)
{
    KMeans k_means(data, number_classes);

    // Genera colores aleatorios para las clases
    vector<Color> colors(number_classes);
    for (int i = 0; i < colors.size(); i++)
        colors[i] = grapher.randomColor();

    std::vector<std::vector<float>> last_centroids = k_means.getCentroids();

    int count = 0;

    do
    {
        last_centroids = k_means.getCentroids();
        k_means.step();
        // Actualiza los círculos en la gráfica
        for (auto &circle : grapher.getCircles())
        {
            vector<float> pixel_color = grapher.getPixelColor(Vector2i(circle.getPosition().x, circle.getPosition().y));

            float min_distance = numeric_limits<float>::max();
            int min_index = 0;
            for (int i = 0; i < k_means.getCentroids().size(); i++)
            {
                float distance = k_means.euclidianDistance(pixel_color, k_means.getCentroids()[i]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = i;
                }
            }

            circle.setFillColor(colors[min_index]);
        }

        count++;
        grapher.mainLoop();
    } while (!k_means.areCentroidsEqual(k_means.getCentroids(), last_centroids));

    k_means.printCentroids();
    cout << "Reached in " << count << " steps.\n";
}

// Aplica K-Means y actualiza la visualización
void applyAgglomerativeHierarchical(const vector<vector<float>> &data, Grapher &grapher, int number_classes)
{
    AgglomerativeHierarchical agglo_hier(data);

    std::cout << agglo_hier.getClusters().size() << " -> size \n";
    auto clusters = agglo_hier.getClusters();

    for (int i = 0; i < clusters.size(); i++)
    {
        for (const vector<float> &point : clusters[i])
        {
            for (float dimention : point)
                cout << dimention << " ";
            cout << "\n";
        }
    }

    // Genera colores aleatorios para las clases
    vector<Color> colors;
    for (int i = 0; i < data.size(); i++) // Máximo inicial de clusters
        colors.push_back(grapher.randomColor());

    int count = 0;

    do
    {
        auto clusters = agglo_hier.getClusters();

        // Actualizar la visualización
        for (CircleShape &circle : grapher.getCircles())
        {
            vector<float> pixel_color = grapher.getPixelColor(Vector2i(circle.getPosition().x, circle.getPosition().y));

            int index = -1;

            // Buscar el cluster del pixel
            for (int i = 0; i < clusters.size(); i++)
            {
                for (const vector<float> &point : clusters[i])
                {
                    std::cout << pixel_color[0] << ", " << pixel_color[1] << ", " << pixel_color[2] << "\n";
                    std::cout << point[0] << ", " << point[1] << ", " << point[2] << "\n";
                    if (agglo_hier.arePointsEqual(pixel_color, point))
                    {
                        index = i;
                        break; // No necesitamos seguir buscando
                    }
                }
                if (index != -1)
                    break;
            }

            // Asignar color al círculo
            if (index != -1)
                circle.setFillColor(colors[index]);
        }

        grapher.mainLoop();
        agglo_hier.step();
        count++;
    } while (agglo_hier.getClusters().size() > number_classes);

    cout << "Reached in " << count << " steps.\n";
}

int main()
{
    string image_route = readFile(); // Selección de imagen
    int number_classes;
    cout << "Number of classes: ";
    cin >> number_classes;

    Grapher grapher(image_route, image_route);
    vector<vector<float>> data;
    int sample_size;
    cout << "Sample points: ";
    cin >> sample_size;

    initializeData(data, grapher, sample_size);

    // Seleccionar el algoritmo deseado
    // applyKMeans(data, grapher, number_classes);
    applyAgglomerativeHierarchical(data, grapher, number_classes);

    grapher.mainLoop();

    return 0;
}
