/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:13:07 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/27 23:11:36 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	create_files_utils(t_shell **shell, char *home, t_parse *m_next,
			char **pwd)
{
	*pwd = ft_strdup(m_next->text[0]);
	if (!*pwd)
	{
		if (home)
			free(home);
		malloc_error(5, shell);
	}
}

void	create_files_utils2(t_shell **shell, char **home)
{
	*home = get_env((*shell)->env, "HOME");
	if (!(*home))
		malloc_error(5, shell);
}

void	create_files_utils3(t_parse *nparse, char **pwd)
{
	if (*pwd)
		free(*pwd);
	printf("minishell: %s: No such file or directory\n", nparse->text[0]);
}

int	create_in_files_me(t_parse *parse, t_shell *shell)
{
	t_parse	*nparse;
	char	*pwd;
	char	*home;

	home = NULL;
	pwd = NULL;
	create_files_utils2(&shell, &home);
	nparse = parse->next;
	if (!ft_strnstr(nparse->text[0], home, ft_strlen(home)))
		handle_relative_path(&pwd, parse);
	else
		create_files_utils(&shell, home, nparse, &pwd);
	if (!access(pwd, F_OK))
		nparse->fd = open(pwd, O_RDONLY, 0777);
	else
	{
		create_files_utils3(nparse, &pwd);
		return (0);
	}
	if (pwd)
		free(pwd);
	free(home);
	parse->infile = nparse->fd;
	return (1);
}
