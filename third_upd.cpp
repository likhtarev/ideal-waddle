#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <semaphore.h>

// Функция для записи сообщения в файл
void writeMessageToFile(const std::string& message, sem_t* semaphore) {
    sem_wait(semaphore); // Ожидание доступа к файлу (ожидание семафора)
    
    std::ofstream file("chat_log.txt", std::ios_base::app); // Открытие файла для добавления сообщения в конец файла
    file << "Собеседник: " << message << std::endl; // Запись сообщения в файл
    file.close(); // Закрытие файла

    sem_post(semaphore); // Освобождение доступа к файлу (увеличение семафора)
}

// Функция для чтения сообщений из файла и вывода на экран
void readMessagesFromFile() {
    std::ifstream file("chat_log.txt");
    if (file.is_open()) {
        std::string message;
        while (std::getline(file, message)) {
            std::cout << message << std::endl;
        }
        file.close();
    } else {
        std::cout << "Файл с чатом не найден." << std::endl;
    }
}

int main() {
    sem_t* semaphore = sem_open("chat_semaphore", O_CREAT, 0644, 1); // Создание и инициализация семафора

    readMessagesFromFile(); // Чтение сообщений из файла

    std::string message;
    while (true) {
        std::cout << "Введите ваше сообщение (или 'exit' для выхода): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }

        writeMessageToFile(message, semaphore); // Запись сообщения в файл
    }

    sem_close(semaphore); // Закрытие семафора
    sem_unlink("chat_semaphore"); // Удаление семафора

    return 0;
}
