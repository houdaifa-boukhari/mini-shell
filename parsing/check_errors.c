


#include "min.h"


// ls >>    <|
int check_errors(char *str,int err)
{

    int x =0;
    int l;
    t_quote q = {0, 0};

    while (str[x])
    {
        l=chacke_q(str[x],&q);
        // printf("l=%d\n",l);
        if(!l && !str[x+1] && str[x] == '|')
        {
            printf("%s `%c'\n",TOKENS_ERROR,str[x++]);
            return 1;
        }
        else if(!l&&(str[x] == '<' || str[x] == '>'))
        {
            x++;
            if(str[x]==str[x-1])
                x++;
            // else   
            //     printf("%s '%c'\n",TOKENS_ERROR,str[x]);
            while (str[x]&& str[x]==' ')
                x++;
            if(!str[x])
            {
                printf("%s\n",NEW_LINE_ERROR);
                return 1;
            }
            else if(str[x]=='|' || str[x]=='<' || str[x]=='>' )
            {
                printf("%s `%c'\n",TOKENS_ERROR,str[x++]);
                return 1;
            }
        }
        else    
            x++;
        // if(chacke_q(str[x],&q))

    }
    if(l==2)
    {
        printf("%s `%c'\n",QUOTES_ERROR,'"');
        return 1;
    }
    else if(l==1)
    {
        printf("%s `%c'\n",QUOTES_ERROR,'\'');
        return 1;
    }
    if(err)
    {
        printf("%s\n",AMBIGUOUS_ERROR);
        return 1;
    }
    return 0;

}