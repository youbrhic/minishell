#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0)
    {
        // Child process
        char *args[] = {"ls", "-l", NULL};
        FILE *file = fopen("output.txt", "a");
        if (file == NULL) {
            perror("fopen");
            return 1;
        }
        // Redirect stdout to the file
        dup2(fileno(file), STDOUT_FILENO);
        fclose(file);
        execvp("ls", args);
        perror("execvp");
        return 1;
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
