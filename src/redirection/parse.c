/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:17:19 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 18:59:15 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	switch_agre_node(char *old, char *new, char *sign)
{
	if (sign[0] == '<')
	{
		if (old[0] == '-')
			close(!new ? 0 : ft_atoi(new));
		else
		{
			dup2(ft_atoi(old), !new ? 1 : ft_atoi(new));
			close(ft_atoi(old));
		}
	}
	else
	{
		if (old[0] == '-')
			close(!new ? 1 : ft_atoi(new));
		else
		{
			if (fcntl(ft_atoi(old), F_GETFL) == -1)
				exit_error(BAD_FD_ERR, ft_strcat("42sh bad fd, ", old));
			else
			{
				dup2(ft_atoi(old), !new ? 1 : ft_atoi(new));
				close(ft_atoi(old));
			}
		}
	}
}

void	parse_redir_aggre_list(t_re_ag *l, t_job *j, int *outfile)
{
	int		out;

	out = *outfile;
	while (l)
	{
		l->e_flag == REDIR ? switch_redir_node(l, j, outfile)
			: switch_agre_node(l->node.t_ag.word,
			l->node.t_ag.n, l->node.t_ag.sign);
		l = l->next;
	}
	if (out != *outfile)
		dup42(STDIN_FILENO, *outfile, STDERR_FILENO);
}
