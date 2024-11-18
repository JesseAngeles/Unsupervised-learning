#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

#include "tinyfiledialogs.h"


// Declarar `engine` como `extern` para indicar que será definido en un archivo fuente.
extern std::random_device rd;
extern std::mt19937 engine;

std::string readFile();
int randomInt(int min, int max);

#endif // FUNCTIONS_H
