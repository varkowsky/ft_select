/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 17:20:27 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/09 18:50:23 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_select.h"

t_lst	*eb_new_elt(char *str)
{
	t_lst		*new;

	new = (t_lst *)malloc(sizeof(*new));
	new->str = ft_strdup(str);
	new->select = 0;
	new->prev = new;
	new->next = new;
	return (new);
}

void	eb_add_list_last(t_lst **list, t_lst *new)
{
	if ((*list)->next == *list)
	{
		(*list)->next = new;
		(*list)->prev = new;
		new->next = *list;
		new->prev = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = *list;
		((*list)->prev)->next = new;
		(*list)->prev = new;
	}
}

void	eb_add_list_first(t_lst **list, t_lst *new)
{
	if ((*list)->next == *list)
	{
		(*list)->next = new;
		(*list)->prev = new;
		new->next = *list;
		new->prev = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = *list;
		((*list)->prev)->next = new;
		(*list)->prev = new;
	}
	*list = new;
}

int		eb_del_elt(t_lst **list, t_lst *elt, t_data *d)
{
	if (*list == NULL)
		return (0);
	if (elt->next == elt)
	{
		if (*list == elt)
			*list = NULL;
		free(elt);
		d->nb_elt--;
		return (0);
	}
	else
	{
		if (*list == elt)
			*list = elt->next;
		elt->prev->next = elt->next;
		elt->next->prev = elt->prev;
		free(elt);
		d->nb_elt--;
		return (1);
	}
}

t_lst	**get_lst(char **av, t_data *d)
{
	t_lst			**list;
	t_lst			*tmp;
	int				len;

	list = (t_lst **)malloc(sizeof(t_lst *));
	d->len = (int)ft_strlen(*av);
	tmp = eb_new_elt(*av);
	d->nb_elt = 1;
	*list = tmp;
	av++;
	while (*av != '\0')
	{
		d->len = (d->len < (len = (int)ft_strlen(*av))) ? len : d->len;
		tmp = eb_new_elt(*av);
		eb_add_list_last(list, tmp);
		d->nb_elt++;
		av++;
	}
	return (list);
}
