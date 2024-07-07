#include "./parsing/min.h"

int	main(int argc, char **argv, char **envp)
{    
    char **str = NULL;
	// t_args args;
	t_args_n *args_n =NULL;
	while (1)
	{
		clear_list(&args_n);
		char	*line = readline(get_str_redline());
		if(line[0])
		{
			args_n =initialization_list(line);
			// str = ft_split_pip(line,'|');
			// int  i =0;
			// while (str[i])
			// {
			// 	printf("%d,%s\n",i,str[i]);
			// 	ft_lstadd_backk(&args_n,ft_lstnew_one(str[i++]));
				
			// }
			ft_lstiterr(args_n);
			// printf("%s\n",args_n->next->flags[i]);
		}
		// free_to_pin(str);
		if (!strcmp(line, "exit"))
			exit(0);
		
	}


//  printf("%s\n",ft_strnstr("cat t.txt |grep e  > out","|",30));
	
	
}

// int main()
// {
//     char * str="cat text.txt | grep \"e\" > out";
//     char *ss =strdup("ls");
//     get_all(ss);
// }