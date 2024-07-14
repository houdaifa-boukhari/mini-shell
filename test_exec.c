#include "execution/mini_shell.h"

int	count_cmds(t_args_n *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int main(int argc, char **argv, char **envp)
{
    t_envp *env = NULL;
    t_envp *pos;

    parsing_env(&env, envp);
    pos = search_env(env, "NAME");
    if (!pos)
        printf("NULL");
    else
        printf("%s\n", pos->env);
}