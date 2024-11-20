#include <iostream>
#include <memory>

#include "Functions.h"
#include "gui/Grapher.h"
#include "clustering/KMeans.h"
#include "clustering/AgglomerativeHierarchical.h"
#include "clustering/AgglomerativeChaining.h"

using namespace std;

// Inicializa los datos
void initializeData(vector<vector<float>> &data, Grapher &grapher, int sample_size)
{

    for (int j = 0; j < sample_size; j++)
    {
        sf::Vector2i pos = sf::Vector2i(
            randomInt(0 + 2, grapher.getWidth() - 1),
            randomInt(0 + 2, grapher.getHeight() - 1));

        grapher.drawCircle(pos, 5, {0, 0, 0});
        data.push_back(grapher.getPixelColor(pos));
    }
    grapher.mainLoop(false);
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
    vector<int> size(number_classes, 0);
    do
    {
        last_centroids = k_means.getCentroids();
        k_means.step();
        // Actualiza los círculos en la gráfica
        for (auto &circle : grapher.getCircles())
        {
            vector<float> pixel_color = circle.pixel_rgb;

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
            size[min_index]++;
            circle.shape.setFillColor(colors[min_index]);
        }

        count++;
        grapher.mainLoop(false);
    } while (!k_means.areCentroidsEqual(k_means.getCentroids(), last_centroids));

    k_means.printCentroids();
    for (int i = 0; i < size.size(); i++)
        cout << "Centroid " << i << ": " << size[i] / count << "\n";
    cout << "Reached in " << count << " steps.\n";
    cout << "----------------------------------\n";
}

void applyAgglomerativeHierarchical(const vector<vector<float>> &data, Grapher &grapher, int number_classes)
{
    AgglomerativeHierarchical agglo_hier(data);

    // Genera colores aleatorios para las clases
    vector<Color> colors;
    for (int i = 0; i < data.size(); i++) // Máximo inicial de clusters
        colors.push_back(grapher.randomColor());

    int count = 0;

    do
    {
        grapher.mainLoop(true, 5);
        // colors.erase(colors.end());
        agglo_hier.step();

        auto clusters = agglo_hier.getClusters();

        // Actualizar la visualización
        for (Circle &circle : grapher.getCircles())
        {
            vector<float> pixel_color = circle.pixel_rgb;

            int index = -1;

            // Buscar el cluster del pixel
            for (int i = 0; i < clusters.size(); i++)
            {
                for (const vector<float> &point : clusters[i])
                {
                    if (agglo_hier.arePointsEqual(pixel_color, point))
                    {
                        index = i;
                        break;
                    }
                }
                if (index != -1)
                    break;
            }

            // Asignar color al círculo
            if (index != -1)
                circle.shape.setFillColor(colors[index]);
            else
                cout << "index: " << index;
        }

        count++;
    } while (agglo_hier.getClusters().size() > number_classes);

    agglo_hier.saveLinkageMatrixToCSV("resources/data/linkage.csv");
    
    cout << "Reached in " << count << " steps.\n";
    cout << "----------------------------------\n";
}

void applyAgglomerativeChaining(const vector<vector<float>> &data, Grapher &grapher)
{
    float threshold;
    cout << "Threshold: ";
    cin >> threshold;

    AgglomerativeChaining agglo_chain(data, threshold);

    // Genera colores aleatorios para las clases
    vector<Color> colors;
    colors.push_back(grapher.randomColor());

    std::vector<std::vector<float>> last_centroids = agglo_chain.getClusters();
    std::vector<int> size(last_centroids.size(), 0);

    int count = 0;
    do
    {
        last_centroids = agglo_chain.getClusters();
        agglo_chain.step();

        colors.resize(agglo_chain.getClusters().size());
        size.resize(agglo_chain.getClusters().size());

        for (int i = 0; i < agglo_chain.getClusters().size(); i++)
            colors[i] = grapher.randomColor();

        // Actualiza los círculos en la gráfica
        for (auto &circle : grapher.getCircles())
        {
            vector<float> pixel_color = circle.pixel_rgb;

            float min_distance = numeric_limits<float>::max();
            int min_index = 0;
            for (int i = 0; i < agglo_chain.getClusters().size(); i++)
            {
                float distance = agglo_chain.euclidianDistance(pixel_color, agglo_chain.getClusters()[i]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = i;
                }
            }
            size[min_index]++;
            circle.shape.setFillColor(colors[min_index]);
        }

        count++;
        grapher.mainLoop(false);
    } while (!agglo_chain.areCentroidsEqual(agglo_chain.getClusters(), last_centroids));

    agglo_chain.printClusters();
    for (int i = 0; i < size.size(); i++)
        cout << "Centroid " << i << ": " << size[i] / count << "\n";
    cout << "Reached in " << count << " steps.\n";
    cout << "----------------------------------\n";
}

void menu(int &option)
{
    cout << "1) Choose image\n";
    cout << "2) K Means\n";
    cout << "3) Agglomerative herarchical\n";
    cout << "4) Agglomerative chaining\n";
    cin >> option;
}

int main()
{
    string image_route;
    std::unique_ptr<Grapher> grapher;
    vector<vector<float>> data;
    int option = 0, size = 10, classes_size = 0;

    image_route = readFile();
    grapher = make_unique<Grapher>(image_route, image_route);

    cout << "Random points: ";
    cin >> size;
    initializeData(data, *grapher, size);

    do
    {
        menu(option);

        switch (option)
        {
        case 1:
        {
            image_route = readFile();

            grapher = make_unique<Grapher>(image_route, image_route);
            cout << "Random points: ";
            cin >> size;
            initializeData(data, *grapher, size);
        }
        case 2:
        {
            cout << "Total classes: ";
            cin >> classes_size;
            applyKMeans(data, *grapher, classes_size);
            break;
        }
        case 3:
        {
            cout << "Total classes: ";
            cin >> classes_size;
            applyAgglomerativeHierarchical(data, *grapher, classes_size);
            break;
        }
        case 4:
        {
            applyAgglomerativeChaining(data, *grapher);
            break;
        }
        default:
            cout << "Opción no válida.\n";
        }

        for (Circle &circle : (*grapher).getCircles())
            circle.shape.setFillColor(Color(0, 0, 0));

    } while (option != 0);

    return 0;
}
