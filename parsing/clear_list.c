#include "min.h"


void	remove_file(t_inp *inp);

void	clear_list(t_args_n **lst)
{
	t_args_n	*nexttte;
    int i =0;

	if (!lst)
		return ;
	while (*lst)
	{
        i =0;
        remove_file((*lst)->inp);
		nexttte = (*lst)->next;
        // free((*lst)->cmd);
        // free((*lst)->arguments);
        while ((*lst)->arguments[i])
        {
            free((*lst)->arguments[i++]);
        }
        free((*lst)->arguments);

		i =0;
        while ((*lst)->inp[i].inp)
        {
			free((*lst)->inp[i].inp);
            i++;
        }
		free((*lst)->inp);
        i =0;
        while ((*lst)->out[i].out)
        {
			free((*lst)->out[i].out);
            i++;     
        }
		free((*lst)->out);
		free(*lst);
		*lst = nexttte;

	}
	*lst = NULL;
}
