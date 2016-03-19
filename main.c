/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 21:06:02 by qle-guen          #+#    #+#             */
/*   Updated: 2016/03/19 16:19:43 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			main
	(int argc, char **argv)
{
	size_t	i;
	int		fd;
	int		gnl_return;
	char	*line;

	i = 2;
	line = NULL;
	if (argc < 3)
	{
		ft_putendl("usage: gnl-test function file1 file2 ... fileN");
		return (1);
	}
	if (ft_strequ(argv[1], "debug"))
	{
		while (i < (size_t)argc)
		{
			fd = open(argv[i], 0, 0);
			printf("debug\topen %s on fd %d\n", argv[i], fd);
			while (1)
			{
				gnl_return = get_next_line(fd, &line);
				if (line)
				{
					ft_putstr("debug\t");
					ft_putnbr(gnl_return);
					ft_putchar('\t');
					ft_putendl(line);
				}
				else
				{
					ft_putstr("debug\t");
					ft_putendl("line is set to NULL");
				}
				if (gnl_return <= 0)
				{
					ft_putstr("debug\tgnl exited with ");
					ft_putnbr(gnl_return);
					ft_putendl("");
					break ;
				}
			}
			i++;
			if (i < (size_t)argc)
				ft_putendl("debug\t");
		}
	}
	else if (ft_strequ(argv[1], "cat"))
	{
		while (i < (size_t)argc)
		{
			fd = open(argv[i], 0, 0);
			while (1)
			{
				gnl_return = get_next_line(fd, &line);
				if (gnl_return <= 0)
					break ;
				ft_putendl(line);
			}
			i++;
		}
	}
	else if (ft_strequ(argv[1], "cat-leaks"))
	{
		while (i < (size_t)argc)
		{
			fd = open(argv[i], 0, 0);
			while (1)
			{
				gnl_return = get_next_line(fd, &line);
				if (gnl_return <= 0)
					break ;
				else
					ft_putendl(line);
				free(line);
			}
			i++;
		}
		while (1)
			;
	}
	else if (ft_strequ(argv[1], "silent"))
	{
		fd = open(argv[i], 0, 0);
		while (get_next_line(fd, &line) > 0)
			free(line);
		free(line);
	}
	else
	{
		ft_putendl("function can be either <cat> or <debug> or <silent> or <cat-leaks>");
		return (2);
	}
	return (0);
}
