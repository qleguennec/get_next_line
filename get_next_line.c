/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/28 16:36:04 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int			linecpy
	(t_list **l, char **line, t_list **st, char *tmp)
{
	t_list			*s;

	s = st ? *st : NULL;
	if (!(list_concat(*l)))
		return (0);
	if (!(*line = ft_strnew((*l)->size)))
		return (0);
	ft_memcpy(*line, (*l)->data, (*l)->size);
	list_del(l);
	if (s && tmp)
	{
		s->size -= tmp + 1 - (char *)s->data;
		ft_memmove(s->data, tmp + 1, s->size);
		ft_bzero(s->data + s->size, BUFF_SIZE - s->size);
		s->next = NULL;
		if (!s->size)
			list_del(st);
	}
	return (1);
}

static int			do_read
	(t_list **st, int fd, char **line)
{
	t_list			*a;

	if (!(a = list_new(NULL, BUFF_SIZE)))
		return (-1);
	a->size = read(fd, a->data, BUFF_SIZE);
	if ((int)a->size < 0)
		return (-1);
	if (!a->size)
		return (st ? linecpy(st, line, NULL, NULL) : 0);
	list_add(st, a);
	return (gnl_byfd(st, fd, line));
}

int					gnl_byfd
	(t_list **st, int fd, char **line)
{
	char			*tmp;
	t_list			*a;

	if (!((*st) && (tmp = ft_memchr((*st)->data, SEP_CHAR, (*st)->size))))
		return (do_read(st, fd, line));
	if (tmp == (*st)->data && (*st)->next)
	{
		if (!(linecpy(&(*st)->next, line, NULL, NULL)))
			return (-1);
		if ((*st)->size-- > 1)
			ft_memmove((*st)->data, (*st)->data + 1, (*st)->size);
		if (!(*st)->size)
			list_del(st);
		return (1);
	}
	if (!(a = list_new((*st)->data, tmp - (char *)(*st)->data)))
		return (-1);
	a->next = (*st)->next;
	return (linecpy(&a, line, st, tmp) ? 1 : -1);
}

static void			list_del_fd
	(t_list *a, t_list *l)
{
	if (!l)
		return ;
	while (a && a->next != l)
		a = a->next;
	if (!a)
		return ;
	l = l->next;
	list_del_one(&a->next);
	a->next = l;
}

int					get_next_line
	(int fd, char **line)
{
	static t_list	*st_byfd = NULL;
	t_list			*l;
	int				gnl_ret;

	if (fd < 0 || !line)
		return (-1);
	l = st_byfd;
	while (l && l->size != (size_t)fd)
		l = l->next;
	if (!l)
	{
		if (!(l = ft_memalloc(sizeof(*st_byfd))))
			return (-1);
		l->size = (size_t)fd;
		list_add(&st_byfd, l);
	}
	gnl_ret = gnl_byfd((t_list **)&l->data, fd, line);
	if (gnl_ret <= 0)
	{
		*line = NULL;
		list_del_fd(st_byfd, l);
	}
	return (gnl_ret);
}
