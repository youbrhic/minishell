#include <stdio.h>
#include <unistd.h>

int main() {
    // Create an array of strings for the command and its arguments
    char *args[] = {"ls", "-l", NULL};

    // Create an array of strings for the environment variables
    char *envp[] = {NULL};

    // Use execve to execute the command
    execve("/bin/ls", args, envp);

    // If execve returns, an error occurred
    perror("execve");
    return 1;
}