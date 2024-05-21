/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:08:44 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/21 06:18:10 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_all_paths(char **env)
{
	char	*path;
	char	**paths;

	path = ft_getenv("PATH", env);
	if (!path)
		return (NULL);
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
			return (free_mat(all_paths), tmp);
		if (!tmp)
			return (free_mat(all_paths), NULL);
		free(tmp);
	}
	return (free_mat(all_paths), ft_strndup(first_cmd, ft_strlen(first_cmd)));
}

static int	print_error(char *str, char *path_cmd, int err)
{
	int		i;

	write(2, "minishell :", 11);
	write(2, str, ft_strlen(str));
	i = -1;
	while (str[++i] && str[i] != '/')
		;
	if (err == 13)
	{
		if (access(path_cmd, X_OK))
			return (write(2, ": command not found \n", 21), 127);
		return (write(2, ": Permission denied\n", 20), 126);
	}
	else
	{
		if (i == ft_strlen(str))
			return (write(2, ": command not found \n", 21), 127);
		return (perror(""), 127);
	}
}

int	ft_exec_cmd(char *cmd, char ***env, int exit_status)
{
	char	*path_cmd;
	char	**all_cmd;
	int		state;

	all_cmd = ft_token_cmds(cmd, *env, exit_status, 1);
	if (!all_cmd)
		return (perror("error"), 1);
	if (!*all_cmd)
		return (free_mat(all_cmd), 0);
	path_cmd = get_path_cmd(all_cmd[0], *env);
	if (!path_cmd)
		return (state = print_error(all_cmd[0], path_cmd, errno),
			free_mat(all_cmd), state);
	if (check_bultin(all_cmd[0]))
		return (state = ft_exec_bultin(all_cmd, env, 0),
			free_mat(all_cmd), free(path_cmd), state);
	if (execve(path_cmd, all_cmd, *env) < 0)
		return (state = print_error(all_cmd[0], path_cmd, errno),
			free_mat(all_cmd), free(path_cmd), state);
	return (free_mat(all_cmd), free(path_cmd), 0);
}
