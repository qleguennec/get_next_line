/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/07 18:03:12 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int			get_next_line(int fd, char **line)
{
	static t_list	*stat = NULL;
	char	*tmp;
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	if (stat && (tmp = ft_memchr(stat->content, SEP_CHAR, stat->content_size)))
	{
		if (tmp == stat->content && stat->next)
		{
			ft_lstrevbuild(stat->next);
			*line = ft_strnew(stat->next->content_size);
			ft_memcpy(*line, stat->next->content, stat->next->content_size);
			if (stat->content_size-- > 1)
				ft_memmove(stat->content, stat->content + 1, stat->content_size);
			ft_lstdel(&stat->next, &ft_delete);
			if (!stat->content_size)
				ft_lstdel(&stat, &ft_delete);
			return (1);
		}
		a = ft_lstnew(stat->content, tmp - (char *)stat->content);
		a->next = stat->next;
		ft_lstrevbuild(a);
		*line = ft_strnew(a->content_size);
		ft_memcpy(*line, a->content, a->content_size);
		a->content_size = stat->content_size - (tmp + 1 - (char *)stat->content);
		ft_memmove(stat->content, tmp + 1, a->content_size);
		ft_bzero(stat->content + a->content_size, stat->content_size - a->content_size);
		stat->content_size = a->content_size;
		stat->next = NULL;
		ft_lstdel(&a, &ft_delete);
		if (!stat->content_size)
			ft_lstdel(&stat, &ft_delete);
		return (1);
	}
	b = ft_lstnew(NULL, BUFF_SIZE);
	b->content_size = read(fd, b->content, BUFF_SIZE);
	if ((int)b->content_size < 0)
		return (-1);
	if (!b->content_size)
	{
		if (!stat)
			return (0);
		ft_lstrevbuild(stat);
		*line = ft_strnew(stat->content_size);
		ft_memcpy(*line, stat->content, stat->content_size);
		ft_lstdel(&stat, &ft_delete);
		return (1);
	}
	ft_lstadd(&stat, b);
	return (get_next_line(fd, line));
}
