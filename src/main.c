/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:06:02 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/21 21:46:59 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int			main
	(int argc, char **argv)
{
	size_t	i;
	int		fd;
	int		gnl_return;
	char	*line;

	i = 1;
	while (i < (size_t)argc)
	{
		fd = open(argv[i], 0, O_RDONLY);
		while ((gnl_return = get_next_line(fd, &line)) >= 0)
		{
			ft_putendl(line);
			free(line);
		}
		if (gnl_return < 0)
			return (- gnl_return);
	}
	return (0);
}
