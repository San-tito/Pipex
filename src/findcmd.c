/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:15:47 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/12 17:43:20 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	absolute_program(const char *string)
{
	return (ft_strchr(string, '/') != NULL);
}

static char	*ft_getenv(char *name, char **env)
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

static char	*find_in_path_element(char *name, char *path)
{
	char	*full_path;
	size_t	path_len;
	size_t	name_len;

	path_len = ft_strlen(path);
	name_len = ft_strlen(name);
	full_path = ft_calloc(path_len + name_len + 2, sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path, path_len + 1);
	if (*(full_path + path_len - 1) != '/')
		ft_strlcat(full_path, "/", path_len + 2);
	ft_strlcat(full_path, name, path_len + name_len + 2);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*search_for_command(char *pathname, char **env)
{
	char	*command;
	char	*path_list;
	char	**paths;
	int		path_index;

	path_index = 0;
	path_list = ft_getenv("PATH", env);
	if (absolute_program(pathname))
		return (command = pathname);
	else if (!path_list || !*path_list)
		return (command = pathname);
	paths = ft_split(path_list, ':');
	if (!paths)
		return (NULL);
	while (*(paths + path_index))
	{
		command = find_in_path_element(pathname, *(paths + path_index));
		free(*(paths + path_index));
		if (command)
			break ;
		path_index++;
	}
	free(paths);
	return (command);
}
