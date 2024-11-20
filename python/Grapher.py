import json
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Leer los datos desde el archivo JSON
with open("build/data.json", "r") as file:
    data = json.load(file)

# Obtener los puntos de firstClass
first_class = data["firstClass"]

# Separar las coordenadas en listas x, y, z para graficar
x_first = [point[0] for point in first_class]
y_first = [point[1] for point in first_class]
z_first = [point[2] for point in first_class]

# Obtener los puntos de secondClass
second_class = data["secondClass"]

# Separar las coordenadas en listas x, y, z para graficar
x_second = [point[0] for point in second_class]
y_second = [point[1] for point in second_class]
z_second = [point[2] for point in second_class]

# Obtener el plano (ajustar el rango de la malla de puntos para [0, 1])
x_vals = np.linspace(0, 255, 100)  # Rango para x (ajustado)
y_vals = np.linspace(0, 255, 100)  # Rango para y (ajustado)
x_grid, y_grid = np.meshgrid(x_vals, y_vals)
weights = data["weights"]

# Calcular z usando la ecuación del plano (Ax + By + Cz = D)
z_grid = (-weights[3] - weights[0]*x_grid - weights[1]*y_grid) / weights[2]

# Configurar la gráfica en 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Graficar los puntos de la primera clase en 3D (color azul)
ax.scatter(x_first, y_first, z_first, c='blue', marker='o', label="First Class")

# Graficar los puntos de la segunda clase en 3D (color rojo)
ax.scatter(x_second, y_second, z_second, c='red', marker='o', label="Second Class")

# Graficar el plano
ax.plot_surface(x_grid, y_grid, z_grid, color='green', alpha=0.5, label="Plane")

# Etiquetas de los ejes
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Título y leyenda
ax.set_title("3D Scatter Plot of First and Second Class Points with Plane")
ax.legend()

# Establecer límites para el cubo de 1x1x1
ax.set_xlim([0, 255])
ax.set_ylim([0, 255])
ax.set_zlim([0, 255])

# Mostrar la gráfica
plt.show()
