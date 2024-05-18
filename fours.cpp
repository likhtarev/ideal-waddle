#include <iostream>
#include <map>
#include <string>

class FileSystem {
private:
    std::map<std::string, std::string> files; // Хранение файлов в виде пары "имя файла" -> "содержимое файла"

public:
    void createFile(const std::string& fileName) {
        files[fileName] = ""; // Создание файла с пустым содержимым
        std::cout << "Файл '" << fileName << "' создан." << std::endl;
    }

    void writeFile(const std::string& fileName, const std::string& content) {
        if (files.find(fileName) != files.end()) {
            files[fileName] = content; // Запись содержимого в файл
            std::cout << "Содержимое файла '" << fileName << "' обновлено." << std::endl;
        } else {
            std::cout << "Файл '" << fileName << "' не найден." << std::endl;
        }
    }

    void readFile(const std::string& fileName) {
        if (files.find(fileName) != files.end()) {
            std::cout << "Содержимое файла '" << fileName << "': " << files[fileName] << std::endl;
        } else {
            std::cout << "Файл '" << fileName << "' не найден." << std::endl;
        }
    }

    void deleteFile(const std::string& fileName) {
        if (files.find(fileName) != files.end()) {
            files.erase(fileName); // Удаление файла
            std::cout << "Файл '" << fileName << "' удален." << std::endl;
        } else {
            std::cout << "Файл '" << fileName << "' не найден." << std::endl;
        }
    }
};

int main() {
    FileSystem fileSystem;

    fileSystem.createFile("file1.txt");
    fileSystem.writeFile("file1.txt", "Hello, World!");
    fileSystem.readFile("file1.txt");

    fileSystem.createFile("file2.txt");
    fileSystem.writeFile("file2.txt", "This is a text file.");
    fileSystem.readFile("file2.txt");

    fileSystem.deleteFile("file1.txt");
    fileSystem.readFile("file1.txt");

    return 0;
}
