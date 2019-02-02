/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 19:21:58 by iganich           #+#    #+#             */
/*   Updated: 2018/09/30 14:38:12 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <fcntl.h>
# include "../ft_printf/headers/ft_printf.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

typedef struct	s_room
{
	char	*name;
	int		coord[2];
	int		cur_ant;
	int		islast;
	int		*way;
	int		realway;
	int		steps;
}				t_room;

typedef struct	s_data
{
	t_room	**rooms;
	char	*mapinfo;
	int		start;
	int		finish;
	int		ants;
	int		roomcount;
	int		**links;
	int		finished;
	int		started;
	int		temprooms;
	int		*queue;
	int		steps;
	int		colour;
	int		path_p;
	int		status_p;
}				t_data;

int				algo(t_data *lemin, int size);
int				creating_ways(t_data *lemin, int *used, int bestroom, int prev);
void			create_queue(t_data *lemin);
t_room			*freeroom(t_room *room);
void			freelemin(t_data *lemin);
void			clear_map(t_data *lemin);
int				get_min_links(t_data *lemin, int f, int fin, int s);
int				get_best_size(t_data *lemin);
int				get_at_finish(t_data *lemin);
int				read_lemin(t_data *lemin, int *flag);
void			give_mem(t_data *lemin);
void			custom_free(void **memory);
int				is_nbr_str(char *line);
int				set_ants(t_data *lemin, int s_e, char *line);
int				set_room_info(t_data *lemin, int *s_e, char *line);
int				line_type(char *line, int *flag, int res, t_data *lemin);
int				set_links(t_data *lemin, int s_e, char *line);
int				check_xboct(t_data *lemin, int *s_e, int *flag);
void			clear_at_finish(t_data *lemin, int *used);
void			clear_ways(t_data *lemin);
void			again_at_finish(t_data *lemin, int *used);
int				try_ants(t_data *lemin, int size, int allsteps, int flag);
void			realloc_links(t_data *lemin);
t_room			*set_new_room(char *line, char *valid, t_data *lemin, int flag);
int				get_min_way(t_data *lemin, int src, int dst);
void			print_links(t_data *lemin);
int				print_paths(t_data *lemin);
void			print_status(t_data *lemin);
int				get_used_size(int *used, int size);

#endif
