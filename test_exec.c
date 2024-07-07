#include "hel-bouk_execution/mini_shell.h"

int main(int argc, char **argv, char **env)
{
    int fd2;
    char *cmd = "/bin/cat";
    char *flags[] = {"cat", "owners" , "-e", NULL};
    char *str = NULL;

    printf("%s", str);
    // fd2 = open("out3", O_RDWR | O_APPEND | O_CREAT);
    // if (fd2 < 0)
    //     perror("out3");
    // dup2(fd2, STDOUT_FILENO);
    // close(fd2);
    // dprintf(STDOUT_FILENO, "hello taha\n");
    // execve(cmd, flags, NULL);   
}