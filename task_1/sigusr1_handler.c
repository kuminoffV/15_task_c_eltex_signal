#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Пользовательский обработчик сигнала для SIGUSR1
void handle_sigusr1(int signum) {
    if (signum == SIGUSR1) {  // Проверяем, что сигнал именно SIGUSR1
        printf("Программа получила SIGUSR1!\n");  // Выводим сообщение
    }
}

int main() {
    struct sigaction sa;

    // Настраиваем структуру sigaction для определения нового обработчика
    sa.sa_handler = handle_sigusr1;  // Указываем функцию-обработчик
    sa.sa_flags = 0;  // Без дополнительных флагов
    sigemptyset(&sa.sa_mask);  // Очищаем маску сигналов

    // Устанавливаем новый обработчик для SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {  // Если произошла ошибка
        perror("sigaction");  // Выводим сообщение об ошибке
        exit(EXIT_FAILURE);  // Завершаем программу с кодом ошибки
    }

    // Бесконечный цикл для ожидания сигналов
    while (1) {
        pause();  // Ожидание сигнала
    }

    return 0;
}

