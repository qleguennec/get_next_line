/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:05:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/01 01:44:37 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>

static int	do_read
	(int fd)
{
	t_list	*l;
	t_read	r;

	r.r_return = read(fd, r.str, BUFF_SIZE);
	if (r.r_return < 0)
		return (-1);
	if (!r.r_return)
	{
		g_stat->line_end = LR + LR_LEN;
		return (0);
	}
	if (!(l = ft_lstnew(&r, sizeof(r))))
		return (-1);
	ft_lstadd(&RL, l);
	LR_LEN = LR_RET;
	g_stat->line_end = ft_memchr(LR, SEP_CHAR, LR_LEN);
	if (!g_stat->line_end && LR_LEN < BUFF_SIZE)
		LR[LR_LEN++] = SEP_CHAR;
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
	ft_lstdel(&RL, &ft_delete);
	if (ret != 1)
	{
		*line = NULL;
		ft_memdel((void **)&g_stat);
	}
	return (ret);
}

int			get_next_line
	(int fd, char **line)
{
	int		r_ret;

	if (BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!g_stat && !(g_stat = ft_memalloc(sizeof(*g_stat))))
		return (-1);
	if (g_stat->end)
		return (end(line, 0));
	if (!RL && !(RL = ft_lstnew(NULL, sizeof(t_read))))
		return (-1);
	g_stat->line_end = ft_memchr(LR, SEP_CHAR, LR_LEN);
	if (!g_stat->line_end)
		r_ret = do_read(fd);
	if (r_ret == -1)
		return (-1);
	if (!r_ret)
		g_stat->end = 1;
	if (!g_stat->line_end)
		return (get_next_line(fd, line));
	LR_LEN -= g_stat->line_end - LR + 1;
	g_stat->slen -= LR_LEN + 1;
	if (!copy(line))
		return (end(line, -1));
	g_stat->slen = LR_LEN;
	ft_memmove(LR, g_stat->line_end + 1, LR_LEN);
	ft_bzero(LR + LR_LEN, BUFF_SIZE - LR_LEN);
	ft_lstdel(&RL->next, &ft_delete);
	return (1);
}
