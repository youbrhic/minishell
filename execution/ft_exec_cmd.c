/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:08:44 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/24 14:57:52 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_all_paths(char **env, char *first_cmd)
{
	char	*path;
	char	**paths;

	path = ft_getenv("PATH", env);
	if (!path)
	{
		paths = malloc(sizeof(char *) * 2);
		if (!paths)
			return (NULL);
		paths[0] = ft_strdup(first_cmd);
		if (!paths[0])
			return (free_mat(paths), NULL);
		paths[1] = NULL;
	}
	else
		paths = ft_split(path, ':');
	return (paths);
}

static int	check_cmd(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

static char	*get_path_cmd(char *first_cmd, char **env)
{
	int		i;
	char	*tmp;
	char	**all_paths;

	all_paths = get_all_paths(env, first_cmd);
	if (!first_cmd)
		return (NULL);
	if (check_cmd(first_cmd))
		return (ft_strdup(first_cmd));
	i = -1;
	while (all_paths[++i])
	{
		(1) && (tmp = ft_strndup("", 1), tmp = ft_strjoin(tmp, all_paths[i]));
		(1) && (tmp = ft_strjoin(tmp, "/"), tmp = ft_strjoin(tmp, first_cmd));
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
		if ((access(str, X_OK) && !access(str, R_OK)) || !*str || !*path_cmd)
			return (write(2, ": command not found \n", 21), 127);
		if (!access (str, S_IFDIR))
			return (write(2, ": is a directory \n", 21), 126);
		return (ft_perror(" "), 126);
	}
	else
	{
		if (i == ft_strlen(str))
			return (write(2, ": command not found \n", 21), 127);
		return (ft_perror(" "), 127);
	}
}

int	ft_exec_cmd(char *cmd, char ***env, int exit_status)
{
	char	*path_cmd;
	char	**all_cmd;
	int		state;

	all_cmd = ft_token_cmds(cmd, *env, exit_status, 1);
	if (!all_cmd)
		return (ft_perror("error"), 1);
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
