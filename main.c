/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/02 17:00:27 by aait-bab         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		exit_status;
	char	**copy_env;
	t_node	*head;

	(void)ac;
	(void)av;
	(1) && (exit_status = 0, copy_env = get_matr_copy(env));
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
			exit(1);
		if (*input)
			add_history(input);
		head = ft_create_list(input, &exit_status);
		if (!head)
			free(input);
		else
		{
			//affiche(head);
			exit_status = ft_execv_cmd(head, &copy_env, exit_status);
			ft_lstclear(&head);
			free(input);
		}
	}
	clear_history();
}
