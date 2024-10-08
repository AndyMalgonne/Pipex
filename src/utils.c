/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:53:05 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/09/11 13:27:05 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mclose(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

int	wait_childs(int pid)
{
	int	wstatus;
	int	code;

	wstatus = 0;
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
