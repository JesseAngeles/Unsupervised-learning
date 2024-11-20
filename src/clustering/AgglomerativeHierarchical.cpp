#include "clustering/AgglomerativeHierarchical.h"

AgglomerativeHierarchical::AgglomerativeHierarchical(std::vector<std::vector<float>> data)
    : data(data)
{
    clusters.resize(data.size());
    cluster_sizes.resize(data.size(), 1); // Cada cluster inicial tiene tamaño 1
    for (int i = 0; i < data.size(); i++)
    {
        clusters[i].insert(data[i]);  // Usamos insert, no push_back
    }
}

void AgglomerativeHierarchical::step()
{
    float min_distance = std::numeric_limits<float>::max();
    int index_a = -1;
    int index_b = -1;

    // Encontrar los clusters más cercanos
    for (size_t i = 0; i < clusters.size() - 1; i++)
    {
        for (size_t j = i + 1; j < clusters.size(); j++)
        {
            for (const auto &point_a : clusters[i])
            {
                for (const auto &point_b : clusters[j])
                {
                    float distance = euclidianDistance(point_a, point_b);
                    if (distance < min_distance)
                    {
                        min_distance = distance;
                        index_a = i;
                        index_b = j;
                    }
                }
            }
        }
    }

    // Fusionar clusters si encontramos dos candidatos válidos
    if (index_a != -1 && index_b != -1)
    {
        int new_cluster_size = cluster_sizes[index_a] + cluster_sizes[index_b];
        
        // Añadir la fusión a la matriz de enlace (con el tamaño del nuevo cluster)
        linkage_matrix.push_back({index_a, index_b, min_distance, new_cluster_size});

        // Actualiza cluster_sizes
        cluster_sizes[index_a] = new_cluster_size;
        cluster_sizes.erase(cluster_sizes.begin() + index_b);  // Eliminar el cluster b fusionado

        // Crear el nuevo cluster combinando los dos más cercanos
        for (const auto& point : clusters[index_b])
        {
            clusters[index_a].insert(point);  // Insertar los puntos del cluster b en el cluster a
        }

        // Eliminar el cluster b fusionado de la lista de clusters
        clusters.erase(clusters.begin() + index_b);
    }

    // Ahora los índices en `linkage_matrix` están correctos y no deben causar el error
}


float AgglomerativeHierarchical::euclidianDistance(const std::vector<float> &a, const std::vector<float> &b)
{
    float sum = 0.0f;
    for (int i = 0; i < a.size(); i++)
        sum += std::pow(a[i] - b[i], 2);

    return std::sqrt(sum);
}

void AgglomerativeHierarchical::saveLinkageMatrixToCSV(const std::string &filename)
{
    std::ofstream file(filename);

    // Verificar si el archivo se abrió correctamente
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << " para escritura.\n";
        return;
    }

    // Escribir encabezado
    file << "cluster_a,cluster_b,distance,size\n";

    // Escribir cada entrada de la matriz de enlace
    for (const auto &entry : linkage_matrix)
    {
        file << std::get<0>(entry) << ","   // Índice del primer cluster
             << std::get<1>(entry) << ","   // Índice del segundo cluster
             << std::get<2>(entry) << ","   // Distancia
             << std::get<3>(entry) << "\n"; // Tamaño del cluster resultante
    }

    // Cerrar el archivo
    file.close();
    std::cout << "Archivo CSV creado exitosamente: " << filename << "\n";
}

const std::vector<std::tuple<int, int, float, int>>& AgglomerativeHierarchical::getLinkageMatrix() const
{
    return linkage_matrix;
}

bool AgglomerativeHierarchical::arePointsEqual(const std::vector<float> &a, const std::vector<float> &b, float epsilon)
{
    if (a.empty() || b.empty())
    {
        std::cerr << "Error: Empty vector encountered in arePointsEqual.\n";
        return false;
    }

    if (a.size() != b.size())
    {
        std::cerr << "Error: Vectors of different sizes in arePointsEqual.\n";
        return false;
    }

    for (size_t i = 0; i < a.size(); i++)
    {
        if (std::abs(a[i] - b[i]) > epsilon)
            return false;
    }
    return true;
}
