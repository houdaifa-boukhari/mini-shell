


#include "min.h"


static char  * search_env(t_envp *env, char *str)
{
	char	*s1;
	int		len_str;

	len_str = ft_strlen(str);
	while (env)
	{
		if (!ft_strncmp(env->env, str, len_str) && *(env->env + len_str) == '=')
			return (env->env + len_str + 1);
		env = env->next;
	}
	return (NULL);
}

static char *get_valu_of_var(char *str,int *j)
{
    char *re;
    int x =0;
    int is_v=0;
    int i=0;
    while (str[x])
    {

        if(is_v)
        {
            if(str[x]==' ' ||  str[x]=='\''|| str[x]=='"')
                break;
            i++;
            (*j)++;
        }
        if(str[x]=='$')
            is_v =1;
        x++;
    }
    re=malloc(i+1);
    // printf("%d\n",i);
    i =0;
    x =0;
    is_v =0;
    while (str[x])
    {

        if(is_v)
        {
            if(str[x]==' ' ||  str[x]=='\''|| str[x]=='"')
                break;
            re[i++]=str[x];
        }
        if(str[x]=='$')
            is_v =1;
        x++;
    }
    re[i]='\0';
    // (*j)++;
    return re;
}


char *change_var(char * str,int *err)
{
    char *re;
    int x =0;
    int q=0;
    int qq=0;
    char * var= NULL;
    int i=0;
    int  j =0;

    while (str[x])
    {
        if (str[x] == '\'' ||  str[x] == '"') 
        {
            if(qq ==0)
            {
                q=str[x];
                qq++;
            }
            else if (q==str[x])
            {
                qq=0;
                q=0;            
            }
            
            // sing_q= !sing_q;
        }
    // printf("%c",str[x]);
        // printf("\nq=%c|\n",q);
       if(str[x]=='$'&& q!='\'' && str[x+1]&& str[x+1]!=' ' && str[x+1]!='$')
        {
            if(str[x+1]=='?')
            {
                char *ll =ft_itoa(exit_status);
                i+=ft_strlen(ll);
                x += 1;
                free(ll);
            }
            else if(str[x+1]&& (str[x+1]==' ' ||  str[x+1]=='\''|| str[x+1]=='"'))
            {
                // if((str[x+1]=='"' || str[x+1]=='\''))
                //     x++;
            }
            else   
            {
                // printf("v=%s\n",(get_valu_of_var(str+x)));
                // var = search_env(env,get_valu_of_var(str+x,&x));
                char *ss= get_valu_of_var(str+x,&x);
                var = getenv(ss);
                free(ss);
                // // printf("dd%s\n",var);
                i+=ft_strlen(var);
                ///"| c   qw 23"
                j =0;
                if(q!='"')
                    i++;
                while (q!='"'&&var && var[j])
                {
                    if(j-1>=0&&q!='"' && var[j-1]==' ' &&var[j]!=' ')
                        i++;
                    // if(j-1>=0&&q!='"' && var[j-1]!=' ' &&var[j]==' ')
                    //     re[i++]='"';
                    
                    if(q!='"' && var[j]!=' ' &&(var[j+1]==' '|| var[j+1]=='\0'))
                        i++;
                    j++;
                }
                
                
            
                
            }
        
        
        }
        else    
        {
            i++;
            // printf("%c",str[x]);
        }
        x++;
        
    }
    // printf("%d\n",i);
    // if(q!='"')
    //     i+=2;
    re =malloc (i+1);
    x =0;
    i =0;
    q=0;
    qq=0;
     j =0;
    while (str[x])
    {
        if (str[x] == '\'' ||  str[x] == '"') 
        {
            if(qq ==0)
            {
                q=str[x];
                qq++;
            }
            else if (q==str[x])
            {
                qq=0;
                q=0;            
            }
            
            // sing_q= !sing_q;
        }
    // printf("%c",str[x]);
        // printf("\nq=%c|\n",q);
        if(str[x]=='$'&& q!='\'' && str[x+1]&& str[x+1]!=' ' && str[x+1]!='$')
        {
            if(str[x+1]=='?')
            {
                // i+=ft_strlen(ft_itoa(exit_status));
                char *sss= ft_itoa(exit_status);
                int a =0;
                while (sss[a])
                {
                    re[i++]=sss[a++];
                }
                free(sss);

                
                x +=1;
            }
            else if(str[x+1]&& (str[x+1]==' ' ||  str[x+1]=='\''|| str[x+1]=='"'))//|$ |
            {
                // if((str[x+1]=='"' || str[x+1]=='\''))
                //     x++;
            }
            else   
            {





                j =x;
                // printf("v=%s\n",(get_valu_of_var(str+x)));
               
                char *ss= get_valu_of_var(str+x,&x);
                var = getenv(ss);
                free(ss);


                /////error

                int l =0;
                int k =0;
                while (var &&var[l])
                {
                    if(var[l]==' ')
                    {
                        k =1;
                        break;
                    }
                    l++;
                }
                l =j;
                if (q!='"'&&  str[x])
                {
                    while (l>=0)
                    {
                        
                        l--;
                        //  printf("%c\n",str[l]);   
                        if((str[l]=='>'||str[l]=='<' ))
                        {
                            if((!var || k))
                                *err = 1;
                        }

                        if(str[l]!=' ')
                            break;
                        


                        
                    }
                    
                    

                    
                    
                }
                


                //////////
                // var = search_env(env,get_valu_of_var(str+x,&x));
                j =0;
                if( var && var[j] && q!='"')
                    re[i++]='"';
                while (var && var[j])
                {
                    if(j-1>=0&&q!='"' && var[j-1]==' ' &&var[j]!=' ')
                        re[i++]='"';
                    // if(j-1>=0&&q!='"' && var[j-1]!=' ' &&var[j]==' ')
                    //     re[i++]='"';
                    re[i++]=var[j];
                    if(q!='"' && var[j]!=' ' &&(var[j+1]==' '|| var[j+1]=='\0'))
                        re[i++]='"';
                    j++;
                }

                // string   |
                // string|
                // if(q!='"')
                //     re[i++]='"';
                
            
                
            }
        
        
        }
        else    
        {
            re[i++]= str[x];
        }
        x++;
        
    }
    re[i]='\0';
    return re;
}


// int main()
// {
//     t_envp *env=NULL;
//     char *str  = "ll $$ $ARG dd";
//     char *ss= "ll $$ \"echo\" \"|\" \"ls'\" '-l\"    \">\"    \"'\"  \"cat\"   dd";
//     printf("%s\n",str);
//     printf("%s\n",change_var(str));
// }