/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:14 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/24 17:01:35 by youbrhic         ###   ########.fr       */
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
		else if (str[i] == '$' && (i + 1 < ft_strlen(str) && (is_alphanum(str[i + 1]) 
			|| str[i + 1] == '?' || str[i + 1] == '_')))
			return (i);
	}
	return (-1);
}

static char	*ft_expenv(char *str, int *i, char *word, int index)
{
	char	*tmp;
	char	*new_str;

	new_str = ft_strndup(word, ft_strlen(word));
	if (str[*i] >= '0' && str[*i] <= '9')
		(1) && (new_str = ft_strjoin(new_str, ""), (*i)++);
	else if (str[*i] == '_')
		(1) && (new_str = ft_strjoin(new_str, getenv("_")), (*i)++);
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

static char *add_rest_word(char *str, char *str2, int *i, int index)
{
	char	*new_str;
	char	*tmp;

	while (str[++(*i)])
			;
	new_str = ft_strndup(str2, ft_strlen(str2));
	tmp = ft_strndup(&str[index], *i);
	new_str = ft_strjoin(new_str, tmp);
	return (free(tmp), free(str2), new_str);
}

static char	*ft_strenv(char *str, int index, int exit_status)
{
	int		i;
	char	*tmp;
	char	*new_str;

	tmp = ft_strndup(str, index);
	new_str = ft_strndup("", 1);
	new_str = ft_strjoin(new_str, tmp);
	i = index;
	while (str[++i] && is_alphanum(str[i]) && (str[i] >= '9' || str[i] <= '0') && str[i] != '$')
		;
	if (str[i] == '?')
	{
		free(tmp);
		tmp = ft_itoa(exit_status);
		(1) && (new_str = ft_strjoin(new_str, tmp), i++);
	}
	else
		new_str = ft_expenv(str, &i, new_str, index);
	index = i;
	if (str[i])
		new_str = add_rest_word(str, new_str, &i, index);
	return (free(str), free(tmp), new_str);
}

void	ft_expand(char **token, int flag, int exit_status)
{
	int		i;
	int		j;

	if (!token)
		return ;
	i = -1;
	while (token[++i])
	{
		if ((i > 0 && !ft_strcmp(token[i - 1], "<<") && flag)
			|| get_index_dollar(token[i], flag) < 0)
			continue ;
		else
		{
			j = get_index_dollar(token[i], flag);
			token[i] = ft_strenv(token[i], j, exit_status);
			if (!token[i])
			{
				free_mat(&token[i + 1]);
				break;
			}
			i--;
		}
	}
}
