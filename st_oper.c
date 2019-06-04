/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_oper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:18:46 by jwinthei          #+#    #+#             */
/*   Updated: 2019/02/27 16:30:18 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int				sort_analis(t_stack *st_st)
{
	int			nb;
	int			i;
	t_stack		*st_tmp;

	if (!st_st || st_st->n == 1)
		return (1);
	nb = st_st->arg;
	st_tmp = st_st->prev;
	while ((st_tmp = st_tmp->next))
	{
		nb = (st_tmp->arg > nb) ? st_tmp->arg : nb;
		if (st_tmp->n == 1)
			break ;
	}
	i = 0;
	while ((st_tmp = st_tmp->next))
	{
		if (st_tmp->arg > st_tmp->next->arg && st_tmp->arg == nb)
			i++;
		else if (st_tmp->arg > st_tmp->next->arg)
			return (0);
		if (st_tmp->next->n == 1)
			break ;
	}
	return ((i) ? 2 : 1);
}

int				repeat_analis(t_stack *st_st, int new_arg)
{
	if (!st_st || st_st->n == 1)
		return (0);
	while (1)
	{
		st_st = st_st->next;
		if (st_st->arg == new_arg)
			return (-1);
		if (st_st->n == 1)
			break ;
	}
	return (0);
}

int				st_swap(t_stack **st_st, char st_name, t_ps *ps)
{
	ft_swap(&st_st[0]->arg, &st_st[0]->next->arg);
	if (st_name && ps)
		if (!(ps->str_op = t_stradd((st_name == 'a') ? "sa" : "sb",\
														ps->str_op)))
			return (-1);
	return (0);
}

int				st_push(t_stack **st_src, t_stack **st_dst,\
											char st_name, t_ps *ps)
{
	t_stack		*st_st;

	if (!(st_src && *st_src))
		return (0);
	st_st = *st_src;
	if (!(*st_dst = st_add(st_st->arg, *st_dst)))
		return (-1);
	st_dst[0]->med = ps->med;
	st_st->next->n = st_st->n - 1;
	st_del(&st_st);
	*st_src = st_st;
	if (st_name && ps)
		if (!(ps->str_op = t_stradd((st_name == 'a') ? "pa" : "pb",\
																ps->str_op)))
			return (-1);
	return (0);
}

int				st_rot(t_stack **st_p, int dir, char st_name, t_ps *ps)
{
	if (!*st_p || st_p[0]->n == 1)
		return (0);
	if (dir)
	{
		st_p[0]->next->n = st_p[0]->n;
		st_p[0]->prev->n = 2;
		st_p[0]->n = 1;
		st_p[0] = st_p[0]->next;
		if (st_name && ps)
			if (!(ps->str_op = t_stradd((st_name == 'a') ?\
									"ra" : "rb", ps->str_op)))
				return (-1);
	}
	else
	{
		st_p[0]->prev->n = st_p[0]->n;
		st_p[0] = st_p[0]->prev;
		st_p[0]->prev->n = 1;
		if (st_name && ps)
			if (!(ps->str_op = t_stradd((st_name == 'a') ?\
									"rra" : "rrb", ps->str_op)))
				return (-1);
	}
	return (0);
}
