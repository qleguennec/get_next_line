/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/07 22:15:20 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>

static int			linecpy
	(t_list **l, char **line, t_list **st, char *tmp)
{
	t_list			*s;

	s = st ? *st : NULL;
	if (!(ft_lstrevbuild(*l)))
		return (0);
	if (!(*line = ft_strnew((*l)->content_size)))
		return (0);
	ft_memcpy(*line, (*l)->content, (*l)->content_size);
	ft_lstdel(l, &ft_delete);
	if (s && tmp)
	{
		s->content_size -= tmp + 1 - (char *)s->content;
		ft_memmove(s->content, tmp + 1, s->content_size);
		ft_bzero(s->content + s->content_size, BUFF_SIZE - s->content_size);
		s->next = NULL;
		if (!s->content_size)
			ft_lstdel(st, &ft_delete);
	}
	return (1);
}

static int			do_read
	(t_list **st, int fd, char **line)
{
	t_list			*a;

	if (!(a = ft_lstnew(NULL, BUFF_SIZE)))
		return (-1);
	a->content_size = read(fd, a->content, BUFF_SIZE);
	if ((int)a->content_size < 0)
		return (-1);
	if (!a->content_size)
		return (st ? linecpy(st, line, NULL, NULL) : 0);
	ft_lstadd(st, a);
	return (gnl_byfd(st, fd, line));
}

int					gnl_byfd
	(t_list **st, int fd, char **line)
{
	char			*tmp;
	t_list			*a;

	if ((*st) &&
		(tmp = ft_memchr((*st)->content, SEP_CHAR, (*st)->content_size)))
	{
		if (tmp == (*st)->content && (*st)->next)
		{
			if (!(linecpy(&(*st)->next, line, NULL, NULL)))
				return (-1);
			if ((*st)->content_size-- > 1)
				ft_memmove((*st)->content,
					(*st)->content + 1, (*st)->content_size);
			if (!(*st)->content_size)
				ft_lstdel(st, &ft_delete);
			return (1);
		}
		if (!(a = ft_lstnew((*st)->content, tmp - (char *)(*st)->content)))
			return (-1);
		a->next = (*st)->next;
		return (linecpy(&a, line, st, tmp) ? 1 : -1);
	}
	return (do_read(st, fd, line));
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
	while (l && l->content_size != (size_t)fd)
		l = l->next;
	if (!l)
	{
		if (!(l = ft_memalloc(sizeof(*st_byfd))))
			return (-1);
		l->content_size = (size_t)fd;
		ft_lstadd(&st_byfd, l);
	}
	gnl_ret = gnl_byfd((t_list **)&l->content, fd, line);
	return (gnl_ret);
}
