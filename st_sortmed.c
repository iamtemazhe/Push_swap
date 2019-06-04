/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sortmed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:47:09 by jwinthei          #+#    #+#             */
/*   Updated: 2019/03/05 16:19:38 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static int		medival(t_stack *st_st, t_ps *ps, int mod, int med)
{
	int			i;

	i = 0;
	ps->oper = 0;
	ps->ss = 0;
	while (1)
	{
		if (st_st->med == med)
		{
			if (mod > 1)
				i += (st_st->arg >= ps->med) ? 1 : 0;
			else
				i += (st_st->arg < ps->med) ? 1 : 0;
			ps->ss += st_st->arg;
			ps->oper++;
		}
		if (st_st->n == 1)
			break ;
		st_st = st_st->next;
	}
	if ((!i && (mod == 1 || mod == 3)) || !ps->oper)
		return (0);
	ps->med = (!i || !mod || mod == 2) ? (int)(ps->ss / ps->oper) : ps->med;
	return (1);
}

static int		check_med(t_stack *st_st, t_ps *ps, int med)
{
	int			i;
	t_stack		*st_tmp;

	i = 0;
	if (med)
		i = 0;
	st_tmp = st_st;
	while (1)
	{
		i += (st_tmp->arg < ps->med) ? 1 : 0;
		if (st_tmp->n == 1)
			break ;
		st_tmp = st_tmp->next;
	}
	return (i);
}

static int		swapper(t_stack **st_a, t_stack **st_b, t_ps *ps, int mod)
{
	if (mod == 'a')
	{
		if (st_swap(st_a, 'a', ps))
			return (-1);
		if (*st_b && st_b[0]->arg < st_b[0]->next->arg &&\
			st_b[0]->med == st_b[0]->next->med)
			if (st_swap(st_b, 'b', ps))
				return (-1);
	}
	else if (mod == 'b')
	{
		if (st_swap(st_b, 'b', ps))
			return (-1);
		if (st_a[0]->arg > st_a[0]->next->arg &&\
			st_a[0]->med == st_a[0]->next->med)
			if (st_swap(st_a, 'a', ps))
				return (-1);
	}
	return (0);
}

int				sort_meda(t_stack **st_a, t_stack **st_b, t_ps *ps, int med)
{
	int			err;
	int			s;
	int			c;

	medival(*st_a, ps, 0, med);
	while (1)
	{
		if ((s = sort_analis(*st_a)) == 1)
			break ;
		if (st_a[0]->arg < ps->med)
			err = st_push(st_a, st_b, 'b', ps);
		else if (ps->oper < 10 && st_a[0]->arg > st_a[0]->next->arg)
			err = swapper(st_a, st_b, ps, 'a');
		else if ((!(c = check_med(*st_a, ps, med)) || s) &&\
									(st_a[0]->prev->med == med))
			err = st_rot(st_a, 0, 'a', ps);
		else if ((st_a[0]->med == med && !s && c) ||\
							st_a[0]->med == st_a[0]->arg)
			err = st_rot(st_a, 1, 'a', ps);
		else
			medival(*st_a, ps, 0, med);
		if (err)
			return (-1);
	}
	return (0);
}

int				sort_medb(t_stack **st_a, t_stack **st_b, t_ps *ps, int med)
{
	int			err;
	int			n;

	(*st_b) ? medival(*st_b, ps, 2, med) : 0;
	while ((n = (*st_b) ? medival(*st_b, ps, 3, med) : 0))
	{
		if (!*st_b)
			break ;
		if (st_b[0]->arg >= ps->med && st_b[0]->med == med)
			err = st_push(st_b, st_a, 'a', ps);
		else if (ps->oper < 10 && st_b[0]->med == st_b[0]->next->med &&\
									st_b[0]->arg < st_b[0]->next->arg)
			err = swapper(st_a, st_b, ps, 'b');
		else if (st_b[0]->med == med)
			err = st_rot(st_b, 1, 'b', ps);
		if (err)
			return (-1);
	}
	while (*st_b && st_b[0]->prev->med == med && ps->oper < st_b[0]->n)
		if (st_rot(st_b, 0, 'b', ps))
			return (-1);
	return (0);
}
