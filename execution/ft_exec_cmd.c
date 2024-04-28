/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:08:44 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/28 02:22:26 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path_env(char **env)
{
	int		i;
	int		j;
	char	*path;

	i = -1;
	path = getenv("PATH");
	if (!path || !env)
		return ("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	return (path);
}

static char	**get_all_paths(char **env)
{
	char	*path;
	char	**paths;

	path = get_path_env(env);
	paths = ft_split(path, ':');
	return (paths);
}

static char	*get_path_cmd(char *first_cmd, char **env)
{
	int		i;
	char	*tmp;
	char	**all_paths;

	all_paths = get_all_paths(env);
	if (!all_paths || !first_cmd)
		return (NULL);
	i = -1;
	while (all_paths[++i])
	{
		tmp = ft_strndup("", 1);
		tmp = ft_strjoin(tmp, all_paths[i]);
		tmp = ft_strjoin(tmp, "/");
		tmp = ft_strjoin(tmp, first_cmd);
		if (!access(tmp, F_OK | X_OK))
			return (free_mat(&all_paths), tmp);
		if (!tmp)
			return (free_mat(&all_paths), NULL);
		free(tmp);
	}
	return (free_mat(&all_paths), ft_strndup(first_cmd, ft_strlen(first_cmd)));
}

static void	print_error(char *str)
{
	if (str)
	{
		write(2, "minishell :", 11);
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
}

int	ft_exec_cmd(char *cmd, char ***env)
{
	char	*path_cmd;
	char	**all_cmd;
	int		i;

	all_cmd = ft_split_cmd(cmd);
	if (!all_cmd)
		return (perror("error"), errno);
	i = -1;
	ft_remove_quotes(all_cmd);
	path_cmd = get_path_cmd(all_cmd[0], *env);
	if (execve(path_cmd, all_cmd, *env) < 0)
	{
		if (path_cmd)
			free(path_cmd);
		print_error(all_cmd[0]);
		return (free_mat(&all_cmd), 127);
	}
	return (free_mat(&all_cmd), free(path_cmd), 0);
}