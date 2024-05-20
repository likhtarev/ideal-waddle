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

int main() {
    sem_t* semaphore = sem_open("chat_semaphore", O_CREAT, 0644, 1); // Создание и инициализация семафора

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
