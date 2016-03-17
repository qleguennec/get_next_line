/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:06:49 by qle-guen          #+#    #+#             */
/*   Updated: 2016/03/17 21:43:35 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1   10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1		7
#define READ_LIST		stat->read
#define LAST_READ		((t_read *)stat->read->content)->str
#define LAST_READ_LEN	((t_read *)stat->read->content)->slen
#define LAST_READ_RET	((t_read *)stat->read->content)->r_return

typedef struct	s_status
{
	t_list		*read;
	char		*line_end;
	size_t		slen;
}				t_status;

typedef struct	s_read
{
	char		str[BUFF_SIZE 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1   10000 1000 100 42 10 1 10000 1000 100 42 10 1 10000 1000 100 42 10 1];
	size_t		slen;
	int			r_return;
}				t_read;

static t_status	*stat = NULL;

int				get_next_line(int fd, char **line);

#endif
