/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:42:04 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/24 09:22:01 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strcut(char *str, char stop)
{
	size_t	i;

	i = 0;
	if(str == NULL)
		return NULL;
	while (str[i] && str[i] != stop)
		i++;
	return (ft_substr(str, 0, i));
}

void mclose(int fd)
{
	if (fd != -1)
		close(fd);
}