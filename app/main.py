from fastapi import FastAPI
import dbscan
import time
from pydantic import BaseModel
from typing import List
import json
import random

app = FastAPI()

# Definir el modelo para la matriz
class Matrix(BaseModel):
    matrix: List[List[float]]

# Definir el modelo para el vector
class VectorF(BaseModel):
    vector: List[float]

@app.post("/dbscan")
async def calculo(data: Matrix, eps: float,
                  min_samples: int):
    start = time.time()

    # Datos de ejemplo (2D para simplicidad)
    """data = [
        [1.0, 1.0],
        [1.2, 1.1],
        [1.1, 1.3],
        [10.0, 10.0],
        [10.1, 10.2],
        [9.9, 10.1],
        [5.0, 5.0]
    ]"""

    # Parámetros de DBSCAN
    #eps = 1.5  # Radio de vecindad
    #min_samples = 2  # Mínimo número de puntos para formar un cluster

    # Crear y entrenar el modelo DBSCAN
    model = dbscan.DBSCAN(eps, min_samples)
    labels = model.fit(data.matrix)

    # Mostrar resultados
    #print("Datos:")
    str1 = ""
    for i, point in enumerate(data):
        str1 += f"Punto {i}: {point}|"

    #print("\nEtiquetas de cluster:")
    str2 = ""
    for i, label in enumerate(labels):
        if label == -2:
            str2 += f"Punto {i}: Ruido|"
        else:
            str2 += f"Punto {i}: Cluster {label}|"



    end = time.time()

    var1 = end - start

    j1 = {
        "Time taken in seconds": var1,
        "Datos": str1,
        "Etiquetas de cluster": str2
    }
    jj = json.dumps(str(j1))

    return jj