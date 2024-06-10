/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:45:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/10 14:57:47 by andymalgonn      ###   ########.fr       */
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

char *find_file(char *cmd, char **path)
{
	int		i = 0;
	char	*file_path;

	cmd = ft_strcut(cmd, ' ');
	if(ft_strchr(cmd, '/') != NULL)
		return (cmd);
	if (ft_strncmp(cmd, "", 1) == 0)
		return (ft_dprintf(2, "%s: command not found\n", cmd), \
		free(cmd), NULL);
	while (path != NULL && path[++i])
	{
		file_path = ft_strjoin(path[i], cmd);
		if (!file_path)
			return (free(cmd), NULL);
		if (access(file_path, F_OK | X_OK) == 0)
			return (free(cmd), file_path);
		free(file_path);
	}
	ft_dprintf(2, "%s: command not found\n", cmd);
	return(NULL);
}

static int	exec_child(char *file, char *cmd, int *fds)
{
	int		pid;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		return (ft_dprintf(2, "Memory Error\n"), -1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (dup2(fds[0], 0) == -1 || dup2(fds[1], 1) == -1)
			return (ft_fsplit(args), -1);
		(mclose(fds[0]), mclose(fds[1]));
		if (fds[2] != -1 && fds[3] != -1)
			(mclose(fds[2]), mclose(fds[3]));
		if (fds[4] != -1 && fds[5] != -1)
			(mclose(fds[4]), mclose(fds[5]));
		if(execve(file, args, NULL) == -1)
			return(perror("execve"), ft_fsplit(args), -1);
	}
	(mclose(fds[0]), mclose(fds[1]), ft_fsplit(args));
	return (pid);
}

static int	exec_commands(char **cmds, char **path, int count, int *fds)
{
	char	*file;
	int		pipefd[2];
	int		pid;
	int		*child_fd;

	if(count < 0)
		return -1;
	if (pipe(pipefd) == -1)
		return (-1);
	file = find_file(cmds[0], path);
	if (count == 0)
		child_fd = (int []){fds[0], fds[1], -1, -1};
	else
		child_fd = (int []){fds[0], pipefd[1], pipefd[0], fds[1]};
	if (file)
		pid = exec_child(file, cmds[0], child_fd);
	else
		(mclose(fds[0]), mclose(pipefd[1]));
	(free(file), fds[0] = pipefd[0]);
	mclose(pipefd[1]);
	if (count == 0)
		return (pid);
	return (exec_commands(cmds + 1, path, count - 1, fds));
}

static int	wait_childs(int pid)
{
    int	wstatus;
    int	code = 0;

    while (errno != ECHILD)
    {
        if (wait(&wstatus) == pid)
        {
            if (WIFEXITED(wstatus))
                code = WEXITSTATUS(wstatus);
            else
                code = 128 + WTERMSIG(wstatus);
        }
    }
    if (pid == -1)
        return (127);
    return (code);
}

void mclose(int fd)
{
	if (fd != -1)
		close(fd);
}

int main(int ac, char **av, char **envp)
{
	char **path;
	int fd[2];
	int pid;
	if (ac <= 4)
		return(ft_dprintf(2, "Error: Not enough Arg\n"), 1);
	fd[0] = open(av[1], O_RDONLY);
	if(fd[0] < 0)
		perror(av[1]);
	fd[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd[1] < 0)
		return (mclose(fd[0]), perror(av[ac - 1]), 1);
	path = find_path(envp);
	if(!path)
		return(mclose(fd[0]), mclose(fd[1]), 1);
	pid = exec_commands(av + 2, path, ac - 4, fd);
	if (pid < 0)
		return(mclose(fd[0]), mclose(fd[1]), ft_fsplit(path), 1);
	mclose(fd[0]);
	mclose(fd[1]);
	return(ft_fsplit(path), wait_childs(pid));
}
