/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:08:44 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/24 09:39:23 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path_env(char **env)
{
	int		i;
	// int		j;
	char	*path;

	i = -1;
	path = getenv("PATH");
	if (!path)
		return ("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	return (path);
}

static char	**get_all_paths(char **env)
{
	char	**paths;
	char	*path;
	int		i;

	path = get_path_env(env);
	if (!path)
		return (NULL);
	i = -1;
	while (++i < 5 && *path)
		path++;
	paths = ft_split(path, ':');
	return (paths);
}

static char	*get_path_cmd(char *first_cmd, char **env)
{
	int		i;
	char	**all_paths;
	char	*tmp;

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
		free(tmp);
	}
	return (free_mat(&all_paths), ft_strndup(first_cmd, ft_strlen(first_cmd)));
}

static void print_error(char *str)
{
	if (str)
	{
		write(2, "minishell :", 11);
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
}

int	exec_cmd(char *cmd, char **env)
{
	char	*path_cmd;
	char	**all_cmd;
	int		i;

	all_cmd = ft_split_cmd(cmd);
	remove_quotes(all_cmd);
	if (!all_cmd)
		return (perror("error"), errno);
	// for (i = 0; all_cmd[i]; i++)
	// {
	// 	printf("cmd[%d] = %s\n", i, all_cmd[i]);
	// }
	if (check_bultin(all_cmd[0]))
	{
		exec_bultin(all_cmd, env);
		return (free_mat(&all_cmd), 0);
	}
	i = -1;
	path_cmd = get_path_cmd(all_cmd[0], env);
	if (execve(path_cmd, all_cmd, env) < 0)
	{
		if (path_cmd)
			free(path_cmd);
		print_error(all_cmd[0]);
		return (free_mat(&all_cmd), 127);
	}
	return (free_mat(&all_cmd), free(path_cmd), 0);
}
