/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:01:42 by jwinthei          #+#    #+#             */
/*   Updated: 2019/03/05 16:25:12 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static int		push_swap(t_stack **st_a, t_stack **st_b, t_ps *ps)
{
	int			n;

	if ((sort_analis(*st_a)) == 1)
		return (0);
	n = st_a[0]->n;
	if (n > 3)
		if (sort_a(st_a, st_b, ps))
			return (-1);
	if ((n <= 3) || (n >= 10 && n <= 150))
	{
		if (sort_b(st_a, st_b, ps))
			return (-1);
	}
	else
		while (1)
		{
			if (!*st_b && (sort_analis(*st_a) == 1))
				break ;
			if (((*st_b) ? sort_medb(st_a, st_b, ps, st_b[0]->med) : 0))
				return (-1);
			if (sort_meda(st_a, st_b, ps, st_a[0]->med))
				return (-1);
		}
	return (optimizoper(&ps->str_op));
}

int				main(int argc, char **argv)
{
	t_stack		*st_a;
	t_stack		*st_b;
	t_ps		ps;
	int			err;

	if (argc < 2)
		return (0);
	ps.flg = PS;
	ps.str_op = NULL;
	if ((arg_finder(argc, argv, &st_a, &ps)) == -1)
		return (ft_puterr(-1, "Error") + st_err(0, &st_a));
	ps.fd = (ps.flg & WRM) ? ps.fd : 1;
	if ((err = push_swap(&st_a, &st_b, &ps)) == -1)
		ft_puterr(err, "Error");
	(!err) ? putoper(ps) : NULL;
	(ps.flg & WRM) ? close(ps.fd) : 0;
	return (st_err(err, &st_a) + st_err(0, &st_b) + t_strerr(0, &ps.str_op));
}
