/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:01:31 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/25 13:22:43 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>
# include <errno.h>

typedef struct s_child
{
	int c1;
	int c2;
	int c3;
	int c4;
}	t_child;

typedef struct s_info{
    char **path;
    int count;
    int fds[2];
	t_child	child_fd;
} t_info;

char	*ft_strcut(char *str, char stop);
void	mclose(int fd);
void	execve_perm(void);
char	**find_path(char **envp);
char	*find_file(char *cmd, t_info *info);
int		wait_childs(int pid);
int		outfile_not_writable(char **av, int ac, char **envp, t_info *info);
int		exec_commands(char **cmds, t_info *info, char **envp);
int		handle_zero_count(int error, int pid);


#endif