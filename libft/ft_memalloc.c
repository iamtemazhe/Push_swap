/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:51:05 by jwinthei          #+#    #+#             */
/*   Updated: 2018/11/23 17:44:25 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*dst;

	dst = malloc(size);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
		((unsigned char*)dst)[i++] = '\0';
	return (dst);
}
