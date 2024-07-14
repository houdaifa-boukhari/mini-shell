


#include "min.h"


static char *get_var(char *str,int *j)
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


char *change_var(char * str)
{
    char *re;
    int x =0;
    int q=0;
    int qq=0;
    char * var;
    int i=0;

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
        if(str[x]=='$'&& q!='\'' && str[x+1]&& str[x+1]!=' ')
        {
            if(str[x+1]&& (str[x+1]==' ' ||  str[x+1]=='\''|| str[x+1]=='"'))
            {
                // if((str[x+1]=='"' || str[x+1]=='\''))
                //     x++;
            }
            else   
            {
                // printf("v=%s\n",(get_var(str+x)));
                var = getenv(get_var(str+x,&x));
                i+=ft_strlen(var);
                // printf("%s",var);
            
                
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
    re =malloc (i+1);
    x =0;
    i =0;
    q=0;
    qq=0;
    int j =0;
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
        if(str[x]=='$'&& q!='\'' && str[x+1]&& str[x+1]!=' ')
        {
            if(str[x+1]&& (str[x+1]==' ' ||  str[x+1]=='\''|| str[x+1]=='"'))
            {
                // if((str[x+1]=='"' || str[x+1]=='\''))
                //     x++;
            }
            else   
            {
                j =0;
                // printf("v=%s\n",(get_var(str+x)));
                var = getenv(get_var(str+x,&x));
                while (var && var[j])
                {
                    re[i++]=var[j++];
                }
                
            
                
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
//     char *str  = "ll dd$ARG\"d\"";
//     printf("%s\n",str);
//     printf("%s\n",change_var(str));
// }