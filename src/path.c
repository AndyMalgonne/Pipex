/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:37:21 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/25 13:11:01 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strcut(char *str, char stop)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != stop)
		i++;
	return (ft_substr(str, 0, i));
}

char	**find_path(char **envp)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/')
		{
			tmp = ft_strjoin(path[i], "/");
			if (!tmp)
				return (ft_fsplit(path), NULL);
			free(path[i]);
			path[i] = tmp;
		}
	}
	return (path);
}

char	*find_file(char *cmd, t_info *info)
{
	int		i;
	char	*file_path;

	i = 0;
	cmd = ft_strcut(cmd, ' ');
	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	if (ft_strncmp(cmd, "", 1) == 0)
		return (ft_dprintf(2, "%s: command not found\n", cmd), free(cmd), NULL);
	while (info->path != NULL && info->path[++i])
	{
		file_path = ft_strjoin(info->path[i], cmd);
		if (!file_path)
			return (free(cmd), NULL);
		if (access(file_path, F_OK | X_OK) == 0)
			return (free(cmd), file_path);
		free(file_path);
	}
	ft_dprintf(2, "%s: command not found\n", cmd);
	return (free(cmd), NULL);
}
