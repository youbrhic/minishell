/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hardoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 02:15:06 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/19 10:45:57 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_heredoc(char *limiter, char *file, char **env, int exit_status)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("pid");
		return ;
	}
	else if (pid == 0)
		write_hardoc(file, limiter, env, exit_status);
	wait(NULL);
	ft_signal_heredoc();
}

int	unlinek_heredocs(void)
{
	char	*tmp;
	int		i;
	char	*nb;

	(1) && (i = 0, tmp = ft_strdup("/tmp/hardoc"));
	if (!tmp)
		return (0);
	while (++i && !access(tmp, F_OK))
	{
		unlink(tmp);
		free (tmp);
		tmp = ft_strdup("/tmp/hardoc");
		if (!tmp)
			return (0);
		nb = ft_itoa(i);
		if (!nb)
			return (0);
		tmp = ft_strjoin(tmp, nb);
		if (!tmp)
			return (free(nb), 0);
		free(nb);
	}
	return (free(tmp), 1);
}

int	ft_hardoc(char **limiter, char **env, int exit_status)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = get_file_hardoc();
	if (!file)
		return (1);
	create_heredoc(*limiter, file, env, exit_status);
	tmp = ft_strdup(file);
	if (!tmp)
		return (1);
	free(*limiter);
	free(file);
	*limiter = tmp;
	return (0);
}
