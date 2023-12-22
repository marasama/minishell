/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:14:01 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/22 15:53:57 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	parse_text_typer(t_parse *parse, char *str, int *j, int *flag)
{
	parse->text[*j] = ft_strdup(str);
	*j += 1;
	parse->text[*j] = NULL;
	*flag = 1;
}

void	option_check(t_parse *parse, int flag)
{
	if (flag == 0)
	{
		free_parse_text(parse->text);
		parse->text = NULL;
	}
}

void	parse_type_typer(t_parse **parse, const char *str)
{
	if (str[0] == '|')
		(*parse)->type = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		(*parse)->type = GREATER;
	else if (str[0] == '<' && str[1] == '<')
	{
		(*parse)->type = HEREDOC;
		g_check_heredoc = 1;
	}
	else if (str[0] == '>')
		(*parse)->type = GREAT;
	else if (str[0] == '<')
		(*parse)->type = LESS;
}

t_parse	*initialize_parse(size_t len)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	(parse)->next = NULL;
	(parse)->cmd = NULL;
	(parse)->text = ft_calloc(sizeof(char *), len + 1);
	if (!(parse)->text)
		return (NULL);
	(parse)->type = 0;
	(parse)->infile = STDINN;
	(parse)->outfile = STDOUT;
	(parse)->fd = 1;
	(parse)->pid = 0;
	(parse)->control = 0;
	return (parse);
}
