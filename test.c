#include "hel-bouk_execution/mini_shell.h"

int main(int argc, char **argv, char **env)
{
    char *cmd = "/bin/ls";
    char *flags[] = {"ls", "" , "-la", NULL};
    execve(cmd, flags, NULL);   
}