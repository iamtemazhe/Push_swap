/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:25:34 by jwinthei          #+#    #+#             */
/*   Updated: 2019/03/05 15:58:31 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void			st_print(t_stack *st_a, t_stack *st_b, t_ps ps, int mod)
{
	(mod & 0x1) ? ft_printf("\033[2J") : 0;
	(mod & 0x2) ? ft_printf("%13|\n%13|\n%6<Operation:%4s>\n", ps.c_op) : 0;
	(mod & 0x2) ? ft_printf("%12\\./\n%13|\n") : 0;
	ft_printf("|-----------|-----------|");
	ft_printf("\n|  Stack A: |  Stack B: |\n|-----------|-----------|\n");
	while (1)
	{
		if (st_a && st_b && st_a->n >= 1 && st_b->n >= 1)
			ft_printf("|%11d|%11d|%11d\n", st_a->arg, st_b->arg, st_a->med);
		else if (st_a && st_a->n >= 1)
			ft_printf("|%11d|%12|%11d\n", st_a->arg, st_a->med);
		else if (st_b && st_b->n >= 1)
			ft_printf("|%12|%11d|\n", st_b->arg);
		else
			break ;
		st_a = (st_a && st_a->n > 1) ? st_a->next : NULL;
		st_b = (st_b && st_b->n > 1) ? st_b->next : NULL;
	}
	ft_printf("|-----------|-----------|\n");
}

static int		modfinder(const char *str1, const char *str2)
{
	int			mod;

	mod = ((!ft_strcmp(str1, "ra") && !ft_strcmp(str2, "rb")) ||\
		(!ft_strcmp(str1, "rb") && !ft_strcmp(str2, "ra"))) ? 1 : 0;
	mod = ((!ft_strcmp(str1, "sa") && !ft_strcmp(str2, "sb")) ||\
		(!ft_strcmp(str1, "sb") && !ft_strcmp(str2, "sa"))) ? 2 : mod;
	mod = ((!ft_strcmp(str1, "rra") && !ft_strcmp(str2, "rrb")) ||\
		(!ft_strcmp(str1, "rrb") && !ft_strcmp(str2, "rra"))) ? 3 : mod;
	mod = (!mod && ((!ft_strcmp(str1, "ra") && !ft_strcmp(str2, "rra")) ||\
		(!ft_strcmp(str1, "rra") && !ft_strcmp(str2, "ra")) ||\
		(!ft_strcmp(str1, "rb") && !ft_strcmp(str2, "rrb")) ||\
		(!ft_strcmp(str1, "rrb") && !ft_strcmp(str2, "rb")))) ? 4 : mod;
	return (mod);
}

int				optimizoper(t_str **str_op)
{
	int			mod;
	t_str		*s_s;

	if (str_op[0]->n == 1)
		return (0);
	s_s = *str_op;
	while (1)
	{
		s_s = s_s->next;
		if ((mod = modfinder(s_s->str, s_s->prev->str)))
		{
			s_s = s_s->prev;
			t_strdel(&s_s);
			t_strdel(&s_s);
			s_s = (mod == 1) ? t_stradd("rr", s_s) : s_s;
			s_s = (mod == 2) ? t_stradd("ss", s_s) : s_s;
			s_s = (mod == 3) ? t_stradd("rrr", s_s) : s_s;
			if (!s_s)
				return (-1);
		}
		if (s_s->n == 1 || s_s->prev->n == 1)
			break ;
	}
	return (0);
}

void			putoper(t_ps ps)
{
	t_str		*s_s;

	if (!ps.str_op)
		return ;
	s_s = ps.str_op;
	while (1)
	{
		s_s = s_s->prev;
		write(ps.fd, s_s->str, ft_strlen(s_s->str));
		write(ps.fd, "\n", 1);
		if (s_s->prev->n == 1)
			break ;
	}
}
