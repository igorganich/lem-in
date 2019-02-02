/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 17:45:54 by iganich           #+#    #+#             */
/*   Updated: 2018/09/30 16:58:33 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/lem_in.h"
#include <stdlib.h>

void	default_solution(t_data *lemin)
{
	create_queue(lemin);
	clear_map(lemin);
	get_min_links(lemin, 0, lemin->finish, 1);
	lemin->steps = get_best_size(lemin) + lemin->ants /
		get_at_finish(lemin) - get_at_finish(lemin);
	while (!algo(lemin, lemin->steps))
		lemin->steps++;
	ft_printf("\n");
}

void	simple_solution(t_data *lemin)
{
	int i;
	int c;

	c = lemin->colour;
	i = 0;
	if (lemin->path_p == 1)
		ft_printf("\x1b[%dm[\x1b[%dm%s\x1b[%dm]\x1b\[%dm->\x1b[%dm\
[\x1b[%dm%s\x1b[%dm]\n",
				c * 31, c * 33,
				lemin->rooms[lemin->start]->name,
				c * 31, c * 32,
				c * 31, c * 33,
				lemin->rooms[lemin->finish]->name,
				c * 31);
	ft_printf("\n");
	while (++i <= lemin->ants)
		ft_printf("\x1b[%dmL\x1b[%dm%i\x1b[%dm-\x1b[%dm%s ", lemin->colour * 34,
				lemin->colour * 31, i, lemin->colour * 32,
				lemin->colour * 33, lemin->rooms[lemin->finish]->name);
	ft_printf("\n");
}

int		err_case(t_data *lemin)
{
	int i;

	i = -1;
	while (++i < lemin->roomcount)
	{
		if (lemin->links[i][lemin->finish] == 1)
			if (lemin->links[lemin->start][i])
				return (lemin->links[lemin->start][i]);
	}
	return (0);
}

int		main(void)
{
	t_data	*lemin;
	int		flag;
	int		ret;

	flag = 0;
	lemin = (t_data*)ft_memalloc(sizeof(t_data));
	lemin->start = -1;
	lemin->finish = -1;
	lemin->mapinfo = ft_memalloc(1);
	if (read_lemin(lemin, &flag) == -1 && flag != 2)
		ft_printf("\x1b[%dmERROR\n", lemin->colour * 31);
	else
	{
		give_mem(lemin);
		if ((ret = get_min_links(lemin, lemin->start, lemin->finish, 1)) == 0)
			ret = err_case(lemin);
		if (ret == 1)
			simple_solution(lemin);
		else if (ret != 0)
			default_solution(lemin);
		else
			ft_printf("\x1b[%dmERROR\n", lemin->colour * 31);
	}
	freelemin(lemin);
	return (0);
}
