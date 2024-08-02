/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:08:45 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/08/02 18:45:34 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_heredoc_file(void)
{
	char	*file;
	int		size;

	size = 2;
	file = NULL;
	file = ft_calloc(size, sizeof(char));
	if (!file)
		return (NULL);
	ft_memset(file, 'a', size - 1);
	while (access(file, F_OK) != 0 && errno != ENOENT)
	{
		free(file);
		if (++size < 0)
			return (NULL);
		file = ft_calloc(size, sizeof(char));
		if (!file)
			return (NULL);
		ft_memset(file, 'a', size - 1);
	}
	return (file);
}

int	write_to_heredoc(int fd, char *del)
{
	char	*gnl;

	ft_printf("here_doc > ");
	gnl = get_next_line(0);
	while (gnl)
	{
		if (ft_strncmp(gnl, del, ft_strlen(del) + 1) == 0)
			break ;
		ft_putstr_fd(gnl, fd);
		free(gnl);
		ft_printf("here_doc > ");
		gnl = get_next_line(0);
	}
	if (!gnl)
		return (-1);
	free(gnl);
	return (0);
}

int	get_here_doc(char *del)
{
	char	*file;
	t_info	info;

	del = ft_strjoin(del, "\n");
	if (!del)
		return (-1);
	file = find_heredoc_file();
	if (!file || !del)
		return (free(del), free(file), -1);
	info.fds[0] = open(file, O_WRONLY | O_CREAT, 0644);
	info.fds[1] = open(file, O_RDONLY);
	(unlink(file), free(file));
	if (info.fds[0] < 0 || info.fds[1] < 0)
		return (free(del), close(info.fds[0]), close(info.fds[1]), -1);
	if (write_to_heredoc(info.fds[0], del) < 0)
		return (free(del), close(info.fds[0]), close(info.fds[1]), -1);
	return (free(del), close(info.fds[0]), info.fds[1]);
}
