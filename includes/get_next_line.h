/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:06:49 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/07 17:42:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <libft.h>
# include <stdlib.h>
#include <stdio.h>

# define BUFF_SIZE 10
# define SEP_CHAR '\n'

int				get_next_line(int fd, char **line);

#endif
