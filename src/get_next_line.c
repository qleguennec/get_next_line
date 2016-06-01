/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/01 03:14:08 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>

int			get_next_line(int fd, char **line)
{
	t_list	*l;
	char	buffer[BUFF_SIZE];
	char	*buf;
	char	*tmp;
	int		ret;

	if (g_stat)
	{
		tmp = ft_memchr(g_stat->content, SEP_CHAR, g_stat->content_size);
		ret = g_stat->content_size;
		printf("(%d)\n", ret);
		buf = g_stat->content;
	}
	if (!tmp)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		buf = buffer;
		if (!ret)
			return (0);
		tmp = ft_memchr(buf, SEP_CHAR, ret);
	}
	if (tmp)
	{
		l = ft_lstnew(buf, tmp - buf);
		ft_lstadd(&g_stat, l);
		ft_lstrevbuild(g_stat);
		*line = ft_strnew(g_stat->content_size);
		ft_memcpy(*line, g_stat->content, g_stat->content_size);
		ft_memdel((void **)&g_stat);
		g_stat = ft_lstnew(tmp + 1, (size_t)ret - (tmp + 1 - buf));
		return (1);
	}
	l = ft_lstnew(buf, ret);
	ft_lstadd(&g_stat, l);
	return (get_next_line(fd, line));
}
