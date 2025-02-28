/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:17:17 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:50:14 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Returns path to a executable binary file if found, else NULL is returned.
*/

char	*find_path(char *command)
{
	char	**paths;
	char	*path;
	size_t	i;

	path = ft_strnew(PATH_MAX);
	if (!path)
		exit(1);
	i = 0;
	paths = ft_strsplit(hash_get(g_shell->vars, "PATH"), ':');
	ft_strcat(path, command);
	while (access(path, X_OK) == -1 && paths[i])
	{
		ft_bzero(path, PATH_MAX);
		ft_strcat(path, paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, command);
		i += 1;
	}
	ft_arrfree(paths);
	if (access(path, X_OK) == -1)
		ft_strdel(&path);
	return (path);
}
