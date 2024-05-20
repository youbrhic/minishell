/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hardoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 02:15:06 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 03:41:22 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_heredoc(char *limiter, char *file, char **env, int exit_status)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("pid");
		return (1);
	}
	else if (pid == 0)
		write_hardoc(file, limiter, env, exit_status);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
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
	char	*file;
	char	*tmp;
	int		state;

	rl_catch_signals = 1;
	ft_signal_heredoc();
	file = get_file_hardoc();
	if (!file)
		return (1);
	state = create_heredoc(*limiter, file, env, exit_status);
	tmp = ft_strdup(file);
	if (!tmp)
		return (1);
	free(*limiter);
	free(file);
	*limiter = tmp;
	ft_signals();
	rl_catch_signals = 0;
	if (g_cld_proc == 1)
		return (1);
	return (0);
}
