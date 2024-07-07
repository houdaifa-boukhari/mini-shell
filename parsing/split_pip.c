

#include "min.h"


static char get_q(char *str)
{
    char q = '\0';
    int x =0;
    while (str[x])
    {
        if(str[x]=='\'')
            q = '\'';
        if(str[x]=='"')
            q='"';
        if(str[x]=='\''||str[x]=='"')
            return q;  
        x++;
    }
    return q;
}

static	int	c_word( char *s, char c)
{
	size_t	x;
	int		re;
    bool in_quotes = false;

	x = 0;
	re = 0;
	if (!s[x])
		return (0);
	if (s[x] && c == '\0')
		return (1);
	// while (s[x] == c)
    // {
    //     if (s[x] == '"' ) 
    //         in_quotes = !in_quotes;
	// 	x++;
    // }

    x =0;
	if (s[x] == '\0')
		return (0);
	while (s[x])
	{
        if (s[x] == get_q(s) ) 
            in_quotes = !in_quotes;
		if (c == s[x]&& !in_quotes && c != s[x + 1] && x < ft_strlen(s) - 1)
			re++;
		x++;
	}
	return (re + 1);
}

static	char	**is_free(char **d)
{
	int	x;

	x = 0;
	while (d[x])
	{
		free(d[x]);
		x++;
	}
	free(d);
	return (NULL);
}

static	char	*word(char  *s, char c, int *x)
{
	int		i;
	char	*re;
	int		j;
    bool in_quotes = false;

	i = 0;
        // char q;

    // printf("str==%s=\n",s+*x);
    // while (s[(*x)+i])
    // {
    //     if(s[(*x)+i]=='\'')
    //         q = '\'';
    //     if(s[(*x)+i]=='"')
    //         q='"';
    //     if(s[(*x)+i]=='\''||s[(*x)+i]=='"')
    //         break;  
    //     i++;
    // }
    // i =0;
	while (s[*x] == c )
		(*x)++;
	while (s[(*x) + i])
    {
        if (s[(*x) + i] == c && (!in_quotes || !get_q(s+*x)))
            break;
        if (s[(*x)+i] == get_q(s+*x) ) 
            in_quotes = !in_quotes;
		i++;
    }
    // printf("i==%d\n",i);
	re = malloc (i + 1);
	if (!re)
		return (NULL);
	j = 0;
	while (i > j)
		re[j++] = s[(*x)++];
	re[j] = '\0';
	return (re);
}

char	**ft_split_pip(char  *s, char c)
{
	char	**re;
	int		x;
	int		j;
	int		t;

	x = 0;
	j = 0;
	if (!s)
		return (NULL);
	t = c_word(s, c);
    // printf("%d\n",t);
	re = (char **)malloc((1 + t) * sizeof(char *));
	if (!re)
		return (NULL);
	while (j < t)
	{
		re[j] = word(s, c, &x);
        // printf("%s\n",s);
		if (!re[j])
			return (is_free(re));
		j++;
	}
	re[j] = NULL;
	return (re);
}


// char **get_parts_by_pip(char *str)
// {
//     char **re;

//     re = ft_split(str,'|');

    



//     return re;
// }
// int main ()
// {


//     int x =0;
// 	char *str ="> out cat -e out1 | wc -c" ;
// 	printf("cmd = %s\n",str);

//     while (ft_split_pip(str,'|')[x])
//     {

//     	printf("%s\n",ft_split_pip(str ,'|')[x]);
//         x++;
//     }
    
// }

