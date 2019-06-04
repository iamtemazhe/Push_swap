/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:10:50 by jwinthei          #+#    #+#             */
/*   Updated: 2019/02/20 13:24:00 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reader(const char *src)
{
	int		rd[3];
	char	*str_input;
	char	*str_buf;

	rd[1] = 0;
	rd[2] = BUF_SIZE;
	if (ft_strlen(src))
		if ((rd[0] = open(src, O_RDONLY)) == -1)
			return (char*)("");
	str_input = (char*)malloc(sizeof(*str_input) * (BUF_SIZE + 1));
	str_buf = (char*)malloc(sizeof(*str_buf) * (BUF_SIZE + 1));
	rd[1] = read(rd[0], str_input, BUF_SIZE);
	str_input[rd[1]] = '\0';
	while (rd[1])
	{
		rd[2] += BUF_SIZE;
		rd[1] = read(rd[0], str_buf, BUF_SIZE);
		str_buf[rd[1]] = '\0';
		if (rd[1])
			str_input = ft_realloc(rd[2], str_input, str_buf);
	}
	if (ft_strlen(src))
		close(rd[0]);
	free(str_buf);
	return (str_input);
}
