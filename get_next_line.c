/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/03/21 00:32:54 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	do_read
	(int fd)
{
	t_list	*l;

	if (!(l = ft_lstnew(NULL, sizeof(t_read))))
		return (0);
	ft_lstadd(&READ_LIST, l);
	LAST_READ_RET = read(fd, LAST_READ, BUFF_SIZE);
	if (LAST_READ_RET < 0)
		return (0);
	LAST_READ_LEN = LAST_READ_RET;
	stat[fd]->slen += LAST_READ_LEN;
	return (1);
}

static int	copy
	(int fd, char **line)
{
	char	*buf;
	t_list	*l;

	if (!(*line = ft_strnew(stat[fd]->slen)))
		return (0);
	buf = *line + stat[fd]->slen - (stat[fd]->line_end - LAST_READ);
	ft_memcpy(buf, LAST_READ, stat[fd]->line_end - LAST_READ);
	l = READ_LIST;
	READ_LIST = READ_LIST->next;
	while (READ_LIST)
	{
		buf -= LAST_READ_LEN;
		ft_memcpy(buf, LAST_READ, LAST_READ_LEN);
		READ_LIST = READ_LIST->next;
	}
	READ_LIST = l;
	return (1);
}

static int	end
	(int fd, char **line, int ret)
{
	if (!ret && READ_LIST->next && ((t_read*)READ_LIST->next->content)->slen)
	{
		*line = ft_strdup((char*)READ_LIST->next->content);
		ft_lstdel(&READ_LIST->next, &ft_delete);
		READ_LIST->next = NULL;
		stat[fd]->slen = 0;
		return (1);
	}
	*line = NULL;
	ft_lstdel(&READ_LIST, &ft_delete);
	ft_memdel((void**)&stat[fd]);
	return (ret);
}

int			get_next_line
	(int fd, char **line)
{
	if (BUFF_SIZE <= 0 || !line || fd < 0 || fd > 255)
		return (-1);
	if (!(stat[fd] || !(stat[fd] = ft_memalloc(sizeof(*stat[fd])))
		|| (READ_LIST = ft_lstnew(NULL, sizeof(t_read)))))
		return (-1);
	if (!(stat[fd]->line_end = ft_memchr(LAST_READ, SEP_CHAR, LAST_READ_LEN)))
	{
		if (!do_read(fd))
			return (end(fd, line, -1));
		if (!LAST_READ_RET)
			return (end(fd, line, 0));
		return (get_next_line(fd, line));
	}
	LAST_READ_LEN -= stat[fd]->line_end - LAST_READ + 1;
	stat[fd]->slen -= LAST_READ_LEN + 1;
	if (!copy(fd, line))
		return (-1);
	stat[fd]->slen = LAST_READ_LEN;
	ft_memmove(LAST_READ, stat[fd]->line_end + 1, LAST_READ_LEN);
	ft_bzero(LAST_READ + LAST_READ_LEN, BUFF_SIZE - LAST_READ_LEN);
	ft_lstdel(&READ_LIST->next, &ft_delete);
	return (1);
}
