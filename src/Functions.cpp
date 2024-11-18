#include "Functions.h"

// Define `rd` y `engine` en este archivo.
std::random_device rd;
std::mt19937 engine(rd()); // Inicialización del generador con una semilla única

std::string readFile()
{
    const char *filterPatterns[] = {"*.png", "*.jpg", "*.bmp"};
    const char *filePath = tinyfd_openFileDialog(
        "Select a file",
        "./resources/images/a",
        3,
        filterPatterns,
        nullptr,
        0
    );

    return filePath ? std::string(filePath) : "";
}

int randomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}
