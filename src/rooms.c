/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:46:40 by iganich           #+#    #+#             */
/*   Updated: 2018/08/19 19:20:15 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

char	*custom_strchr(char *line)
{
	while (*line && *line != ' ')
		line++;
	return (line);
}

int		is_name_free(t_data *lemin, char *line)
{
	int		i;
	char	*temp;

	i = -1;
	temp = ft_strchr(line, ' ');
	if (temp)
	{
		while (++i < lemin->roomcount)
			if (!ft_strncmp(lemin->rooms[i]->name, line, temp - line)
					&& !lemin->rooms[i]->name[line - temp + 1])
				return (0);
	}
	else
		return (0);
	return (1);
}

int		tempfunc(char *valid, t_room *room, char **line)
{
	int i;

	if (!valid)
		return (-1);
	ft_copying(&(room->name), *line, ' ');
	valid = room->name;
	room->name = ft_strdup(room->name);
	custom_free((void*)&valid);
	*line = ft_strchr(*line, ' ');
	i = -1;
	while (++i < 2)
	{
		if (!(**line) || !is_nbr_str(*line + 1))
			return (-1);
		(*line)++;
		(room->coord)[i] = ft_atoi(*line);
		*line = custom_strchr(*line);
	}
	return (0);
}

t_room	*set_new_room(char *line, char *valid, t_data *lemin, int flag)
{
	t_room	*room;
	int		i;

	room = ft_memalloc(sizeof(t_room));
	if (!ft_strchr(line, '-') && (valid = ft_strchr(line, ' ')))
		valid = ft_strchr(valid, ' ');
	if (tempfunc(valid, room, &line) == -1)
		return (freeroom(room));
	if (!valid)
		return (freeroom(room));
	i = -1;
	while (++i < lemin->roomcount)
		if (flag == 0)
			if (!ft_memcmp(room->coord, lemin->rooms[i]->coord,
						sizeof(int) * 2))
				return (freeroom(room));
	if (*line)
		return (freeroom(room));
	room->realway = 2147483647;
	return (room);
}

int		set_room_info(t_data *lemin, int *s_e, char *line)
{
	t_room	**newmas;
	int		i;

	i = -1;
	if (!is_name_free(lemin, line))
		return (-1);
	if (s_e[1] == 1 && lemin->start == -1)
		lemin->start = lemin->roomcount;
	else if (lemin->start != -1 && s_e[1] == 1)
		return (-1);
	if (s_e[1] == 2 && lemin->finish == -1)
		lemin->finish = lemin->roomcount;
	else if (lemin->finish != -1 && s_e[1] == 2)
		return (-1);
	newmas = ft_memalloc(sizeof(t_room*) * (lemin->roomcount + 1));
	while (++i < lemin->roomcount)
		newmas[i] = (lemin->rooms)[i];
	newmas[i] = set_new_room(line, NULL, lemin, 0);
	free(lemin->rooms);
	lemin->rooms = newmas;
	(lemin->roomcount)++;
	if (!(newmas[i]))
		return (-1);
	ft_bzero(s_e, sizeof(int) * 2);
	return (0);
}
