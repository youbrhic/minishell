/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:57:53 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/22 10:21:54 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	getindexqoute(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if ((i + 1 < ft_strlen(str) && str[i] == '\\')
			&& (is_quot(str[i + 1])))
			return (i);
	}
	return (-1);
}

static char	*ft_skipquote(char *str1, char *str2, int *index)
{
	int		i;
	char	*new_str;
	char	*tmp;
	int		size;
	char	c;

	new_str = ft_strndup(str2, ft_strlen(str2));
	(*index)++;
	i = *index + 1;
	c = str1[*index];
	size = 0;
	while (str1[++(*index)] && !(*index + 1 < ft_strlen(str1)
			&& str1[*index] == '\\' && str1[*index + 1] == c))
		size++;
	tmp = ft_strndup(&str1[i], size);
	new_str = ft_strjoin(new_str, tmp);
	if (str1[*index])
		(*index)++;
	return (free(tmp), free(str2), new_str);
}

static char	*getword(char *str, char *str2, int *i)
{
	char	*new_str;
	char	*tmp;
	int		nb;

	new_str = ft_strndup(str2, ft_strlen(str2));
	nb = *i;
	while (str[*i] && !(*i + 1 < ft_strlen(str)
			&& str[*i] == '\\' && is_quot(str[*i + 1])))
		(*i)++;
	tmp = ft_strndup(&str[nb], *i - nb);
	new_str = ft_strjoin(new_str, tmp);
	if (str[*i])
		(*i)--;
	return (free(tmp), free(str2), new_str);
}

static char	*ft_remove(char *str)
{
	int		i;
	char	*new_str;

	i = -1;
	new_str = ft_strndup("", 1);
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if ((i + 1 < ft_strlen(str) && str[i] == '\\' && is_quot(str[i + 1])))
			new_str = ft_skipquote(str, new_str, &i);
		else
			new_str = getword(str, new_str, &i);
		if (str[i] == '\0')
			break ;
	}
	return (new_str);
}

int	ft_remove_quotes(char **token)
{
	int		i;
	char	*tmp;

	i = -1;
	while (token[++i])
	{
		if (getindexqoute(token[i]) >= 0 && (i == 0
				|| (i - 1 >= 0 && ft_strcmp(token[i - 1], "<<"))))
		{
			tmp = ft_remove(token[i]);
			if (!tmp)
				return (ft_perror("Error"), 0);
			free(token[i]);
			token[i] = tmp;
		}
	}
	return (1);
}
