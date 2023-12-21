/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:13:30 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/21 09:37:13 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*get_next_cmd(t_parse **parse)
{
	t_parse *tmp;

	tmp = *parse;
	while (tmp->infile > STDERR || tmp->outfile > STDERR
		|| tmp->type == HEREDOC)
	{
		tmp = tmp->next;
	}
	return (tmp->next);
}

int	single_or_multi_command(t_shell *m_shell)
{
	t_parse	*parse;
	int		i;

	i = 0;
	parse = m_shell->parse;
	while (parse)
	{
		if (parse->type == 2)
			i++;
		parse = parse->next;
	}
	return (i);
}
