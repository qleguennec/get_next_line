/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:49:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/22 13:27:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_client.h"

#define CMD(cmd, buf, n) (n == sizeof(cmd) - 1 && ft_memcmp(cmd, buf, n) == 0)

static int
	recv_data
	(int sockfd
	, void **data_addr
	, size_t *data_size)
{
	int	ack;

	recv(sockfd, data_size, 8, 0);
	*data_addr = malloc(*data_size);
	if (*data_addr == NULL)
	{
		ack = 0;
		send(sockfd, &ack, 4, 0);
		return (0);
	}
	recv(sockfd, *data_addr, *data_size, 0);
	return (1);
}

void
	client_loop
	(int sockfd)
{
	char	cmdbuf[10];
	int		nbytes;
	void	*data;
	size_t	i;
	size_t	data_size;

	data = NULL;
	if ((nbytes = recv(sockfd, cmdbuf, sizeof(cmdbuf), 0)) <= 0)
		return ;
	if (CMD("cam", cmdbuf, nbytes))
	{
		if (!recv_data(sockfd, &data, &data_size))
			return ;
	}
	i = 1;
	send(sockfd, &i, 4, 0);
	free(data);
	client_loop(sockfd);
}
