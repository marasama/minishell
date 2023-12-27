/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:10:41 by edamar            #+#    #+#             */
/*   Updated: 2023/12/27 21:19:04 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	expand_utils2(t_shell **shell, char *back, t_list *lex,
			char *before)
{
	if (!lex->content)
	{
		free(back);
		free(before);
		malloc_error(4, shell);
	}
}

void	expand_utils3(t_shell **shell, char *before, char *new_value,
			t_list *lex)
{
	if (!new_value)
	{
		free(before);
		malloc_error(4, shell);
	}
	free(lex->content);
	lex->content = ft_strjoin(before, new_value);
	free(new_value);
}

void	expand_utils4(t_shell **shell, char *before, char *new_value,
			t_list *lex)
{
	if (!lex->content)
	{
		free(before);
		free(new_value);
		malloc_error(4, shell);
	}
}
