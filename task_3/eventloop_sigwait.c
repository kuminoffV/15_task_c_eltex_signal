#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int signum) {
    if (signum == SIGUSR1) {
        printf("SIGUSR1 has arrived!\n");
    }
}

int main() {
    struct sigaction sa;
    sigset_t sigset;

    // Настраиваем обработчик сигнала SIGUSR1
    sa.sa_handler = handle_sigusr1;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Настраиваем набор сигналов для sigwait (только SIGUSR1)
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);

    printf("Waiting for SIGUSR1...\n");

    // Цикл обработки событий
    int sig;
    while (1) {
        // Ожидаем сигнал
        if (sigwait(&sigset, &sig) == -1) {
            perror("sigwait");
            exit(EXIT_FAILURE);
        }

        // Обработка сигнала
        if (sig == SIGUSR1) {
            printf("SIGUSR1 has arrived!\n");
        }
    }

    return 0;
}

