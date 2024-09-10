/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:45:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/09/10 11:24:05 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_with_outf_nw(char **av, int ac, char **envp, t_info *info)
{
	int	pid;

	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
	{
		perror(av[ac - 1]);
		info->path = find_path(envp, info);
		pid = exec_commands(av + 2, info, envp);
		if (pid < 0)
			return (mclose(info->fds[0]), mclose(info->fds[1]),
				ft_fsplit(info->path), 1);
		return (mclose(info->fds[0]), mclose(info->fds[1]),
			ft_fsplit(info->path), wait_childs(pid), 1);
	}
	return (0);
}

int	pipex_with_outf_w(char **av, int ac, char **envp, t_info info)
{
	int	pid;

	info.fds[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (info.fds[1] < 0)
		(mclose(info.fds[0]), perror(av[ac - 1]));
	info.path = find_path(envp, &info);
	pid = exec_commands(av + 2, &info, envp);
	return (mclose(info.fds[0]), mclose(info.fds[1]),
		ft_fsplit(info.path), wait_childs(pid));
}

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	info.count = ac - 4;
	info.fds[0] = -1;
	info.fds[1] = -1;
	if (ac != 5)
		return (ft_dprintf(2, "Error Arg\n"), 1);
	info.fds[0] = open(av[1], O_RDONLY);
	if (info.fds[0] < 0)
		perror(av[1]);
	if (pipex_with_outf_nw(av, ac, envp, &info))
		return (1);
	else
		return (pipex_with_outf_w(av, ac, envp, info));
}
