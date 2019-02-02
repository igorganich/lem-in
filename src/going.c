/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   going.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:07:51 by iganich           #+#    #+#             */
/*   Updated: 2018/09/30 14:29:53 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	go_ant(t_data *lemin, int src, int dst)
{
	if (src >= lemin->roomcount)
	{
		lemin->started++;
		ft_printf("\x1b[%dmL\x1b[%dm%d\x1b[%dm-\x1b[%dm%s ",
				lemin->colour * 34, lemin->colour * 31,
				lemin->started, lemin->colour * 32,
				lemin->colour * 33, lemin->rooms[dst]->name);
		lemin->rooms[src]->steps--;
	}
	else
		ft_printf("\x1b[%dmL\x1b[%dm%d\x1b[%dm-\x1b[%dm%s ",
				lemin->colour * 34, lemin->colour * 31,
				lemin->rooms[src]->cur_ant, lemin->colour * 32,
				lemin->colour * 33, lemin->rooms[dst]->name);
	lemin->rooms[dst]->cur_ant = lemin->rooms[src]->cur_ant;
	if (src >= lemin->roomcount)
		lemin->rooms[dst]->cur_ant = lemin->started;
	lemin->rooms[src]->cur_ant = 0;
	if (dst == lemin->finish)
	{
		lemin->finished++;
		lemin->rooms[dst]->cur_ant = 0;
	}
}

void	advance_branch(t_data *lemin, int prevroom, int room, int flag)
{
	int l;
	int nextroom;

	l = -1;
	while (++l < lemin->roomcount && room != lemin->finish)
		if (lemin->links[l][room] == lemin->links[room][prevroom]
				&& l != prevroom)
		{
			nextroom = l;
			break ;
		}
	if (lemin->rooms[room]->cur_ant)
	{
		advance_branch(lemin, room, nextroom, 1);
		if (flag == 1)
			go_ant(lemin, prevroom, room);
	}
	else if (flag == 0 && room != lemin->finish)
		advance_branch(lemin, room, nextroom, flag);
	else if (flag == 1)
		go_ant(lemin, prevroom, room);
}

void	one_step(t_data *lemin)
{
	int i;
	int nextroom;
	int l;

	ft_printf("\n");
	print_status(lemin);
	i = lemin->roomcount - 1;
	while (++i < lemin->roomcount + lemin->temprooms)
	{
		l = -1;
		while (++l < lemin->roomcount)
			if (lemin->links[i][l] == i * (-1) - 100)
			{
				nextroom = l;
				advance_branch(lemin, i, nextroom, lemin->rooms[i]->steps > 0);
				break ;
			}
	}
}

int		go_all_ants(t_data *lemin, int *steps, int allsteps, int *best)
{
	int i;
	int l;
	int z;
	int flag;

	steps[best[1]] = allsteps - best[0] + 1;
	flag = 0;
	while (!flag && (i = -1))
	{
		flag = 1;
		while (++i < lemin->roomcount && (l = -1))
			while (++l < lemin->roomcount + lemin->temprooms)
				if (lemin->links[i][l] < -100 && (z = -1) && l != lemin->finish)
					while (++z < lemin->roomcount)
						if (lemin->links[z][i] == 1 && !(flag = 0))
							lemin->links[z][i] = lemin->links[i][l];
	}
	print_paths(lemin);
	i = lemin->roomcount - 1;
	while (++i < lemin->roomcount + lemin->temprooms)
		lemin->rooms[i]->steps = steps[i];
	while (lemin->finished != lemin->ants)
		one_step(lemin);
	free(steps);
	return (1);
}

int		try_ants(t_data *lemin, int size, int allsteps, int flag)
{
	int b[2];
	int *steps;
	int i;

	steps = ft_memalloc(sizeof(int) * (lemin->roomcount + lemin->temprooms));
	i = lemin->roomcount - 1;
	b[0] = 2147483647;
	b[1] = lemin->roomcount;
	while (++i < lemin->roomcount + lemin->temprooms)
		if (lemin->rooms[i]->realway < b[0] && (b[1] = i))
			if ((b[0] = lemin->rooms[i]->realway))
				flag = 0;
	allsteps = b[0] + lemin->ants - 1;
	while (!flag && (i = lemin->roomcount - 1))
		if ((flag = 1))
			while (++i < lemin->roomcount + lemin->temprooms)
				if (lemin->rooms[i]->realway < 2147483647)
					if (i != b[1] && lemin->rooms[i]->realway
							+ steps[i] <= allsteps)
						++steps[i] && allsteps-- > -228 ? flag = 0 : 0;
	if (allsteps > 0 && allsteps <= size)
		return (go_all_ants(lemin, steps, allsteps, b));
	free(steps);
	return (0);
}
