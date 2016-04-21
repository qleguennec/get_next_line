/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:06:49 by qle-guen          #+#    #+#             */
/*   Updated: 2016/04/21 14:15:24 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <libft.h>
# include <stdlib.h>

# define BUFF_SIZE	10
# define SEP_CHAR	'\n'
# define RL			g_stat[fd]->read
# define LR			((t_read *)g_stat[fd]->read->content)->str
# define LR_LEN		((t_read *)g_stat[fd]->read->content)->slen
# define LR_RET		((t_read *)g_stat[fd]->read->content)->r_return

typedef struct	s_status
{
	t_list		*read;
	char		*line_end;
	size_t		slen;
}				t_status;

typedef struct	s_read
{
	char		str[BUFF_SIZE];
	size_t		slen;
	int			r_return;
}				t_read;

static t_status	*g_stat[256] = {NULL};

int				get_next_line(int fd, char **line);

#endif
