/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:19:51 by jwinthei          #+#    #+#             */
/*   Updated: 2019/02/27 21:18:39 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static int		checker(t_stack **st_a, t_stack **st_b, t_ps *ps)
{
	int			i;
	t_stack		*st_tmp;

	if (!ps->oper)
		return (0);
	(ps->flg & VM) ? st_print(*st_a, *st_b, *ps, 1) : 0;
	if (ps->oper & PA)
		if (((ps->oper & B) ?\
			st_push(st_a, st_b, 0, ps) : st_push(st_b, st_a, 0, ps)))
			return (-1);
	i = (ps->oper & AB) ? 2 : 1;
	st_tmp = (ps->oper & B) ? *st_b : *st_a;
	while (i-- && (!(ps->oper & PA)))
	{
		if (ps->oper & SA && st_tmp && st_tmp->n > 1)
			ft_swap(&st_tmp->arg, &st_tmp->next->arg);
		if (ps->oper & RRA || ps->oper & RA)
			st_rot(&st_tmp, ps->oper & RA, 0, ps);
		*st_b = (ps->oper & B || (ps->oper & AB && !i)) ? st_tmp : *st_b;
		*st_a = (ps->oper & B || (ps->oper & AB && !i)) ? *st_a : st_tmp;
		st_tmp = *st_b;
	}
	(ps->flg & VM) ? st_print(*st_a, *st_b, *ps, 2) : 0;
	(ps->flg & DM && ps->flg & VM) ? read(1, 0, 1) : 0;
	return (0);
}

static int		oper_analis(const char *line, t_ps *ps)
{
	if (ft_strcmp(line, "sa") && ft_strcmp(line, "ra") &&\
		ft_strcmp(line, "pa") && ft_strcmp(line, "sb") &&\
		ft_strcmp(line, "rb") && ft_strcmp(line, "pb") &&\
		ft_strcmp(line, "rra") && ft_strcmp(line, "rrb") &&\
		ft_strcmp(line, "rrr") && ft_strcmp(line, "ab") &&\
		ft_strcmp(line, "ss") && ft_strcmp(line, "rr"))
		return (-1);
	if (!(ps->c_op = ft_strdup(line)))
		return (-1);
	ps->oper |= (line[0] == 's') ? SA : 0;
	ps->oper |= (line[0] == 'p') ? PA : 0;
	ps->oper |= (line[0] == 'r' && !line[2]) ? RA : 0;
	ps->oper |= (line[2]) ? RRA : 0;
	ps->oper |= (line[1] == 'b' || line[2] == 'b') ? B : 0;
	ps->oper |= (line[1] == 's' || line[2] == 'r' || (line[1] == 'r' &&\
				(line[2] != 'a' && line[2] != 'b'))) ? AB : 0;
	return (0);
}

static int		readncheck(t_stack **st_a, t_stack **st_b, t_ps *ps)
{
	int			err;
	char		*line;

	line = NULL;
	while ((err = get_next_line(ps->fd, &line)))
	{
		if (err == -1)
			return (ft_strerr(err, &line));
		ps->oper = 0;
		if (*line && (oper_analis(line, ps)))
			return (ft_strerr(-1, &line));
		if ((err = checker(st_a, st_b, ps)))
			return (ft_strerr(err, &line) + ft_strerr(0, &ps->c_op));
		(ps->flg & QM && ps->flg & WRM) ?\
			write(ps->med, line, ft_strlen(line)) : 0;
		(ps->flg & QM && ps->flg & WRM) ? write(ps->med, "\n", 1) : 0;
		if (!*line)
			break ;
		ft_strdel(&line);
		ft_strdel(&ps->c_op);
	}
	(ps->flg & VM) ? st_print(*st_a, *st_b, *ps, 1) : 0;
	(line && !*line && !(ps->flg & VM)) ? ft_printf("\033[A") : 0;
	ft_strdel(&line);
	return (((sort_analis(*st_a)) == 1) ? 0 : 1);
}

int				main(int argc, char **argv)
{
	t_stack		*st_a;
	t_stack		*st_b;
	t_ps		ps;
	int			err;

	if (argc < 2)
		return (0);
	if ((arg_finder(argc, argv, &st_a, &ps)) == -1)
		return (ft_puterr(-1, "Error") + st_err(0, &st_a));
	if (!st_a)
		return (0);
	(ps.flg & VM) ? st_print(st_a, 0, ps, 0) : 0;
	ps.fd = (ps.flg & WRM) ? ps.fd : 0;
	if ((ps.med = (ps.flg & QM && ps.flg & WRM) ?\
		open("out_check", O_WRONLY | O_TRUNC | O_CREAT) : 0) == -1)
		return (ft_puterr(-1, "Error") + st_err(0, &st_a));
	if ((err = readncheck(&st_a, &st_b, &ps)) == -1)
		ft_puterr(err, "Error");
	else if (st_b || err)
		write((ps.flg & QM && ps.flg & WRM) ? ps.med : 1, "KO\n", 3);
	else
		write((ps.flg & QM && ps.flg & WRM) ? ps.med : 1, "OK\n", 3);
	(ps.flg & QM) ? close(ps.med) : 0;
	(ps.flg & WRM) ? close(ps.fd) : 0;
	return (st_err(err, &st_a) + st_err(0, &st_b));
}
