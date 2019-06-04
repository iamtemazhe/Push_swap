/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_analis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:21:02 by jwinthei          #+#    #+#             */
/*   Updated: 2019/03/05 13:45:44 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static int		stafiller(char *str, t_stack **st_a)
{
	int			cc;
	int			nb;
	int			pr_nb;

	cc = 0;
	while (str && *str)
	{
		nb = pratoi(&str, &pr_nb);
		if (pr_nb > 0 && !(*st_a = st_add(nb, *st_a)))
			return (-1);
		if (pr_nb < 0 || (!cc && !pr_nb) ||\
			(pr_nb > 0 && repeat_analis(*st_a, nb)))
			return (-1);
		cc++;
		st_rot(st_a, 1, 0, 0);
	}
	return (0);
}

static int		argreader(const char *file_name, t_stack **st_a)
{
	int			fd;
	int			err;
	char		*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (-1);
	line = NULL;
	while ((err = get_next_line(fd, &line)))
	{
		if (err == -1)
			return (ft_strerr(err, &line));
		if (stafiller(line, st_a))
			return (ft_strerr(-1, &line));
		(line && *line) ? ft_strdel(&line) : NULL;
	}
	close(fd);
	return (0);
}

static int		flg_finder(char **argv, t_stack **st_a, t_ps *ps, int *i)
{
	if (*argv[*i] == 'v' && !(ps->flg & VM))
		ps->flg |= VM;
	else if (*argv[*i] == 'd' && !(ps->flg & DM))
		ps->flg |= DM;
	else if (*argv[*i] == 'q' && !(ps->flg & QM))
		ps->flg |= QM;
	else if (*argv[*i] == 'f' && !(ps->flg & FM))
	{
		ps->flg = ((argreader(argv[++*i], st_a)) == -1) ? -1 : ps->flg | FM;
		return ((ps->flg == -1) ? -1 : -2);
	}
	else if (*argv[*i] == 'F' && !(ps->flg & WRM))
	{
		ps->flg |= WRM;
		if ((ps->fd = open(argv[++*i], (ps->flg & PS) ?\
			O_WRONLY | O_CREAT | O_TRUNC : O_RDWR, S_IRUSR | S_IWUSR)) == -1)
			return (-1);
		return (-2);
	}
	else
		return (-1);
	return (0);
}

static int		flg_analis(int argc, char **argv, t_stack **st_a, t_ps *ps)
{
	int			i;
	int			retv;

	i = 0;
	while (++i < argc)
	{
		while (*argv[i] && (*argv[i] == ' ' || *argv[i] == '\n' ||\
				*argv[i] == '\r' || *argv[i] == '\t' || *argv[i] == '\v'))
			argv[i]++;
		if (*argv[i] != '-' || *argv[i] == '+' ||\
			('0' <= *(argv[i] + 1) && *(argv[i] + 1) <= '9'))
			break ;
		while (*(++argv[i]))
		{
			if ((retv = flg_finder(argv, st_a, ps, &i)) == -2)
				break ;
			else if (retv)
				return ((retv == -1) ? 0 : retv);
		}
	}
	return (i);
}

int				arg_finder(int argc, char **argv, t_stack **st_a, t_ps *ps)
{
	int			i;

	ps->c_op = NULL;
	if ((i = flg_analis(argc, argv, st_a, ps) - 1) == -1)
		return (-1);
	while (++i < argc)
		if (stafiller(argv[i], st_a))
			return (-1);
	return (0);
}
