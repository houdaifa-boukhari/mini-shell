

#include "../mini_shell.h"



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
        while (lst->inp[i].last)
        {
            printf("file_name[%d]==>\033[0;32m%s\033[0m<==\n",i,lst->inp[i].file);            
            printf("file_type[%d]==>\033[0;32m%d\033[0m<==\n",i,lst->inp[i].typ);   
            printf("file_am[%d]==>\033[0;32m%d\033[0m<==\n",i,lst->inp[i].is_am); 
            i++;     
        }
    
        


        
        printf("-----------------------\n");
		lst = lst->next;
	}
}

