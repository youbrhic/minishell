/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/30 18:08:45 by aait-bab         ###   ########.fr       */
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
	t_node	*head;
	char	**new_env;

	(void)ac;
	(void)av;
	exit_status = 0;
	new_env = get_matr_copy(env);
	while (1)
	{
		input = readline("minibash$ ");
		if (!input)
			exit(1);
		else
			add_history(input);
		head = ft_create_list(input, &exit_status);
		if (!head)
			continue;
		else
		{
			// affiche(head);
			exit_status = ft_execv_cmd(head, &new_env);
			ft_lstclear(&head);
		}
		free(input);
	}
	clear_history();
}
