#include "tests.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <numeric>  // Für std::accumulate und std::inner_product
#include <cmath>    // Für std::sqrt
#include <unordered_map>

// ANSI-Escape-Sequenzen für Farbcodes
const std::string RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";
const std::string RESET = "\033[0m";

// Implementierung der Funktion measure_time bleibt unverändert
#include "tests.h"
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

void measure_time(DistanceCalculator* calculator,
    float (DistanceCalculator::* distance_func)(const Vector3&, const Vector3&),
    const std::string& func_name,
    int num_iterations,
    std::vector<Measurement>& measurements) {
    std::vector<Vector3> points1;
    std::vector<Vector3> points2;

    for (int i = 0; i < 1000; ++i) {
        points1.push_back({ static_cast<float>(i), static_cast<float>(i * 2), static_cast<float>(i * 3) });
        points2.push_back({ static_cast<float>(i + 1), static_cast<float>(i * 2 + 1), static_cast<float>(i * 3 + 1) });
    }

    int num_tests = static_cast<int>(points1.size());
    double total_time = 0.0;
    double total_result = 0.0;
    std::vector<double> results;

    for (int iter = 0; iter < num_iterations; ++iter) {
        for (int i = 0; i < num_tests; ++i) {
            Vector3 p1 = points1[i];
            Vector3 p2 = points2[i];

            auto start = std::chrono::high_resolution_clock::now();
            float dist = (calculator->*distance_func)(p1, p2);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            total_time += duration.count();
            total_result += dist;
            results.push_back(dist);
        }
    }

    // Durchschnittliche Zeit und Ergebnis speichern
    double avg_time = total_time / (num_tests * num_iterations);
    double avg_result = total_result / (num_tests * num_iterations);

    measurements.push_back({ func_name, avg_time, avg_result, results });
}

// Hilfsfunktion zum Berechnen des Modus
double calculate_mode(const std::vector<double>& values) {
    std::unordered_map<double, int> frequency_map;

    // Häufigkeit jedes Wertes zählen
    for (double value : values) {
        frequency_map[value]++;
    }

    // Finde den Wert mit der höchsten Häufigkeit
    double mode = values[0];
    int max_count = 0;
    for (const auto& pair : frequency_map) {
        if (pair.second > max_count) {
            max_count = pair.second;
            mode = pair.first;
        }
    }

    return mode;
}

void print_results(const std::vector<Measurement>& measurements) {
    // Definiere die Spaltenbreiten
    const int function_width = 25;
    const int time_width = 20;
    const int result_width = 20;

    // Header ausgeben
    std::cout << std::setw(function_width) << std::left << "Function"
        << std::setw(time_width) << "             Avg Time (s)"
        << std::setw(result_width) << "                 Avg Result" << std::endl;
    std::cout << std::string(function_width + time_width + result_width + 20, '--') << std::endl;

    // Bestimme die minimale Zeit
    double min_time = std::min_element(measurements.begin(), measurements.end(),
        [](const Measurement& a, const Measurement& b) {
            return a.average_time < b.average_time;
        })->average_time;

    std::vector<double> all_results;
    for (const auto& measurement : measurements) {
        all_results.insert(all_results.end(), measurement.results.begin(), measurement.results.end());
    }

    // Berechne den Modus für die Ergebnisse
    double mode_result = calculate_mode(all_results);

    for (const auto& measurement : measurements) {
        // Färbe die Zeit grün, wenn sie die minimale Zeit ist
        std::string time_color = (measurement.average_time == min_time) ? GREEN : RED;
        // Färbe das Ergebnis rot, wenn es sich vom Modus unterscheidet
        std::string result_color = (measurement.average_result != mode_result) ? RED : RESET;

        std::cout << std::setw(function_width) << std::left << measurement.function_name
            << std::setw(time_width) << std::right << time_color << std::fixed << std::setprecision(10) << measurement.average_time << RESET
            << std::setw(result_width) << std::right << result_color << std::fixed << std::setprecision(10) << measurement.average_result << RESET
            << std::endl;
    }
}
