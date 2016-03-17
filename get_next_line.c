/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/03/18 00:00:22 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			do_read
	(int fd)
{
	t_list	*l;

	if (!(l = ft_lstnew(ft_memalloc(sizeof(t_read*)), sizeof(t_read))))
		return (0);
	ft_lstadd(&READ_LIST, l);
	LAST_READ_RET = read(fd, LAST_READ, BUFF_SIZE);
	if (LAST_READ_RET < 0)
		return (0);
	LAST_READ_LEN = LAST_READ_RET;
	stat->slen += LAST_READ_LEN;
	return (1);
}

static int	copy
	(char **line)
{
	char	*buf;
	t_list	*l;

	if (!(*line = ft_strnew(stat->slen)))
		return (0);
	buf = *line + stat->slen - (stat->line_end - LAST_READ);
	ft_memcpy(buf, LAST_READ, stat->line_end - LAST_READ);
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
	(int ret, char **line)
{
	if (!ret && READ_LIST->next && ((t_read*)READ_LIST->next->content)->slen)
	{
		*line = ft_strdup((char*)READ_LIST->next->content);
		ft_lstdel(&READ_LIST->next, &ft_delete);
		READ_LIST->next = NULL;
		return (1);
	}
	else
		*line = NULL;
	ft_lstdel(&READ_LIST, &ft_delete);
	ft_memdel((void**)&stat);
	return (ret);
}

int			get_next_line
	(int fd, char **line)
{
	if (!line || fd < 0 || fd > 255)
		return (-1);
	if (!(stat || !(stat = ft_memalloc(sizeof(*stat)))
		|| (READ_LIST = ft_lstnew(NULL, sizeof(t_read)))))
		return (-1);
	if (!(stat->line_end = ft_memchr(LAST_READ, '\n', LAST_READ_LEN)))
	{
		if (!do_read(fd))
			return (end(-1, line));
		if (!LAST_READ_RET)
			return (end(0, line));
		return (get_next_line(fd, line));
	}
	LAST_READ_LEN -= stat->line_end - LAST_READ + 1;
	stat->slen -= LAST_READ_LEN + 1;
	if (!copy(line))
		return (-1);
	stat->slen = LAST_READ_LEN;
	ft_memmove(LAST_READ, stat->line_end + 1, LAST_READ_LEN);
	ft_bzero(LAST_READ + LAST_READ_LEN, BUFF_SIZE - LAST_READ_LEN);
	ft_lstdel(&READ_LIST->next, &ft_delete);
	return (1);
}
