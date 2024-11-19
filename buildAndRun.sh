clear

g++ -c -I./include src/tinyfiledialogs.c     -o build/tinyfiledialogs.o
g++ -c -I./include src/Functions.cpp         -o build/Functions.o
g++ -c -I./include src/gui/Grapher.cpp       -o build/Grapher.o
g++ -c -I./include src/clustering/KMeans.cpp -o build/KMeans.o
g++ -c -I./include main.cpp                  -o build/main.o

g++ build/tinyfiledialogs.o build/Functions.o build/Grapher.o build/KMeans.o build/main.o \
    -o build/main.exe -Iinclude -lsfml-graphics -lsfml-window -lsfml-system

./build/main.exe
