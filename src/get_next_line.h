/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:06:49 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/21 22:15:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>

#define BUFF_SIZE		100
#define READ_LIST		stat->read
#define LAST_READ		((t_read *)stat->read->content)->str
#define LAST_READ_LEN	((t_read *)stat->read->content)->slen
#define LAST_READ_RET	((t_read *)stat->read->content)->r_return

typedef struct	s_status
{
	t_list		*read;
	size_t		slen;
}				t_status;

typedef struct	s_read
{
	char		str[BUFF_SIZE];
	size_t		slen;
	size_t		r_return;
}				t_read;

static t_status	*stat = NULL;

int				get_next_line(int fd, char **line);

#endif
