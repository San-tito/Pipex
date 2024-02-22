/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:15:47 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/22 20:08:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	absolute_program(const char *string)
{
	return (ft_strchr(string, '/') != NULL);
}

static char	*ft_getenv(const char *name, char **env)
{
	size_t	len;
	int		i;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (*(env + i))
	{
		if (!ft_strncmp(*(env + i), name, len) && *(*(env + i) + len) == '=')
			return (*(env + i) + len + 1);
		i++;
	}
	return (NULL);
}

char	*search_for_command(const char *pathname, char **env)
{
	char	*command;
	char	*path_list;

	path_list = ft_getenv("PATH", env);
	if (absolute_program(pathname))
		command = ft_strdup(pathname);
	if (!path_list || !*path_list)
		command = ft_strdup(pathname);
	return (command);
}
