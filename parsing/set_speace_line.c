#include "min.h"


char *set_speece(char *str) 
{
    char *re;
    int x = 0;
    int i = 0;
    t_quote q = {0, 0};
    
    // First pass: calculate new length
    int newLen = ft_strlen(str);
    while (str[x]) 
    {
        if (!chacke_q(str[x], &q) && (str[x] == '>' || str[x] == '<')) 
        {
            newLen += 2; // add space before and after
            while (str[x] == '>' || str[x] == '<') {
                x++;
            }
        } 
        else 
            x++;
        
    }

    re = malloc(newLen + 1);

    // Second pass: construct the new string
    x = 0;
    q.inDoubleQuote = 0;
    q.inSingleQuote = 0;
    while (str[x]) 
    {
        if (!chacke_q(str[x], &q) && (str[x] == '>' || str[x] == '<'))
        {
            re[i++] = ' ';
            while (str[x] == '>' || str[x] == '<') 
            {
                re[i++] = str[x++];
            }
            re[i++] = ' ';
        } 
        else 
            re[i++] = str[x++];
    }

    re[i] = '\0';
    return re;
}
