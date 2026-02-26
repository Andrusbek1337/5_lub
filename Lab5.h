#ifndef LAB5_H
#define LAB5_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

class Lab5 {
public:
    // Структура для Задания 3
    struct Toy {
        std::string name;
        int price;          // стоимость в рублях
        int minAge;         // минимальный возраст
        int maxAge;         // максимальный возраст
    };

    // --- Методы для заполнения файлов ---
    static void createBinaryFileWithRandomData(const std::string& filename, int count);
    static void createBinaryFileWithToys(const std::string& filename, int count);
    static void createTextFileOnePerLine(const std::string& filename, int count);
    static void createTextFileMultiplePerLine(const std::string& filename, int count, int numbersPerLine);
    static void createTextFileWithText(const std::string& filename);

    // --- Задание 1 ---
    static int task1(const std::string& filename);

    // --- Задание 2 ---
    static std::vector<std::vector<int>> task2(const std::string& filename, int n);

    // --- Задание 3 ---
    static std::vector<std::string> task3(const std::string& filename, int k);

    // --- Задание 4 ---
    static int task4(const std::string& filename);

    // --- Задание 5 ---
    static int task5(const std::string& filename);

    // --- Задание 6 ---
    static void task6(const std::string& inputFilename, const std::string& outputFilename, const std::string& substring);

private:
    // Вспомогательные приватные методы (оканчиваются на _)
    static void ensureFileOpen_(std::ifstream& file, const std::string& filename);
    static void ensureFileOpen_(std::ofstream& file, const std::string& filename);
};

#endif // LAB5_H
