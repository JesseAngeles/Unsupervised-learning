import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import dendrogram, linkage
import numpy as np

# Cargar la matriz de enlace desde el archivo CSV
linkage_matrix = np.loadtxt("resources/data/linkage.csv", delimiter=",", skiprows=1)

# Crear el dendograma
plt.figure(figsize=(10, 7))
dendrogram(linkage_matrix)
plt.title("Dendrogram")
plt.xlabel("Clusters")
plt.ylabel("Distance")
plt.show()
