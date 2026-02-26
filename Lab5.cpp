#include "Lab5.h"
#include <algorithm>
#include <sstream>
#include <climits>

// --- Реализация приватных вспомогательных методов ---

void Lab5::ensureFileOpen_(std::ifstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
    }
}

void Lab5::ensureFileOpen_(std::ofstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }
}

// --- Реализация публичных методов ---

void Lab5::createBinaryFileWithRandomData(const std::string& filename, int count) {
    std::ofstream out(filename, std::ios::binary);
    ensureFileOpen_(out, filename);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < count; ++i) {
        int num = std::rand() % 100; // случайные числа от 0 до 99
        out.write(reinterpret_cast<char*>(&num), sizeof(num));
    }
    out.close();
}

void Lab5::createBinaryFileWithToys(const std::string& filename, int count) {
    std::ofstream out(filename, std::ios::binary);
    ensureFileOpen_(out, filename);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::string names[] = {"Кукла", "Машинка", "Мяч", "Конструктор", "Пазл", "Робот", "Кубики", "Самолетик"};

    for (int i = 0; i < count; ++i) {
        Toy toy;
        toy.name = names[std::rand() % 8] + std::to_string(i);
        toy.price = 100 + std::rand() % 901; // цена от 100 до 1000
        toy.minAge = 1 + std::rand() % 5;    // от 1 до 5
        toy.maxAge = toy.minAge + 1 + std::rand() % 8; // чтобы maxAge был больше minAge

        // Запись строки: сначала длина, потом данные
        size_t len = toy.name.size();
        out.write(reinterpret_cast<char*>(&len), sizeof(len));
        out.write(toy.name.c_str(), len);
        out.write(reinterpret_cast<char*>(&toy.price), sizeof(toy.price));
        out.write(reinterpret_cast<char*>(&toy.minAge), sizeof(toy.minAge));
        out.write(reinterpret_cast<char*>(&toy.maxAge), sizeof(toy.maxAge));
    }
    out.close();
}

void Lab5::createTextFileOnePerLine(const std::string& filename, int count) {
    std::ofstream out(filename);
    ensureFileOpen_(out, filename);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < count; ++i) {
        out << std::rand() % 100 << "\n";
    }
    out.close();
}

void Lab5::createTextFileMultiplePerLine(const std::string& filename, int count, int numbersPerLine) {
    std::ofstream out(filename);
    ensureFileOpen_(out, filename);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < numbersPerLine; ++j) {
            out << std::rand() % 100;
            if (j < numbersPerLine - 1) out << " ";
        }
        out << "\n";
    }
    out.close();
}

void Lab5::createTextFileWithText(const std::string& filename) {
    std::ofstream out(filename);
    ensureFileOpen_(out, filename);

    out << "Сегодня старшеклассники выполняли ЕГЭ по информатике и ИКТ\n";
    out << "Информационные технологии окружают нас повсюду\n";
    out << "Программирование - это интересно и полезно\n";
    out << "Форма обучения может быть разной\n";
    out << "Эта строка содержит слово форма\n";
    out << "А здесь нет такого сочетания\n";
    out << "Иформатика без 'ф' - это инорматика\n";
    out.close();
}

// --- Задание 1 ---
int Lab5::task1(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    ensureFileOpen_(in, filename);

    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    int num;

    while (in.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        if (num < minVal) minVal = num;
        if (num > maxVal) maxVal = num;
    }

    if (minVal == INT_MAX || maxVal == INT_MIN) {
        throw std::runtime_error("Файл пуст или содержит недостаточно данных");
    }

    return maxVal - minVal;
}

// --- Задание 2 ---
std::vector<std::vector<int>> Lab5::task2(const std::string& filename, int n) {
    std::ifstream in(filename, std::ios::binary);
    ensureFileOpen_(in, filename);

    // Создаем матрицу n x n, заполненную нулями
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    // Читаем числа из файла и заполняем матрицу
    int num;
    int maxElement = INT_MIN;
    std::vector<int> elements;

    while (in.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        elements.push_back(num);
        if (num > maxElement) {
            maxElement = num;
        }
    }

    // Заполняем матрицу
    for (size_t i = 0; i < elements.size() && i < static_cast<size_t>(n * n); ++i) {
        matrix[i / n][i % n] = elements[i];
    }

    // Заменяем все вхождения максимального элемента на 0
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == maxElement) {
                matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

// --- Задание 3 ---
std::vector<std::string> Lab5::task3(const std::string& filename, int k) {
    std::ifstream in(filename, std::ios::binary);
    ensureFileOpen_(in, filename);

    std::vector<Toy> toys;
    int maxPrice = 0;

    // Чтение игрушек из файла
    while (in) {
        Toy toy;
        size_t len;
        if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;

        toy.name.resize(len);
        if (!in.read(&toy.name[0], len)) break;
        if (!in.read(reinterpret_cast<char*>(&toy.price), sizeof(toy.price))) break;
        if (!in.read(reinterpret_cast<char*>(&toy.minAge), sizeof(toy.minAge))) break;
        if (!in.read(reinterpret_cast<char*>(&toy.maxAge), sizeof(toy.maxAge))) break;

        toys.push_back(toy);
        if (toy.price > maxPrice) {
            maxPrice = toy.price;
        }
    }

    // Поиск игрушек, цена которых отличается от максимальной не более чем на k
    std::vector<std::string> result;
    for (const auto& toy : toys) {
        if (maxPrice - toy.price <= k) {
            result.push_back(toy.name);
        }
    }

    return result;
}

// --- Задание 4 ---
int Lab5::task4(const std::string& filename) {
    std::ifstream in(filename);
    ensureFileOpen_(in, filename);

    int num;
    int maxElement = INT_MIN;
    int count = 0;
    std::vector<int> numbers;

    // Читаем все числа и находим максимум
    while (in >> num) {
        numbers.push_back(num);
        if (num > maxElement) {
            maxElement = num;
        }
    }

    // Подсчитываем количество вхождений максимума
    for (int n : numbers) {
        if (n == maxElement) {
            count++;
        }
    }

    return count;
}

// --- Задание 5 ---
int Lab5::task5(const std::string& filename) {
    std::ifstream in(filename);
    ensureFileOpen_(in, filename);

    int num;
    int evenCount = 0;
    std::string line;

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        while (iss >> num) {
            if (num % 2 == 0) {
                evenCount++;
            }
        }
    }

    return evenCount;
}

// --- Задание 6 ---
void Lab5::task6(const std::string& inputFilename, const std::string& outputFilename, const std::string& substring) {
    std::ifstream in(inputFilename);
    ensureFileOpen_(in, inputFilename);

    std::ofstream out(outputFilename);
    ensureFileOpen_(out, outputFilename);

    std::string line;
    while (std::getline(in, line)) {
        if (line.find(substring) != std::string::npos) {
            out << line << "\n";
        }
    }

    in.close();
    out.close();
}
