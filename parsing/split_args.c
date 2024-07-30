/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-24 15:52:14 by zbakkas           #+#    #+#             */
/*   Updated: 2024-07-24 15:52:14 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

//1=>'  2=>"
int	chacke_q(char c, t_quote *q)
{
	if (c == '"' && !q->inSingleQuote)
		q->inDoubleQuote = !q->inDoubleQuote;
	else if (c == '\'' && !q->inDoubleQuote)
		q->inSingleQuote = !q->inSingleQuote;
	if (!q->inDoubleQuote && !q->inSingleQuote)
		return (0);
	else if (!q->inDoubleQuote && q->inSingleQuote)
		return (1);
	else if (q->inDoubleQuote && !q->inSingleQuote)
		return (2);
	else
		return (3);
}

static	int	c_word(char *s, char c)
{
	size_t	x;
	int		re;
	t_quote	q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	x = 0;
	re = 0;
	if (!s[x])
		return (0);
	if (s[x] && c == '\0')
		return (1);
	while (s[x] == c)
		x++;
	if (s[x] == '\0')
		return (0);
	while (s[x])
	{
		if (!chacke_q(s[x], &q) && c == s[x] && c != s[x + 1]
			&& x < ft_strlen(s) - 1)
			re++;
		x++;
	}
	return (re + 1);
}

static char	*word(char *s, char c, int *x)
{
	int		i;
	char	*re;
	int		j;
	t_quote	q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	i = 0;
	while (s[*x] == c)
		(*x)++;
	while (s[(*x) + i])
	{
		if (!chacke_q(s[*x + i], &q) && s[(*x) + i] == c)
			break ;
		i++;
	}
	re = malloc (i + 1);
	if (!re)
		return (NULL);
	j = 0;
	while (i > j)
		re[j++] = s[(*x)++];
	re[j] = '\0';
	return (re);
}

char	**split_part(char *s)
{
	char	**re;
	int		x;
	int		j;
	int		t;

	x = 0;
	j = 0;
	if (!s)
		return (free(s), NULL);
	t = c_word(s, ' ');
	re = (char **)malloc((1 + t) * sizeof(char *));
	if (!re)
		return (NULL);
	while (j < t)
	{
		re[j] = word(s, ' ', &x);
		j++;
	}
	re[j] = NULL;
	free(s);
	return (re);
}

// int main()
// {
//     char *str0 ="ls \"\" -a \"\" -l";
//     char *str1 ="l\"s\"> \"hello  <'worde\"  \"-l -a\" \"\">\"\" 'out'";
//     char *str2 ="l\"s\"< 'hello  \">> worde'  \"-l -a\">> out >f";
//     char *str3 ="'cat'\"<\" \" min '2\" -e";
//     printf("%s\n",str3);
//    printf("%s\n", set_speece(str3));
// char ** str =split_part(set_speece(str3));
// int x =0;
// while (str[x])
// {
//     printf("%s\n",str[x]);
//     x++;
// }
// }