/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:47:54 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/05 16:18:26 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"
#include "../libft/libft.h"

size_t	gnl_lines(int fd, t_vect *lines, int opts)
{
	int		ret;
	size_t	count;
	t_vect	buf;
	t_vect	line;

	BZERO(buf);
	BZERO(line);
	count = 0;
	while ((ret = get_next_line(fd, &buf, &line, opts | GNL_STR)) > 0)
	{
		if (GNL_LINES_COUNT & opts)
			count++;
		if (GNL_LINES_TOTAL & opts)
			count += line.used + !!(opts & GNL_STR);
		vect_add(lines, &line.data, sizeof(line.data));
		BZERO(line);
	}
	if (ret < 0)
		return (ret);
	return (count);
}
