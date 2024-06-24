/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:45:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/24 10:50:39 by andymalgonn      ###   ########.fr       */
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

char *find_file(char *cmd, t_info *info) {
    int i = 0;
    char *file_path;

    cmd = ft_strcut(cmd, ' ');
    if (ft_strchr(cmd, '/') != NULL)
        return cmd;
    if (ft_strncmp(cmd, "", 1) == 0)
        return (ft_dprintf(2, "%s: command not found\n", cmd), free(cmd), NULL);

    while (info->path != NULL && info->path[++i]) {
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


static int	exec_child(char *file, char *cmd, t_info *info, char **envp)
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
		if (dup2(info->child_fd.c1, 0) == -1 || dup2(info->child_fd.c2, 1) == -1)
			(ft_fsplit(args), exit(127));
		(mclose(info->child_fd.c1), mclose(info->child_fd.c2));
		if (info->child_fd.c3 != -1 && info->child_fd.c4 != -1)
			(mclose(info->child_fd.c3), mclose(info->child_fd.c4));
		if(execve(file, args, envp) == -1)
		{
    	perror("execve");
    	ft_fsplit(args);
    	if (errno == EACCES) 
        	exit(126);
    	else
        	exit(127); 
		}
	}
	(mclose(info->child_fd.c1), mclose(info->child_fd.c2), ft_fsplit(args));
	return (pid);
}

static int	exec_commands(char **cmds, t_info *info, char **envp)
{
    char	*file;
    int		pipefd[2];
    int		pid = -1;
    int		error = 0;

    if(info->count < 0)
        return -1;
    if (pipe(pipefd) == -1)
        return (-1);
    file = find_file(cmds[0], info);
	if(!file)
		(mclose(info->fds[0]), mclose(pipefd[1]));
    if (info->count == 0)
        info->child_fd = (t_child){info->fds[0], info->fds[1], -1, -1};
    else
        info->child_fd = (t_child){info->fds[0], pipefd[1], pipefd[0], info->fds[1]};
    if (file)
        pid = exec_child(file, cmds[0], info, envp);
    else
	{
        (mclose(info->fds[0]), mclose(pipefd[1]));
        error = -1;
    }
    free(file);
    info->fds[0] = pipefd[0];
    mclose(pipefd[1]);
    if (pid < 0)
        error = -1;
    if (info->count == 0)
	{
    	if (error == -1) {
        	return -1;
    } 
	else 
        return pid;
}
	info->count--;
    return (exec_commands(cmds + 1, info, envp));
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

int main(int ac, char **av, char **envp)
{
	int pid;
	t_info info;
    info.count = ac - 4;
	
	if (ac != 5)
		return(ft_dprintf(2, "Error Arg\n"), 1);
	info.fds[0] = open(av[1], O_RDONLY);
	if(info.fds[0] < 0)
		perror(av[1]);
	if(access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
	{
		perror(av[ac - 1]);
		info.path = find_path(envp);
		pid = exec_commands(av + 2, &info, envp);
		if (pid < 0)
			return(mclose(info.fds[0]), mclose(info.fds[1]), ft_fsplit(info.path), 1);
		mclose(info.fds[0]);
		mclose(info.fds[1]);
		return(ft_fsplit(info.path), 1);
	}
	else
	{
	info.fds[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (info.fds[1] < 0)
		(mclose(info.fds[0]), perror(av[ac - 1]));
	info.path = find_path(envp);
	pid = exec_commands(av + 2, &info, envp);
	if (pid < 0)
		return(mclose(info.fds[0]), mclose(info.fds[1]), ft_fsplit(info.path), 127);
	mclose(info.fds[0]);
	mclose(info.fds[1]);
	return(ft_fsplit(info.path), wait_childs(pid));
	}
}
