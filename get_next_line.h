/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:06:49 by qle-guen          #+#    #+#             */
/*   Updated: 2016/03/19 00:13:39 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1
#define SEP_CHAR		'\n'
#define READ_LIST		stat[fd]->read
#define LAST_READ		((t_read *)stat[fd]->read->content)->str
#define LAST_READ_LEN	((t_read *)stat[fd]->read->content)->slen
#define LAST_READ_RET	((t_read *)stat[fd]->read->content)->r_return

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

static t_status	*stat[256] = {NULL};

int				get_next_line(int fd, char **line);

#endif
