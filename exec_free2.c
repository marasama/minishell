/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:13:27 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/21 08:40:40 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_parse_text(char **text)
{
	int	i;

	i = 0;
	if (text)
	{
		if (text[i])
		{
			while (text[i])
				free(text[i++]);
		}
		free(text);
	}
}

void	free_parser(t_shell *m_shell)
{
	t_parse	*parse;
	t_parse	*tmp;

	parse = m_shell->parse;
	if (parse)
	{
		while (parse)
		{
			tmp = parse;
			parse = parse->next;
			if (tmp->cmd)
				free(tmp->cmd);
			if (tmp->text)
				free_parse_text(tmp->text);
			free(tmp);
		}
	}
	else if (m_shell->parse)
		free(m_shell->parse);
}

int	*create_pipe(void)
{
	int	index;
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	if (!fd)
		return (NULL);
	index = -1;
	while (++index < 6)
		fd[index] = 0;
	return (fd);
}
