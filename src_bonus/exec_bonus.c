/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:09:08 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/08/16 23:14:22 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void close_child_fds(t_info	*info) {
    mclose(&info->child_fd.c1);
    mclose(&info->child_fd.c2);
    mclose(&info->child_fd.c3);
    mclose(&info->child_fd.c4);
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
		return (ft_fsplit(args), -1);
	if (pid == 0)
	{
		ft_fsplit(info->path);
		if (dup2(info->child_fd.c1, 0) == -1 || dup2(info->child_fd.c2, 1) \
		== -1)
			(ft_fsplit(args), free(file), close_child_fds(info), exit(127));
		close_child_fds(info);
		if (execve(file, args, envp) == -1)
			(perror("execve"), ft_fsplit(args), free(file), execve_perm());
	}
	(mclose(&info->child_fd.c1), ft_fsplit(args));
	return (pid);
}

int	init_exec_commands(t_info *info, int pipefd[2])
{
	if (info->count < 0)
		return (-1);
	if (info->count >= 1)
		if (pipe(pipefd) < 0)
			return (-1);
	return (0);
}

void	set_child_fd(t_info *info, int pipefd[2])
{
	if (info->count == 0)
		info->child_fd = (t_child){info->fds[0], info->fds[1], -1, -1};
	else
		info->child_fd = (t_child){info->fds[0], pipefd[1], pipefd[0],
			info->fds[1]};
}

int	exec_commands(char **cmds, t_info *info, char **envp)
{
	char	*file;
	int		pipefd[2];
	int		pid;
	int		error;

	pid = -1;
	error = 0;
	pipefd[0] = -1;
	pipefd[1] = -1;
	file = find_file(cmds[0], info);
	if (init_exec_commands(info, pipefd) == -1)
		return (mclose(&info->fds[0]), mclose(&info->fds[1]), -1);
	set_child_fd(info, pipefd);
	if (file)
		pid = exec_child(file, cmds[0], info, envp);
	else
		(mclose(&info->fds[0]), error = -1);
	(free(file), mclose(&pipefd[1]), info->fds[0] = pipefd[0]);
	if (pid < 0)
		error = -1;
	if (info->count == 0)
		return (handle_zero_count(error, pid));
	return (info->count--, exec_commands(cmds + 1, info, envp));
}
