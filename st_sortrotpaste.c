/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sortrotpaste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:00:30 by jwinthei          #+#    #+#             */
/*   Updated: 2019/03/05 16:21:17 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static int		st_rotforpa(t_stack **st_st, t_stack **st_src, t_ps *ps)
{
	t_stack		*st_t;
	int			cc;

	cc = 0;
	st_t = *st_st;
	while (1)
	{
		if ((st_t->prev->arg > st_t->arg && st_t->next->arg > st_t->arg &&\
		(st_t->arg > st_src[0]->arg || st_src[0]->arg > st_t->prev->arg)) ||\
		(st_t->prev->arg < st_src[0]->arg && st_src[0]->arg < st_t->arg))
			break ;
		st_t = st_t->next;
		cc++;
	}
	if (cc <= (st_st[0]->n + 1) / 2)
		while (cc-- > 0)
			if (st_rot(st_st, 1, 'a', ps))
				return (-1);
	if (cc > (st_st[0]->n + 1) / 2)
		while (st_st[0]->n - cc++ > 0)
			if (st_rot(st_st, 0, 'a', ps))
				return (-1);
	return (0);
}

static int		pa_medanalis(t_stack **st_a, t_stack **st_b, t_ps *ps)
{
	t_stack		*st_tmp;
	int			cc;

	cc = 0;
	if (!st_b[0])
		return (0);
	if (st_a[0]->n == 1)
		return (st_push(st_b, st_a, 'a', ps));
	st_tmp = *st_b;
	while (st_tmp->arg < ps->med)
	{
		if (st_tmp->n == 1)
			break ;
		st_tmp = st_tmp->next;
		cc++;
	}
	cc = (cc == st_b[0]->n) ? 0 : cc;
	while (cc-- > 0)
		if (st_rot(st_b, 1, 'b', ps))
			return (-1);
	st_rotforpa(st_a, st_b, ps);
	if (st_b[0]->arg >= ps->med || st_b[0]->n == 1)
		return (st_push(st_b, st_a, 'a', ps));
	return (0);
}

static int		med_val(t_stack *st_st, t_ps *ps, int mod)
{
	int			i;
	t_stack		*st_tmp;

	i = 0;
	ps->ss = 0;
	st_tmp = st_st;
	while (1)
	{
		if (mod > 1)
			i += (st_tmp->arg >= ps->med) ? 1 : 0;
		else
			i += (st_tmp->arg < ps->med) ? 1 : 0;
		ps->ss += st_tmp->arg;
		if (st_tmp->n == 1)
			break ;
		st_tmp = st_tmp->next;
	}
	if (!i && st_st->n < 2)
		return (0);
	ps->med = (!i || !mod) ? (int)(ps->ss / st_st->n) : ps->med;
	return (1);
}

int				sort_a(t_stack **st_a, t_stack **st_b, t_ps *ps)
{
	int			err;

	err = 0;
	med_val(*st_a, ps, 0);
	while (med_val(*st_a, ps, 1))
	{
		if ((sort_analis(*st_a)) == 1)
			break ;
		if (st_a[0]->arg <= ps->med)
			err = st_push(st_a, st_b, 'b', ps);
		else if ((st_a[0]->n < 4 || st_a[0]->n > 150) &&\
		st_a[0]->arg > st_a[0]->next->arg && (st_a[0]->next->arg > ps->med ||\
		(*st_b && st_b[0]->arg < st_b[0]->next->arg)))
		{
			if (st_swap(st_a, 'a', ps))
				return (-1);
			if (*st_b && st_b[0]->arg < st_b[0]->next->arg)
				err = st_swap(st_b, 'b', ps);
		}
		else
			err = st_rot(st_a, 1, 'a', ps);
		if (err)
			return (-1);
	}
	return (0);
}

int				sort_b(t_stack **st_a, t_stack **st_b, t_ps *ps)
{
	(*st_b) ? med_val(*st_b, ps, 0) : 0;
	while (1)
	{
		(*st_b) ? med_val(*st_b, ps, 2) : 0;
		if (st_a[0]->n < 4 && st_a[0]->arg > st_a[0]->next->arg &&\
				st_a[0]->next->next->arg >= st_a[0]->next->arg)
		{
			if (st_swap(st_a, 'a', ps))
				return (-1);
			if (*st_b && st_b[0]->arg < st_b[0]->next->arg)
				if (st_swap(st_b, 'b', ps))
					return (-1);
		}
		else
		{
			if ((sort_analis(*st_a)) == 1 && !*st_b)
				break ;
			if ((*st_b) ? pa_medanalis(st_a, st_b, ps) :\
											st_rot(st_a, 0, 'a', ps))
				return (-1);
		}
	}
	return (0);
}
