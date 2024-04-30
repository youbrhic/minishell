/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:57:53 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/30 04:46:34 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	getindexqoute(char *str)
{
	int		i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	}
	return (0);
}

static char *ft_skipquote(char *str1, char *str2, int *index)
{
	int		i;
	char	*new_str;
	char	*tmp;
	char	c;

	new_str = ft_strndup(str2, ft_strlen(str2));
	i = *index + 1;
	c = str1[*index];
	while (str1[++(*index)] && str1[*index] != c)
		;
	tmp = ft_strndup(&str1[i], *index - i);
	new_str = ft_strjoin(new_str, tmp);
	if (str1[*index] == c)
		(*index)--;
	return (free(tmp), free(str2), new_str);
}

static char *getwordquote(char *str, char *str2, int *i)
{
	char	*new_str;
	char	*tmp;
	int		nb;

	new_str = ft_strndup(str2, ft_strlen(str2));
	nb = *i;
	while (str[*i] && !is_quot(str[*i]))
		(*i)++;
	tmp = ft_strndup(&str[nb], *i - nb);
	new_str = ft_strjoin(new_str, tmp);
	return (free(tmp), free(str2), new_str);
}

static char *ft_remove(char *str)
{
	int		i;
	char	*new_str;
	int		index;

	i = -1;
	new_str = ft_strndup("", 1);
	if (!new_str)
		return NULL;
	while (str[++i])
	{
		if (!is_quot(str[i]))
			new_str = getwordquote(str, new_str, &i);
		else
			new_str = ft_skipquote(str, new_str, &i);
	}
	return (free(str), new_str);
}

void	ft_remove_quotes(char **token)
{
	int		i;

	i = -1;
	while (token[++i])
	{
		if (!getindexqoute(token[i]))
			continue;
		else
		{
			token[i] = ft_remove(token[i]);
			if (!token[i])
			{
				free_mat(&token[i + 1]);
				break ;
			}
		}
	}
}
