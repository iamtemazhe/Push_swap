/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:08:19 by jwinthei          #+#    #+#             */
/*   Updated: 2018/11/29 16:40:14 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(size_t size, char *dest, char *buf)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	tmp = (char*)malloc(sizeof(*tmp) * (size - BUF_SIZE + 1));
	while (dest[++i])
		tmp[i] = dest[i];
	tmp[i] = '\0';
	free(dest);
	dest = (char*)malloc(sizeof(*dest) * (size + 1));
	i = -1;
	while (tmp[++i])
		dest[i] = tmp[i];
	j = 0;
	while (buf[j])
		dest[i++] = buf[j++];
	dest[i] = '\0';
	free(tmp);
	return (dest);
}
