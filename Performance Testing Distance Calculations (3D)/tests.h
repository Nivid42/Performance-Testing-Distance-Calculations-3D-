#ifndef TESTS_H
#define TESTS_H

#include <string>
#include <vector>

struct Vector3 {
    float x, y, z;
};

struct Measurement {
    std::string function_name;
    double average_time;
    double average_result;
    std::vector<double> results;  // Hinzugefügt für die Ergebnisse
};

// Klasse DistanceCalculator deklarieren
class DistanceCalculator {
public:
    float distance_v3(const Vector3& point1, const Vector3& point2);
    float distance_v3_alt(const Vector3& point1, const Vector3& point2);
    float distance_v3_hypot(const Vector3& point1, const Vector3& point2);
};

// Deklaration der Funktion measure_time, die Methoden der Klasse aufruft
void measure_time(DistanceCalculator* calculator,
    float (DistanceCalculator::* distance_func)(const Vector3&, const Vector3&),
    const std::string& func_name,
    int num_iterations,
    std::vector<Measurement>& measurements);

// Funktion zur Ausgabe der Ergebnisse
void print_results(const std::vector<Measurement>& measurements);

#endif // TESTS_H
