/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:53:05 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/25 13:22:50 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mclose(int fd)
{
	if (fd != -1)
		close(fd);
}

int	wait_childs(int pid)
{
	int	wstatus;
	int	code;

	code = 0;
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

void	execve_perm(void)
{
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

int	handle_zero_count(int error, int pid)
{
	if (error == -1)
		return (-1);
	else
		return (pid);
}

int	outfile_not_writable(char **av, int ac, char **envp, t_info *info)
{
	int	pid;

	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
	{
		perror(av[ac - 1]);
		info->path = find_path(envp);
		pid = exec_commands(av + 2, info, envp);
		if (pid < 0)
		{
			return (mclose(info->fds[0]), mclose(info->fds[1]),
				ft_fsplit(info->path), 1);
		}
		return (mclose(info->fds[0]), mclose(info->fds[1]),
			ft_fsplit(info->path), 1);
	}
	return (0);
}
