/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:14 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/15 15:14:30 by youbrhic         ###   ########.fr       */
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
			while (str[i] && str[++i] != '\'')
				;
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
					|| str[i + 1] == '?' || str[i + 1] == '_' 
					|| (i + 3 < ft_strlen(str) && str[i + 1] == '\\' && is_quot(str[i + 2]) && str[i + 3]))))
			return (i);
	}
	return (-1);
}

static char *get_str_env(char *str, int index_d, char **env, int exit_status)
{
	char 	*str_env;
	char	*tmp;
	int		i;

	i = index_d + 1;
	while (str[i] && (is_alphanum(str[i]) || str[i] == '_'))
		i++;
	if (i + 2 < ft_strlen(str) && str[i] == '\\' && is_quot(str[i + 1]) && str[i + 2])
		i += 2;
	else if (str[i] == '?' && i == index_d + 1)
		return (ft_itoa(exit_status));
	tmp = ft_strndup(&str[index_d + 1], i);
	if (!tmp)
		return (NULL);
	str_env = ft_getenv(tmp, env);
	if (!str_env)
		str_env = "";
	return (free(tmp), ft_strdup(str_env));
}

static char *get_rest_str(char *str, int index_d)
{
	char *rest_str;
	int		i;

	i = index_d + 1;
	while (str[i] && (is_alphanum(str[i]) || str[i] == '_'))
		i++;
	if ((i + 3 < ft_strlen(str) && str[i] == '$' &&  str[i + 1] == '\\'
			&& is_quot(str[i + 2]) && str[i + 3]) || (str[i] == '?' && i == index_d + 1))
		i++;
	rest_str = ft_strdup(&str[index_d + i]);
	return (rest_str);
}

static char *ft_str_expand(char *str, int index_d, char **env, int exit_status)
{
	char	*tmp;
	char	*new_str;

	new_str = ft_strndup(str, index_d);
	if (!new_str)
		return (NULL);
	tmp = get_str_env(str, index_d, env, exit_status);
	if (!tmp)
		return (free(new_str), NULL);
	new_str = ft_strjoin(new_str, tmp);
	if (!new_str)
		return (free(tmp), NULL);
	tmp = get_rest_str(str, index_d);
	if (!tmp)
		return (free(new_str), NULL);
	new_str = ft_strjoin(new_str, tmp);
	return(new_str);
}

int	ft_expand(char **token, int flag, int exit_status, char **env)
{
	int		i;
	char	*tmp;

	i  = -1;
	while (token[++i])
	{
		if (get_index_dollar(token[i], flag) >= 0 
			&& !(i > 0 && !ft_strcmp(token[i - 1], "<<")))
		{
			tmp = ft_str_expand(token[i],
				get_index_dollar(token[i], flag), env, exit_status);
			if (!tmp)
				return (0);
			free(token[i]);
			token[i] = tmp;
		}
	}
	return (1);
}
