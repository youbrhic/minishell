/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:07:59 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/19 23:24:28 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_int(int sig)
{
	int		pid;

	pid = wait(NULL);
	if (pid <= 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_cld_proc = 1;
	}
	else
	{
		write(1, "\n", 1);
		g_cld_proc = sig + 128;
	}
}

static void handle_quite(int sig)
{
	int		pid;

	pid = wait(NULL);
	if (pid > 0)
	{
		write(1, "Quit: 3", 8);
		write(1, "\n", 1);
		g_cld_proc = sig + 128;
	}
}

void	ft_signals()
{
	signal(SIGINT, handle_int);
	signal(SIGQUIT, handle_quite);
}

static void handle_heredoc(int sig)
{
    int     pid;

	(void)sig;
	pid = wait(NULL);
	if (pid <= 0)
	{
		write(1, "\n", 1);
		exit(1);
	}
	else
		g_cld_proc = 1;
}

void    ft_signal_heredoc()
{
    signal(SIGINT, handle_heredoc);
}
