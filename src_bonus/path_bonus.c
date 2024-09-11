/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:49:54 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/09/11 14:10:26 by amalgonn         ###   ########.fr       */
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

char	**find_path(char **envp, t_info *info)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	info->path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
	if (!info->path)
		return (NULL);
	i = -1;
	while (info->path[++i])
	{
		if (info->path[i][ft_strlen(info->path[i]) - 1] != '/')
		{
			tmp = ft_strjoin(info->path[i], "/");
			if (!tmp)
				return (ft_fsplit(info->path), NULL);
			free(info->path[i]);
			info->path[i] = tmp;
		}
	}
	return (info->path);
}

char	*check_file_in_path(char **path, char *cmd)
{
	int		i;
	char	*file_path;

	i = 0;
	while (path != NULL && path[++i])
	{
		file_path = ft_strjoin(path[i], cmd);
		if (!file_path)
			return (NULL);
		if (access(file_path, F_OK | X_OK) == 0)
			return (file_path);
		free(file_path);
	}
	return (NULL);
}

char	*find_file(char *cmd, t_info *info)
{
	char	*file_path;

	cmd = ft_strcut(cmd, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	if (ft_strncmp(cmd, "", 1) == 0)
	{
		if (info->fds[0] != -1 || info->initial_count != info->count)
			ft_dprintf(2, "%s: command not found\n", cmd);
		return (free(cmd), NULL);
	}
	file_path = check_file_in_path(info->path, cmd);
	if (!file_path && (info->fds[0] != -1
			|| info->initial_count != info->count))
		ft_dprintf(2, "%s: command not found\n", cmd);
	return (free(cmd), file_path);
}
