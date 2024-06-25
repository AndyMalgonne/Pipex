/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:45:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/25 11:09:56 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (dup2(info->child_fd.c1, 0) == -1 || dup2(info->child_fd.c2, 1) \
		== -1)
			(ft_fsplit(args), exit(127));
		(mclose(info->child_fd.c1), mclose(info->child_fd.c2), mclose(3),
			mclose(5), mclose(6));
		if (info->child_fd.c3 != -1 && info->child_fd.c4 != -1)
			(mclose(info->child_fd.c3), mclose(info->child_fd.c4));
		if (execve(file, args, envp) == -1)
			(perror("execve"), ft_fsplit(args), execve_perm());
	}
	(mclose(info->child_fd.c1), mclose(info->child_fd.c2), ft_fsplit(args));
	return (pid);
}

static void	setup_child_fd(t_info *info, int pipefd[2])
{
	if (info->count == 0)
		info->child_fd = (t_child){info->fds[0], info->fds[1], -1, -1};
	else
		info->child_fd = (t_child){info->fds[0], pipefd[1], pipefd[0],
			info->fds[1]};
}

static void	handle_file_error(char *file, t_info *info, int pipefd[2],
		int *error)
{
	if (!file)
	{
		mclose(info->fds[0]);
		mclose(pipefd[1]);
		*error = -1;
	}
}

static int	exec_commands(char **cmds, t_info *info, char **envp)
{
	char	*file;
	int		pipefd[2];
	int		pid;
	int		error;

	pid = -1;
	error = 0;
	if (info->count < 0)
		return (-1);
	if (pipe(pipefd) == -1)
		return (-1);
	file = find_file(cmds[0], info);
	handle_file_error(file, info, pipefd, &error);
	setup_child_fd(info, pipefd);
	if (file)
		pid = exec_child(file, cmds[0], info, envp);
	else
	{
		mclose(info->fds[0]);
		mclose(pipefd[1]);
		error = -1;
	}
	free(file);
	info->fds[0] = pipefd[0];
	mclose(pipefd[1]);
	if (pid < 0)
		error = -1;
	if (info->count == 0)
	{
		if (error == -1)
			return (-1);
		else
			return (pid);
	}
	info->count--;
	return (exec_commands(cmds + 1, info, envp));
}

int	main(int ac, char **av, char **envp)
{
	int		pid;
	t_info	info;

	info.count = ac - 4;
	if (ac < 5)
		return (ft_dprintf(2, "Error Arg\n"), 1);
	info.fds[0] = open(av[1], O_RDONLY);
	if (info.fds[0] < 0)
		perror(av[1]);
	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
	{
		perror(av[ac - 1]);
		info.path = find_path(envp);
		pid = exec_commands(av + 2, &info, envp);
		if (pid < 0)
			return (mclose(info.fds[0]), mclose(info.fds[1]),
				ft_fsplit(info.path), 1);
		mclose(info.fds[0]);
		mclose(info.fds[1]);
		return (ft_fsplit(info.path), 1);
	}
	else
	{
		info.fds[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (info.fds[1] < 0)
			(mclose(info.fds[0]), perror(av[ac - 1]));
		info.path = find_path(envp);
		pid = exec_commands(av + 2, &info, envp);
		if (pid < 0)
			return (mclose(info.fds[0]), mclose(info.fds[1]),
				ft_fsplit(info.path), 127);
		mclose(info.fds[0]);
		mclose(info.fds[1]);
		return (ft_fsplit(info.path), wait_childs(pid));
	}
}
