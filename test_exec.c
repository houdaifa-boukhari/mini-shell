#include "execution/mini_shell.h"

int main(int argc, char **argv, char **env)
{
    int fd2;
    char *cmd = "/bin/cat";
    char *flags[] = {"cat", "owners" , "-e", NULL};
    char *str = getenv("PATH");
    printf("%s", str);
}