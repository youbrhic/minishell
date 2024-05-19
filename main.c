/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/19 05:38:40 by youbrhic         ###   ########.fr       */
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

static int init_shell(char **env, char ***copy_env, t_term ter , int exit_status)
{
	char	*shelvl;
	char	*nb;

	*copy_env = get_env(env);
	if (!copy_env || !*copy_env)
		return (perror("memmory problem"), 0);
	if (ft_getenv("SHLVL", *copy_env))
	{
		shelvl = ft_strdup(ft_getenv("SHLVL", *copy_env));
		if (!shelvl)
			return (perror("memmory problem"), free_mat(*copy_env), 0);
		nb = ft_itoa(ft_atoi(shelvl) + 1);
		if (!nb)
			return (free(shelvl), free_mat(*copy_env), perror("memmory problem"), 0);
		ft_setenv("SHLVL", nb, copy_env, 0);
		free(nb);
		free(shelvl);
	}
	if (tcgetattr(STDIN_FILENO, &ter))
		return (perror("ter"), 0);
	exit_status = 0; 
	rl_catch_signals = 0;
	return (1);
}

static void clean_shell(t_node *head, char **copy_env, char *input, int exit_status)
{
	unlinek_heredocs();
	if (copy_env)
		free_mat(copy_env);
	if (!input)
		write(1, "exit\n", 5);
	rl_clear_history();
	exit(exit_status);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		exit_status;
	char	**copy_env;
	t_node	*head;

	(void)ac;
	(void)av;
	if (!init_shell(env, &copy_env, ter, exit_status))
		exit(1);
	ft_signals();
	while (1)
	{
		(1) && (input = readline("Minishell$ "));
		if (!input)
			clean_shell(head, copy_env, input, 0);
		if (*input)
			add_history(input);
		head = ft_create_list(input, copy_env, &exit_status);
		if (head)
			(1) && (exit_status = ft_execv_cmd(head, &copy_env, exit_status),
				ft_lstclear(&head));
	}
}
