/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/24 14:31:46 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *str)
{
	char	*error;

	error = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, " ", 1);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

static int	init_shell(char **env, char ***copy_env,
	struct termios *ter, int *exit_status)
{
	char	*shelvl;
	char	*nb;

	*copy_env = get_env(env);
	if (!copy_env || !*copy_env)
		return (ft_perror("memmory problem"), 0);
	if (ft_getenv("SHLVL", *copy_env))
	{
		shelvl = ft_strdup(ft_getenv("SHLVL", *copy_env));
		if (!shelvl)
			return (ft_perror("memmory problem"), free_mat(*copy_env), 0);
		nb = ft_itoa(ft_atoi(shelvl) + 1);
		if (!nb)
			return (free(shelvl), free_mat(*copy_env),
				ft_perror("memmory problem"), 0);
		ft_setenv("SHLVL", nb, copy_env);
		free(nb);
		free(shelvl);
	}
	if (tcgetattr(STDIN_FILENO, ter))
		return (ft_perror("ter"), free_mat(*copy_env), 0);
	*exit_status = 0;
	rl_catch_signals = 0;
	return (1);
}

static void	clean_shell(char **copy_env,
	char *input, int exit_status)
{
	unlinek_heredocs();
	if (copy_env)
		free_mat(copy_env);
	if (input)
		free(input);
	else
		write(2, "exit\n", 5);
	rl_clear_history();
	exit(exit_status);
}

int	main(int ac, char **av, char **env)
{
	char			*input;
	int				exit_status;
	char			**copy_env;
	t_node			*head;
	struct termios	ter;

	(void)ac;
	(void)av;
	if (!init_shell(env, &copy_env, &ter, &exit_status))
		exit(1);
	ft_signals();
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input || !isatty(STDIN_FILENO))
			clean_shell(copy_env, input, exit_status);
		if (*input)
			add_history(input);
		head = ft_create_list(input, copy_env, &exit_status);
		if (head)
			(1) && (exit_status = ft_execv_cmd(head, &copy_env, exit_status),
				ft_lstclear(&head));
		if (tcsetattr(STDIN_FILENO, TCSANOW, &ter) != 0)
			clean_shell(copy_env, input, exit_status);
	}
}
