/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:14 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/12 05:46:14 by youbrhic         ###   ########.fr       */
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
				if (str[i] == '$' && str[i + 1] != '\"'
					&& !is_space(str[i + 1]))
					return (i);
			}
		}
		else if (str[i] == '$'
			&& (i + 1 < ft_strlen(str) && (is_alphanum(str[i + 1])
					|| str[i + 1] == '?' || str[i + 1] == '_')))
			return (i);
	}
	return (-1);
}

static char	*ft_expenv(char *str, int *i, char *word, int index, char **env)
{
	char	*tmp;
	char	*new_str;

	if (!word)
		return (NULL);
	new_str = ft_strndup(word, ft_strlen(word));
	if (!new_str)
		return (free(word), NULL);
	if (str[*i] == '_' && str[*i + 1] != '_' && !is_alphanum(str[*i + 1]))
		(1) && (new_str = ft_strjoin(new_str, ft_getenv("_", env)), (*i)++);
	else
	{
		tmp = ft_strndup(&str[index + 1], *i - index - 1);
		if (ft_getenv(tmp, env))
			new_str = ft_strjoin(new_str, ft_getenv(tmp, env));
		else
			new_str = ft_strjoin(new_str, "");
		free(tmp);
	}
	return (free(word), new_str);
}

static char	*add_rest_word(char *str, char *str2, int *i, int index)
{
	char	*new_str;
	char	*tmp;

	if (!str2)
		return (NULL);
	while (str[++(*i)])
		;
	tmp = ft_strndup(&str[index], *i);
	if (!tmp)
		return (free(str2), NULL);
	new_str = ft_strndup(str2, ft_strlen(str2));
	new_str = ft_strjoin(new_str, tmp);
	return (free(tmp), free(str2), new_str);
}

static char	*ft_strenv(char *str, int index, int exit_status, char **env)
{
	int		i;
	char	*tmp;
	char	*new_str;

	tmp = ft_strndup(str, index);
	if (!tmp)
		return (NULL);
	(1) && (new_str = ft_strndup("", 1), new_str = ft_strjoin(new_str, tmp));
	i = index + 1;
	while (str[i] && (is_alphanum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '?')
	{
		free(tmp);
		(1) && (tmp = ft_itoa(exit_status),
			new_str = ft_strjoin(new_str, tmp), i++);
	}
	else
		new_str = ft_expenv(str, &i, new_str, index, env);
	index = i;
	if (str[i])
		new_str = add_rest_word(str, new_str, &i, index);
	return (free(tmp), new_str);
}

int	ft_expand(char **token, int flag, int exit_status, char **env)
{
	int		i;
	char	*tmp;

	if (!token)
		return (0);
	i = -1;
	while (token[++i])
	{
		if (!((i > 0 && !ft_strcmp(token[i - 1], "<<") && flag)
			|| get_index_dollar(token[i], flag) < 0))
		{
			tmp = ft_strenv(token[i], get_index_dollar(token[i], flag), exit_status, env);
			if (!token[i])
				return (perror("Error"), 0);
			free(token[i]);
			token[i] = tmp;
			i--;
		}
	}
	return (1);
}
