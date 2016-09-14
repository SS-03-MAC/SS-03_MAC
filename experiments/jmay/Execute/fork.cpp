#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/signal.h>
#include <cstring>

int main(int argc, char* argv[]) {
    int pipein[2]; // from the parent's view
    int pipeout[2];
    pipe(pipein);
    pipe(pipeout);

    int f = fork();
    printf("%d\n", f);
    if (f == 0) {
        // Child
        dup2(pipeout[0], STDIN_FILENO);
        dup2(pipein[1], STDOUT_FILENO);
        dup2(pipein[1], STDERR_FILENO);
        execl("./executee.exe", "executee", (char *) NULL);
        exit(1);
    } else {
        // Parent
        char buf[200];
        sprintf(buf, "I'm testing stdin\n");
        write(pipeout[1], buf, strlen(buf));
        // fflush?
        ssize_t r = read(pipein[0], buf, sizeof(buf));
        buf[r] = '\0';
        printf("Received: %s\n", buf);
        kill(f, SIGKILL);
    }
}