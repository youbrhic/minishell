/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:08:44 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/30 13:09:58 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_path_env(char **env)
{
    int     i;
    int     j;
    char    *path;

    i = -1;
    path = ft_strndup("PATH", 4);
	if (!path)
		return (NULL);
    while(env[++i])
    {
        j = -1;
        while (env[i][++j] && j < 5)
        {
			if (env[i][j] != path[j])
				break;
        }
		if (j == 4)
			return (free(path), env[i]);
    }
	return (free(path), NULL);
}

static char **get_all_paths(char **env)
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

static char *get_path_cmd(char *first_cmd, char **env)
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
	return (free(first_cmd), free_mat(&all_paths), NULL);
}

int	exec_cmd(char *cmd, char **env)
{
	char	*path_cmd;
	char	**all_cmd;
	int		i;

	all_cmd = ft_split_cmd(cmd);
	i = -1;
	path_cmd = get_path_cmd(all_cmd[0], env);
	if (!path_cmd || !all_cmd)
		return (-1);
	if (execve(path_cmd, all_cmd, env) < 0)
		return (free_mat(&all_cmd), free(path_cmd), -1);
	return (free_mat(&all_cmd), free(path_cmd), 1);
	return (1);
}
