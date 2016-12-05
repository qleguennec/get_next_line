/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 08:40:07 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/05 12:35:39 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGNL_H
# define LIBGNL_H

# include "../libvect/libvect.h"

# ifndef GNL_BUFF_SIZE
#  define GNL_BUFF_SIZE 100
# endif

# ifndef GNL_SEP_CHAR
#  define GNL_SEP_CHAR '\n'
# endif

# define GNL_STR 1
# define GNL_LINES_COUNT 2
# define GNL_LINES_TOTAL 4

int		get_next_line(int fd, t_vect *v, t_vect *line, int opts);
size_t	gnl_lines(int fd, t_vect *lines, int opts);

#endif
