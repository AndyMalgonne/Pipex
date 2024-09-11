/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:46:12 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/09/11 14:38:23 by amalgonn         ###   ########.fr       */
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
		pid = exec_commands(av + 3, info, envp);
		if (pid < 0)
			return (mclose(&info->fds[0]), mclose(&info->fds[1]),
				ft_fsplit(info->path), 1);
		return (mclose(&info->fds[0]), mclose(&info->fds[1]),
			ft_fsplit(info->path), wait_childs(pid), 1);
	}
	return (0);
}

int	pipex_with_outf_w(char **av, int ac, char **envp, t_info info)
{
	int	pid;

	info.fds[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (info.fds[1] < 0)
		(mclose(&info.fds[0]), perror(av[ac - 1]));
	info.path = find_path(envp, &info);
	pid = exec_commands(av + 3, &info, envp);
	if (pid < 0)
		return (mclose(&info.fds[0]), mclose(&info.fds[1]),
			ft_fsplit(info.path), 127);
	(mclose(&info.fds[0]), mclose(&info.fds[1]));
	return (ft_fsplit(info.path), wait_childs(pid));
}

int	setup_info(int ac, char **av, t_info *info)
{
	info->fds[0] = -1;
	info->fds[1] = -1;
	info->count = ac - 4;
	if (info->here_doc)
		info->count = ac - 5;
	info->initial_count = info->count;
	info->here_doc = ft_strncmp(av[1], "here_doc", 9) == 0;
	if ((info->here_doc && ac <= 5) || ac <= 4)
		return (ft_dprintf(2, "Error Arg\n"), 1);
	if (info->here_doc && av++ && ac--)
		info->fds[0] = get_here_doc(av[1]);
	else
		info->fds[0] = open(av[1], O_RDONLY);
	if (info->fds[0] < 0)
		perror(av[1]);
	if (info->here_doc)
		info->fds[1] = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		info->fds[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	if (setup_info(ac, av, &info))
		return (1);
	if (pipex_with_outf_nw(av, ac, envp, &info))
		return (1);
	else
		return (pipex_with_outf_w(av, ac, envp, info));
}
