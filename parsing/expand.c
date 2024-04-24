/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:14 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/24 08:12:57 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_index_dollar(char *str, int flag)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && flag)
		{
			while (str[i] && str[++i] != '\'')
				;
		}
		else if (str[i] && str[i] == '\"')
		{
			while (str[i] && str[++i] != '\"')
			{
				if (str[i] == '$')
					return (i);
			}
		}
		else if (str[i] == '$')
			return (i);
	}
	return (-1);
}

static char	*ft_expenv(char *str, int *i, char *word, int index)
{
	char	*tmp;
	char	*new_str;

	new_str = ft_strndup(word, ft_strlen(word));
	if (str[*i] == '?')
	{
		tmp = ft_itoa(g_exit_state);
		new_str = ft_strjoin(new_str, tmp);
		(*i)++;
		free(tmp);
	}
	else
	{
		tmp = ft_strndup(&str[index + 1], *i - index - 1);
		if (getenv(tmp))
			new_str = ft_strjoin(new_str, getenv(tmp));
		else
			new_str = ft_strjoin(new_str, "");
		free(tmp);
	}
	return (free(word), new_str);
}

static char	*ft_strenv(char *str, int index)
{
	int		i;
	char	*tmp;
	char	*new_str;

	tmp = ft_strndup(str, index);
	new_str = ft_strndup("", 1);
	new_str = ft_strjoin(new_str, tmp);
	i = index;
	while (str[++i] && !is_space(str[i]) && str[i] != '$')
		;
	new_str = ft_expenv(str, &i, new_str, index);
	index = i;
	if (str[i])
	{
		while (str[++i])
			;
		free(tmp);
		tmp = ft_strndup(&str[index], i);
		new_str = ft_strjoin(new_str, tmp);
	}
	return (free(str), free(tmp), new_str);
}

void	expand(char **token, int flag)
{
	int		i;
	int		j;

	i = -1;
	while (token[++i])
	{
		if ((i > 0 && !ft_strcmp(token[i - 1], "<<") && flag)
			|| get_index_dollar(token[i], flag) < 0)
			continue ;
		else
		{
			j = get_index_dollar(token[i], flag);
			token[i] = ft_strenv(token[i], j);
			i--;
		}
	}
}
