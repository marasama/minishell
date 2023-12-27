/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:14:13 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/27 00:02:00 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	malloc_error(int control, t_shell **shell)
{
	if (control != 0)
	{
		if (control > 1)
			free(*shell);
		if (control > 2)
		{
			free((*shell)->env);
			free_env(*shell);
		}
		printf("Memory allocation error");
		exit(control);
	}
}

void	edit_env_(t_list *node, char *key, char *value, t_shell *m_shell)
{
	t_env	*new_env;

	if (node == NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ;
		new_env->key = key;
		new_env->value = value;
		ft_lstadd_back(&(m_shell->env), ft_lstnew(new_env));
	}
}

char	*get_home(t_shell *m_shell)
{
	t_list	*tmp;
	t_env	*env;

	tmp = m_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}
