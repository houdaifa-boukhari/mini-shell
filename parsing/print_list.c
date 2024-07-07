

#include "min.h"



void	ft_lstiterr(t_args_n *lst)
{
	if (!lst )
		return ;
        int i =0;
	while (lst)
	{
        i =0;
		// f("cmd",lst->cmd);
        while (lst->arguments[i])
        {
            printf("arg[%d]==>\033[0;32m%s\033[0m<==\n",i,lst->arguments[i]);
            i++;
            // f("arg",lst->arguments[i++]);
        }
        i =0;
        while (lst->inp[i].inp)
        {
            printf("inp_file[%d]==>\033[0;32m%s\033[0m<==\n",i,lst->inp[i].inp);            
            printf("inp_type[%d]==>\033[0;32m%d\033[0m<==\n",i,lst->inp[i].is_h);   
            i++;     
        }
        i =0;
        while (lst->out[i].out)
        {
            printf("out_file[%d]==>\033[0;32m%s\033[0m<==\n",i,lst->out[i].out);            
            printf("out_type[%d]==>\033[0;32m%d\033[0m<==\n",i,lst->out[i].is_a);   
            i++;     
        }
        


        
        printf("-----------------------\n");
		lst = lst->next;
	}
}

