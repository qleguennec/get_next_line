/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/03/04 18:23:19 by qle-guen         ###   ########.fr       */
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

void		debug_line
	(char *line, size_t len)
{
	while (len)
	{
		printf("\033[0;32;40m%c\033[0m", *line);
		line++;
		len--;
	}
	ft_putchar('|');
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putchar('\n');
}

int			get_next_line
	(int fd, char **line)
{
	char	*buf;
	t_list	*l;

	if (fd < 0 || fd > 255)
		return (-1);
	if (!(stat || !(stat = ft_memalloc(sizeof(*stat)))
		|| (READ_LIST = ft_lstnew(NULL, sizeof(t_read)))))
		return (-1);
	if (!(stat->line_end = ft_memchr(LAST_READ, '\n', LAST_READ_LEN)))
		return (do_read(fd)) ? get_next_line(fd, line) : -1;
	debug_line(LAST_READ, LAST_READ_LEN);
	stat->slen -= LAST_READ_LEN - (stat->line_end - LAST_READ);
	*line = ft_strnew(stat->slen);
	buf = *line + stat->slen - (stat->line_end - LAST_READ);
	ft_memcpy(buf, LAST_READ, stat->line_end - LAST_READ);
	LAST_READ_LEN -= stat->line_end - LAST_READ;
	ft_memmove(LAST_READ, stat->line_end + 1, LAST_READ_LEN);
	ft_bzero(LAST_READ + LAST_READ_LEN, BUFF_SIZE - LAST_READ_LEN);
	l = READ_LIST;
	stat->slen -= stat->line_end - LAST_READ;
	while (stat->slen)
	{
		READ_LIST = READ_LIST->next;
		stat->slen -= LAST_READ_LEN;
		ft_memcpy(*line + stat->slen, LAST_READ, LAST_READ_LEN);
	}
	READ_LIST = l;
	stat->slen = LAST_READ_LEN;
	ft_lstdel(&READ_LIST->next, &ft_delete);
	stat->line_end = NULL;
	return (LAST_READ_RET ? 1 : 0);
}
