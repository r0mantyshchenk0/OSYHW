#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static void system_error(void)
{
    _exit(2);
}

/* Obsluha ukonceni generatoru. */
static void handle_sigterm(int sig)
{
    (void)sig;

    const char msg[] = "GEN TERMINATED\n";
    if (write(STDERR_FILENO, msg, sizeof(msg) - 1) != (ssize_t)(sizeof(msg) - 1))
        _exit(2);

    _exit(0);
}

static void run_gen(int pipefd[2])
{
    if (close(pipefd[0]) == -1)
        system_error();

    if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        system_error();

    if (close(pipefd[1]) == -1)
        system_error();

    struct sigaction sa;
    sa.sa_handler = handle_sigterm;
    sa.sa_flags = 0;

    if (sigemptyset(&sa.sa_mask) == -1)
        system_error();

    if (sigaction(SIGTERM, &sa, NULL) == -1)
        system_error();

    int cnt = 0;

    while (1) {
        if (printf("OSY count %d\n", cnt++) < 0)
            system_error();

        if (fflush(stdout) == EOF)
            system_error();

        sleep(1);
    }
}

static void run_xxd(int pipefd[2])
{
    if (close(pipefd[1]) == -1)
        system_error();

    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        system_error();

    if (close(pipefd[0]) == -1)
        system_error();

    execlp("xxd", "xxd", "-p", (char *)NULL);
    system_error();
}

static int child_ok(int status)
{
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

int main(void)
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
        return 2;

    pid_t gen_pid = fork();

    if (gen_pid == -1)
        return 2;

    if (gen_pid == 0)
        run_gen(pipefd);

    pid_t xxd_pid = fork();

    if (xxd_pid == -1)
        return 2;

    if (xxd_pid == 0)
        run_xxd(pipefd);

    /* Rodic uz rouru nepotrebuje. */
    if (close(pipefd[0]) == -1)
        return 2;

    if (close(pipefd[1]) == -1)
        return 2;

    sleep(5);

    if (kill(gen_pid, SIGTERM) == -1)
        return 2;

    int gen_status;
    int xxd_status;

    if (waitpid(gen_pid, &gen_status, 0) == -1)
        return 2;

    if (waitpid(xxd_pid, &xxd_status, 0) == -1)
        return 2;

    if (!child_ok(gen_status) || !child_ok(xxd_status)) {
        printf("ERROR\n");
        return 1;
    }

    printf("OK\n");
    return 0;
}
