/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:01:31 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/09/11 14:22:16 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_child
{
	int		c1;
	int		c2;
	int		c3;
	int		c4;
}			t_child;

typedef struct s_info
{
	char	**path;
	int		count;
	int		initial_count;
	int		fds[2];
	int		here_doc;
	t_child	child_fd;
}			t_info;

char		*ft_strcut(char *str, char stop);
void		mclose(int *fd);
void		execve_perm(void);
char		**find_path(char **envp, t_info *info);
char		*find_file(char *cmd, t_info *info);
int			wait_childs(int pid);
int			exec_commands(char **cmds, t_info *info, char **envp);
int			handle_zero_count(int error, int pid);
int			exec_commands(char **cmds, t_info *info, char **envp);

//Bonus

int			get_here_doc(char *del);

#endif
