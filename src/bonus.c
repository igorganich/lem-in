/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 14:26:38 by iganich           #+#    #+#             */
/*   Updated: 2018/10/14 11:16:30 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		get_used_size(int *used, int size)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (++i < size)
		if (used[i])
			count++;
	return (count);
}

void	print_status(t_data *lemin)
{
	int c;
	int i;

	c = lemin->colour;
	if (!lemin->status_p)
		return ;
	i = -1;
	ft_printf("\n\x1b[%dmin start - \x1b[%dm%d, \x1b[%dm finished\
	- \x1b[%dm%d\n",
			c * 31, c * 35, lemin->ants
			- lemin->started, c * 31, c * 35, lemin->finished);
	while (++i < lemin->roomcount)
	{
		if (i == lemin->start || i == lemin->finish)
			continue;
		ft_printf("\x1b[%dm[\x1b[%dm%s\x1b[%dm]\x1b[%dm-\x1b[%dm%d ",
				c * 31, c * 33, lemin->rooms[i]->name,
				c * 31, c * 32, c * 31,
				lemin->rooms[i]->cur_ant);
	}
	ft_printf("\n\n");
}

int		in_path(t_data *lemin, int room)
{
	int i;

	i = -1;
	while (++i < lemin->roomcount)
		if (lemin->links[i][room] < -100)
			return (i);
	return (-1);
}

void	find_next(t_data *lemin, int prev, int cur)
{
	int i;

	if (cur == lemin->finish)
	{
		ft_printf("\x1b[%dm[\x1b[%dm%s\x1b[%dm]", lemin->colour * 31,
			lemin->colour * 33,
			lemin->rooms[cur]->name,
			lemin->colour * 31);
		return ;
	}
	i = -1;
	while (++i < lemin->roomcount)
		if (i != prev)
			if (lemin->links[i][cur] < -100)
			{
				ft_printf("\x1b[%dm[\x1b[%dm%s\x1b[%dm]\x1b[%dm->",
						lemin->colour * 31,
						lemin->colour * 33,
						lemin->rooms[cur]->name,
						lemin->colour * 31, lemin->colour * 32);
				find_next(lemin, cur, i);
			}
}

int		print_paths(t_data *lemin)
{
	int i;
	int room;

	if (!lemin->path_p)
		return (1);
	i = lemin->roomcount - 1;
	while (++i < lemin->roomcount + lemin->temprooms)
	{
		if ((room = in_path(lemin, i)) > -1)
		{
			ft_printf("\x1b[%dm[\x1b[%dm%s\x1b[%dm]\x1b[%dm->",
					lemin->colour * 31,
					lemin->colour * 33,
					lemin->rooms[lemin->start]->name,
					lemin->colour * 31, lemin->colour * 32);
			find_next(lemin, i, room);
		}
		ft_printf("\n");
	}
	return (1);
}
