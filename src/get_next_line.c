/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/21 22:21:42 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			do_read
	(int fd, char **line)
{
	t_list	*l;

	if (!(l = ft_lstnew(ft_memalloc(sizeof(s_read*)), sizeof(s_read))))
		return (0);
	ft_lstadd
	LAST_READ_RET = read(fd, LAST_READ, BUFF_SIZE);
	if (LAST_READ_RET <= 0)
		return (0);
	LAST_READ_LEN = LAST_READ_RET;
	stat->slen += LAST_READ_LEN;
	return (get_next_line(fd, line));
}

int			get_next_line
	(int fd, char **line)
{
	char	*buf;

	if (!(stat || !(stat = malloc(sizeof(*stat)))
		|| (READ_LIST = ft_lstnew(ft_memalloc(sizeof(s_read*)), sizeof(s_read)))))
		return (-1);
	if (fd < 0 || fd > 255)
		return (-1);
	if (!(buf = ft_memchr(LAST_READ, '\n', LAST_READ_LEN)))
		do_read();
	stat->slen -= buf - LAST_READ;
	*line = malloc(stat->slen);
	while (stat->slen)
	{
		
	}
	return (0);
}
