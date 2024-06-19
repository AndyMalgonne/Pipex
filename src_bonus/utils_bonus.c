/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:46:07 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/13 15:03:21 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strcut(char *str, char stop)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != stop)
		i++;
	return (ft_substr(str, 0, i));
}