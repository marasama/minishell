/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:13:22 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/20 23:29:17 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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
	int				exit_value;

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
	(free_loop(1, *m_shell), free_(*m_shell));
	(free((*m_shell)->lex_list), free(*m_shell));
	exit(exit_value);
}

void	get_title_from_env(t_shell **shell)
{
	char	*user;
	char	*pwd;
	char	*title;
	char	*temp;

	user = get_env((*shell)->env, "USER");
	pwd = get_env((*shell)->env, "PWD");
	title = ft_strdup(user);
	free(user);
	temp = ft_strjoin(title, "@");
	free(title);
	title = temp;
	temp = ft_strjoin(title, pwd);
	free(title);
	title = temp;
	temp = ft_strjoin(title, "$ ");
	free(title);
	(*shell)->title = temp;
	free(pwd);
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
	t_env	*a;
	char	**str;

	free((*shell)->env);
	(*shell)->env = NULL;
	while (*env)
	{
		a = malloc(sizeof(t_env));
		str = ft_split(*env, '=');
		if (str && str[0] && str[1])
		{
			a->key = ft_strdup(str[0]);
			a->value = ft_strdup(str[1]);
			ft_lstadd_back(&(*shell)->env, ft_lstnew(a));
		}
		free_str(str);
		env++;
	}
}
