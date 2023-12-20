/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:22:22 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/20 23:30:19 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int		check_heredoc;

void	initialize_shell(t_shell **shell)
{
	*shell = malloc(sizeof(t_shell));
	(*shell)->env = malloc(sizeof(t_env));
	(*shell)->lex_list = NULL;
	(*shell)->exec_status = 0;
	(*shell)->heredoc = NULL;
	(*shell)->cmd = NULL;
	check_heredoc = 0;
}

void	get_readline(t_shell *shell)
{
	get_title_from_env(&shell);
	shell->cmd = readline(shell->title);
	if (shell->cmd && !is_space(shell->cmd))
	{
		free(shell->cmd);
		free(shell->title);
		get_readline(shell);
	}
	if (!shell->cmd)
	{
		free_loop(0, shell);
		free_(shell);
		if (shell->lex_list)
			free(shell->lex_list);
		free(shell);
		exit(1);
	}
	add_history(shell->cmd);
}

void	go_parser(t_shell *shell, char **env, int control)
{
	int flags[3];

	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	control = check(shell);
	if (!control)
	{
		free_lexes(&(shell->lex_list));
		return ;
	}
	if (ft_strcmp(shell->cmd, ""))
	{
		if (parser(shell, flags))
			exec(env, shell);
	}
	free_loop(control, shell);
}

void	free_lexes(t_list **node)
{
	if (!*node)
		return ;
	if ((*node)->next != NULL)
		free_lexes(&(*node)->next);
	if ((*node)->content)
		(*node)->content = (free((*node)->content), NULL);
	if ((*node))
		(*node) = (free(*node), NULL);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	int		control;

	(void)av;
	control = 0;
	if (ac != 1)
		exit(write(2, "This program cannot accept any arguments\n", 41));
	initialize_shell(&shell);
	env_get(env, &shell);
	signals_control();
	while (1)
	{
		get_readline(shell);
		if (quote_check(shell->cmd))
		{
			lexer(shell->cmd, &shell->lex_list);
			expander(shell);
			go_parser(shell, env, control);
		}
		else
		{
			(free(shell->cmd), free(shell->title));
			continue ;
		}
	}
}
