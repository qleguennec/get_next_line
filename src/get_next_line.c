/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/05/26 22:36:36 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>

static int	do_read
	(int fd)
{
	t_list	*l;

	if (!(l = ft_lstnew(NULL, sizeof(t_read))))
		return (0);
	ft_lstadd(&RL, l);
	LR_RET = read(fd, LR, BUFF_SIZE);
	if (LR_RET < 0)
		return (0);
	LR_LEN = LR_RET;
	g_stat->slen += LR_LEN;
	return (1);
}

static int	copy
	(char **line)
{
	char	*buf;
	t_list	*l;

	if (!(*line = ft_strnew(g_stat->slen)))
		return (0);
	buf = *line + g_stat->slen - (g_stat->line_end - LR);
	ft_memcpy(buf, LR, g_stat->line_end - LR);
	l = RL;
	RL = RL->next;
	while (RL)
	{
		buf -= LR_LEN;
		ft_memcpy(buf, LR, LR_LEN);
		RL = RL->next;
	}
	RL = l;
	return (1);
}

static int	end
	(char **line, int ret)
{
	t_list	*l;

	if (!ret && RL && RL->next && ((t_read*)RL->next->content)->slen)
	{
		g_stat->slen = 0;
		l = RL;
		RL = RL->next;
		g_stat->line_end = LR + LR_LEN;
		while (RL)
		{
			g_stat->slen += LR_LEN;
			RL = RL->next;
		}
		RL = l->next;
		ret = copy(line) ? 1 : -1;
		if (ret == 1)
		{
			ft_lstdel(&RL, &ft_delete);
			return (1);
		}
	}
	*line = NULL;
	ft_lstdel(&RL, &ft_delete);
	ft_memdel((void**)&g_stat);
	return (ret);
}

int			get_next_line
	(int fd, char **line)
{
	if (BUFF_SIZE <= 0 || !line || fd < 0 || fd > 255)
		return (-1);
	if (!(g_stat || !(g_stat = ft_memalloc(sizeof(*g_stat)))
		|| (RL = ft_lstnew(NULL, sizeof(t_read)))))
		return (-1);
	if (!RL)
		return (end(line, 0));
	if (!g_stat->line_end || !(g_stat->line_end = ft_memchr(LR, SEP_CHAR, LR_LEN)))
	{
		if (!do_read(fd))
			return (end(line, -1));
		if (!LR_RET)
			return (end(line, 0));
		if (LR_LEN < BUFF_SIZE)
			g_stat->line_end = LR + LR_LEN;
		return (get_next_line(fd, line));
	}
	LR_LEN -= g_stat->line_end - LR + 1;
	g_stat->slen -= LR_LEN + 1;
	if (!copy(line))
		return (-1);
	g_stat->slen = LR_LEN;
	if (!g_stat->slen)
	{
		ft_lstdel(&RL, &ft_delete);
		return (1);
	}
	ft_memmove(LR, g_stat->line_end + 1, LR_LEN);
	ft_bzero(LR + LR_LEN, BUFF_SIZE - LR_LEN);
	ft_lstdel(&RL->next, &ft_delete);
	return (1);
}
