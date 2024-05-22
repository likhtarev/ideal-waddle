#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
    const char* file_name = "/tmp/communication_file";
    const int FILE_SIZE = 4096;

    int fd = shm_open(file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, FILE_SIZE);
    void* shared_memory = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_t* semaphore = sem_open("communication_semaphore", O_CREAT, 0644, 1);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        while (true) {
            sem_wait(semaphore);
            std::string message;
            std::cout << "Enter a message to send: ";
            std::getline(std::cin, message);
            std::copy(message.begin(), message.end(), static_cast<char*>(shared_memory));
            sem_post(semaphore);
        }
    } else {
        // Parent process
        while (true) {
            sem_wait(semaphore);
            std::string receivedMessage(static_cast<char*>(shared_memory));
            if (!receivedMessage.empty()) {
                std::cout << "Received message: " << receivedMessage << std::endl;
                // Clear the shared memory for the next message
                std::fill_n(static_cast<char*>(shared_memory), FILE_SIZE, 0);
            }
            sem_post(semaphore);
        }
    }

    munmap(shared_memory, FILE_SIZE);
    shm_unlink(file_name);
    sem_close(semaphore);
    sem_unlink("communication_semaphore");

    return 0;
}
