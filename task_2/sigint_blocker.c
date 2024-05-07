#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t newmask;  // Создаем набор сигналов

    // Инициализируем набор сигналов как пустой
    sigemptyset(&newmask);

    // Добавляем SIGINT в набор сигналов
    sigaddset(&newmask, SIGINT);

    // Блокируем SIGINT
    if (sigprocmask(SIG_BLOCK, &newmask, NULL) == -1) {  // Если произошла ошибка
        perror("sigprocmask");  // Выводим сообщение об ошибке
        exit(EXIT_FAILURE);  // Выход с кодом ошибки
    }

    // Сообщаем, что SIGINT теперь заблокирован
    printf("SIGINT теперь заблокирован. Нажатие Ctrl+C не завершит эту программу.\n");

    // Бесконечный цикл, чтобы программа продолжала работать
    while (1) {
        pause();  // Ожидание любого сигнала (кроме заблокированных, например, SIGINT)
    }

    return 0;
}

