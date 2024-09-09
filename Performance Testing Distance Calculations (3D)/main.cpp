#include <iostream>
#include <vector>
#include "tests.h"

// Implementierung der Methoden der DistanceCalculator-Klasse
float DistanceCalculator::distance_v3(const Vector3& point1, const Vector3& point2) {
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) +
        (point1.y - point2.y) * (point1.y - point2.y) +
        (point1.z - point2.z) * (point1.z - point2.z));
}

float DistanceCalculator::distance_v3_alt(const Vector3& point1, const Vector3& point2) {
    float dx = point1.x - point2.x;
    float dy = point1.y - point2.y;
    float dz = point1.z - point2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

float DistanceCalculator::distance_v3_hypot(const Vector3& point1, const Vector3& point2) {
    float dx = point1.x - point2.x;
    float dy = point1.y - point2.y;
    float dz = point1.z - point2.z;
    return std::hypot(std::hypot(dx, dy), dz);
}

int main() {
    DistanceCalculator calculator;
    int num_iterations = 1000;

    // Vektor zum Speichern der Messungen
    std::vector<Measurement> measurements;

    // Zeitmessung für die verschiedenen Methoden
    measure_time(&calculator, &DistanceCalculator::distance_v3, "distance_v3", num_iterations, measurements);
    measure_time(&calculator, &DistanceCalculator::distance_v3_alt, "distance_v3_alt", num_iterations, measurements);
    measure_time(&calculator, &DistanceCalculator::distance_v3_hypot, "distance_v3_hypot", num_iterations, measurements);

    // Ausgabe der Ergebnisse
    print_results(measurements);

    return 0;
}
