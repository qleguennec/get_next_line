/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 15:06:08 by qle-guen          #+#    #+#             */
/*   Updated: 2016/07/08 06:16:28 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "libgnl.h"
#include <unistd.h>

static int	cpy
	(t_vect *v, t_vect *line)
{
	void	*buf;

	if ((buf = ft_memchr(v->data, '\n', v->used)))
	{
		if (!vect_add(line, v->data, buf - v->data))
			return (-1);
		ft_memmove(v->data, buf + 1, v->used - (buf + 1 - v->data));
		v->used -= buf + 1 - v->data;
		return (1);
	}
	return (0);
}

int			get_next_line
	(int fd, t_vect *v, t_vect *line)
{
	int		ret;

	if (v->data && (ret = cpy(v, line)))
		return (ret);
	if (!vect_req(v, BUFF_SIZE)
		|| (ret = read(fd, v->data + v->used, BUFF_SIZE)) < 0)
		return (-1);
	if (!ret)
	{
		if (!v->used)
			return (0);
		if (!vect_add(line, v->data, v->used))
			return (-1);
		v->used = 0;
		return (1);
	}
	v->used += ret;
	return (get_next_line(fd, v, line));
}
