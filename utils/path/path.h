/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:59:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 16:10:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# ifndef NEIGHBOUR_DISTANCE
#  define NEIGHBOUR_DISTANCE 64
# endif

typedef struct s_a_point
{
	int					x;
	int					y;
	int					weight;
	int					heuristic_approxim;
	int					passed_way;
	struct s_a_point	*origin;
}						t_a_point;

typedef struct s_point_node
{
	t_a_point			*point;
	struct s_point_node	*next;
}						t_point_node;

typedef struct s_point_list
{
	t_point_node		*points;
}						t_point_list;

typedef struct s_a_store
{
	t_a_point			*dest;
	t_point_list		*game_objs;
	t_point_list		*opened;
	t_point_list		*closed;
}						t_a_store;

typedef struct s_path
{
	t_point_list		*point_list;
	int					counter;
	int					length;
}						t_path;

// cacl_path return the path from enemy to the player
t_path					*calc_path(t_a_point *src, t_a_point *dest,
							t_point_list *g_objs);

// POINT

t_a_point				*make_a_point(int x, int y, t_a_point *origin);
void					*free_a_point(t_a_point *point);
void					pnt_calc_weight(t_a_point *point, t_a_point *dest);
int						is_equal_point(t_a_point *a, t_a_point *b);

// POINT NODE

t_point_node			*make_point_node(t_a_point *point);
void					*free_point_node(t_point_node *node);

// POINT LIST

t_point_list			*make_point_list(void);
int						lst_add_point(t_point_list *list, t_a_point *point);
t_a_point				*lst_get_min_point(t_point_list *list);
void					lst_rem_point(t_point_list *list, t_a_point *point);
t_a_point				*lst_check_by_coord(t_point_list *list, int x, int y);
int						lst_length(t_point_list *list);
t_point_list			*lst_reverse(t_point_list *list);
void					*free_point_list(t_point_list *list);
// A* ALG STORAGE

t_a_store				*make_a_store(t_a_point *src, t_a_point *dest,
							t_point_list *g_objs);
void					*free_a_store(t_a_store *store);
t_a_point				*a_check_by_coords(t_a_store *store, int x, int y);

// PATH

t_path					*make_path(t_point_list *list);
void					*free_path(t_path *path);
t_a_point				*get_next_point(t_path *path);
#endif // !PATH_H