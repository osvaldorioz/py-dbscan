#include <vector>
#include <cmath>
#include <queue>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

// Función para calcular la distancia euclidiana entre dos puntos
double euclidean_distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    return std::sqrt(sum);
}

// Clase DBSCAN
class DBSCAN {
public:
    DBSCAN(double eps, int min_samples) : eps(eps), min_samples(min_samples) {}

    std::vector<int> fit(const std::vector<std::vector<double>>& data) {
        int cluster_id = 0;
        int n_points = data.size();
        std::vector<int> labels(n_points, -1); // -1: no visitado

        for (int i = 0; i < n_points; ++i) {
            if (labels[i] != -1) continue; // Saltar si ya fue visitado

            // Encontrar vecinos
            std::vector<int> neighbors = region_query(data, i);

            if (neighbors.size() < min_samples) {
                labels[i] = -2; // Marcar como ruido
            } else {
                ++cluster_id;
                expand_cluster(data, labels, i, neighbors, cluster_id);
            }
        }

        return labels;
    }

private:
    double eps;
    int min_samples;

    // Función para buscar vecinos dentro de eps
    std::vector<int> region_query(const std::vector<std::vector<double>>& data, int index) {
        std::vector<int> neighbors;
        for (size_t i = 0; i < data.size(); ++i) {
            if (euclidean_distance(data[index], data[i]) <= eps) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    // Expandir el cluster
    void expand_cluster(const std::vector<std::vector<double>>& data, std::vector<int>& labels, int point_index, const std::vector<int>& neighbors, int cluster_id) {
        std::queue<int> neighbor_queue;
        for (int neighbor : neighbors) {
            neighbor_queue.push(neighbor);
        }

        labels[point_index] = cluster_id;

        while (!neighbor_queue.empty()) {
            int current_point = neighbor_queue.front();
            neighbor_queue.pop();

            if (labels[current_point] == -2) {
                labels[current_point] = cluster_id; // Cambiar de ruido a cluster actual
            }
            if (labels[current_point] != -1) continue;

            labels[current_point] = cluster_id;
            std::vector<int> current_neighbors = region_query(data, current_point);

            if (current_neighbors.size() >= min_samples) {
                for (int neighbor : current_neighbors) {
                    if (labels[neighbor] == -1) {
                        neighbor_queue.push(neighbor);
                    }
                }
            }
        }
    }
};

// Exponer la clase a Pybind11
PYBIND11_MODULE(dbscan, m) {
    py::class_<DBSCAN>(m, "DBSCAN")
        .def(py::init<double, int>())
        .def("fit", &DBSCAN::fit, "Entrena el modelo DBSCAN y devuelve etiquetas de cluster.",
             py::arg("data"));
}
