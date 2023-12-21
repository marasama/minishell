/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adurusoy <adurusoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:14:39 by adurusoy          #+#    #+#             */
/*   Updated: 2023/12/21 14:01:51 by adurusoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void	signals(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sigtir(int sig)
{
	(void)sig;
	
}

void	signals_control(void)
{
	signal(SIGINT, signals);
	signal(SIGQUIT, sigtir);
}
