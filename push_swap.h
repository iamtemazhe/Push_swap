/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:30:26 by jwinthei          #+#    #+#             */
/*   Updated: 2019/02/27 19:24:21 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"

# define SA  0x01
# define RA  0x02
# define RRA 0x04
# define PA  0x08
# define B   0x10
# define AB  0x20

# define DM  0x01
# define FM  0x02
# define VM  0x04
# define WRM 0x08
# define QM  0x10
# define PS  0x80

typedef struct		s_stack
{
	int				arg;
	int				n;
	int				med;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

typedef struct		s_str
{
	char			*str;
	int				n;
	struct s_str	*prev;
	struct s_str	*next;
}					t_str;

typedef struct		s_ps
{
	t_str			*str_op;
	char			*c_op;
	int				oper;
	int				med;
	int				flg;
	int				fd;
	long long		ss;
}					t_ps;

void				st_del(t_stack **st_p);
void				t_strdel(t_str **str_p);
void				putoper(t_ps ps);
void				st_print(t_stack *st_a, t_stack *st_b, t_ps ps, int mod);

int					pratoi(char **src, int *pr_nb);
int					optimizoper(t_str **str_op);
int					sort_analis(t_stack *st_st);
int					repeat_analis(t_stack *st_st, int new_arg);
int					arg_finder(int argc, char **argv, t_stack **st_a, t_ps *ps);
int					t_strerr(int retv, t_str **str_p);
int					st_err(int retv, t_stack **st_p);
int					st_push(t_stack **st_src, t_stack **st_dst, char st_name,\
																	t_ps *ps);
int					st_rot(t_stack **st_p, int dir, char st_name, t_ps *ps);
int					st_swap(t_stack **st_p, char st_name, t_ps *ps);
int					sort_a(t_stack **st_a, t_stack **st_b, t_ps *ps);
int					sort_b(t_stack **st_a, t_stack **st_b, t_ps *ps);
int					sort_meda(t_stack **st_a, t_stack **st_b, t_ps *ps,\
																	int med);
int					sort_medb(t_stack **st_a, t_stack **st_b, t_ps *ps,\
																	int med);

t_stack				*st_new(int arg, int n);
t_stack				*st_add(int arg, t_stack *st_dst);

t_str				*t_strnew(char *str, int n);
t_str				*t_stradd(char *str, t_str *str_dst);
#endif
