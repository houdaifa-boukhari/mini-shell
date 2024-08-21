/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:52:14 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/21 16:42:24 by hel-bouk         ###   ########.fr       */
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

static	int	c_word(char *s)
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
	while (is_sp(s[x]))
		x++;
	if (s[x] == '\0')
		return (0);
	while (s[x])
	{
		if (!chacke_q(s[x], &q) &&  is_sp(s[x]) && !is_sp(s[x + 1])
			&& x < ft_strlen(s) - 1)
			re++;
		x++;
	}
	return (re + 1);
}

static char	*word(char *s, int *x)
{
	int		i;
	char	*re;
	int		j;
	t_quote	q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	i = 0;
	while (is_sp(s[*x]))
		(*x)++;
	while (s[(*x) + i])
	{
		if (!chacke_q(s[*x + i], &q) && is_sp(s[(*x) + i]))
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
	t = c_word(s);
	re = (char **)malloc((1 + t) * sizeof(char *));
	if (!re)
		return (NULL);
	while (j < t)
	{
		re[j] = word(s, &x);
		j++;
	}
	re[j] = NULL;
	free(s);
	return (re);
}

char*strjoin_parsing(char *start, char *buff)
{
char*re;
int xx;
int x;

x = 0;
xx = 0;
if (!start)
{
start = malloc(1);
start[0] = '\0';
}
if (!start || !buff)
return (0);
re = malloc(ft_strlen(start) + ft_strlen(buff) + 1);
if (!re)
return (NULL);
while (start[x])
re[xx++] = start[x++];
x = 0;
while (buff[x])
re[xx++] = buff[x++];
re[xx] = '\0';
free(start);
return (re);
}