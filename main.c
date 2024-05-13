/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/11 23:17:45 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	affiche(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf ("cmd : %s \n", tmp->cmd);
		printf ("rederiction : %s \n", tmp->redirections);
		tmp = tmp->next;
		printf("------------------------\n");
	}
}

static void	handle_fun(int sig)
{
		g_cld_proc = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
}

static void	ft_signals()
{
	signal(SIGINT, handle_fun);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		exit_status;
	char	**copy_env;
	t_node	*head;

	(void)ac;
	(void)av;
	(1) && (exit_status = 0, copy_env = get_matr_copy(env), rl_catch_signals = 0);
	ft_signals();
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (*input)
			add_history(input);
		head = ft_create_list(input, &exit_status);
		if (!head)
			free(input);
		else
		{
			exit_status = ft_execv_cmd(head, &copy_env, exit_status);
			ft_lstclear(&head);
			free(input);
		}
	}
	clear_history();
}
