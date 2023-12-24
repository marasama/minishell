/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:13:22 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/24 23:44:14 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	is_numeric(char *s)
{
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s == 43 || *s == 45)
		s++;
	while (48 <= *s && *s <= 57)
		s++;
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s != '\0')
		return (0);
	return (1);
}

void	builtin_exit(t_shell **m_shell)
{
	int	status;
	int	exit_value;

	exit_value = 0;
	printf("exit\n");
	if (!(*m_shell)->parse->text)
		exit(EXIT_SUCCESS);
	status = is_numeric((*m_shell)->parse->text[0]);
	if (status == 0)
	{
		printf("bash: exit: %s: numeric argument required\n",
			(*m_shell)->parse->text[0]);
		exit_value = 255;
	}
	else if (status == 1 && !(*m_shell)->parse->text[1])
		exit_value = ft_atoi((*m_shell)->parse->text[0]);
	else
	{
		printf("bash: exit: too many arguments\n");
		(*m_shell)->exec_status = 1;
		return ;
	}
	(free_loop(1, *m_shell), free_env(*m_shell));
	(free((*m_shell)->lex_list), free(*m_shell));
	exit(exit_value);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	env_get(char **env, t_shell **shell)
{
	t_env	*new_node;
	char	**str;

	free((*shell)->env);
	(*shell)->env = NULL;
	while (*env)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			malloc_error();
		str = ft_split(*env, '=');
		if (str && str[0] && str[1])
		{
			new_node->key = ft_strdup(str[0]);
			new_node->value = ft_strdup(str[1]);
			ft_lstadd_back(&(*shell)->env, ft_lstnew(new_node));
		}
		free_str(str);
		env++;
	}
}
