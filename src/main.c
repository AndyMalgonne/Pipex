/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:45:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/05/20 13:01:19 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if(!envp[i])
		return (NULL);
	path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/')
		{
			tmp = ft_strjoin(path[i], "/");
			if (!tmp)
				return (ft_fsplit(path), NULL);
			free(path[i]);
			path[i] = tmp;
		}
		i++;
	}
	return (path);	
}

// int main(int ac, char **av, char **envp)
// {
// 	char **path;
// 	int fd[2];
// 	fd[0] = open(av[1], O_RDONLY);
// 	fd[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	if(fd[0] < 0)
// 		return (perror(av[1]), 1);
// 	if(fd[1] < 0)
// 		return (close(fd[0]), perror(av[ac - 1]), 1);
// 	// path = find_path(envp);
// 	return(0);
// }

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;

    char **paths = find_path(envp);

    if (paths == NULL)
    {
        printf("PATH not found\n");
        return 1;
    }

    // Print the paths
    for (int i = 0; paths[i] != NULL; i++)
    {
        printf("Path %d: %s\n", i, paths[i]);
    }

    // Free the paths
    for (int i = 0; paths[i] != NULL; i++)
    {
        free(paths[i]);
    }
    free(paths);

    return 0;
}