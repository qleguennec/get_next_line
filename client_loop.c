/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:49:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/27 17:10:49 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_client.h"

static void
	update_camera
	(t_vect *data
	, t_cl *cl)
{
	int		ret;

	if ((ret = cl_write(&cl->info, cl->main_krl.args[1]
		, sizeof(t_cl_cam), data->data)) != CL_SUCCESS)
		ERR("cannot update camera, cl err %a", 0, ret);
}

static void
	update_buffer
	(t_vect *data
	, cl_mem *mem
	, short n
	, t_cl *cl)
{
	int		ret;

	clReleaseMemObject(*mem);
	if (n == 0)
		return ;
	*mem = clCreateBuffer(cl->info.ctxt, 0, data->used, NULL, &ret);
	if (ret != CL_SUCCESS)
		ERR("clCreateBuffer error %a", 0, ret);
	else if ((ret = cl_write(&cl->info, *mem, data->used, data->data)
		!= CL_SUCCESS))
		ERR("cl_write error %a", 0, ret);
}

void
	process_command
	(char *cmdbuf
	, t_vect *data
	, t_cl *cl)
{
	if (ft_strcmp("cam", cmdbuf) == 0)
		update_camera(data, cl);
	if (ft_strcmp("lgts", cmdbuf) == 0)
	{
		printf("lgts\n");
		update_buffer(data, &cl->lgts, data->used / sizeof(t_cl_lgt), cl);
		cl->n_lgts = data->used / sizeof(t_cl_lgt);
	}
	if (ft_strcmp("objs", cmdbuf) == 0)
	{
		printf("objs\n");
		update_buffer(data, &cl->objs, data->used / sizeof(t_cl_obj), cl);
		cl->n_objs = data->used / sizeof(t_cl_obj);
	}
	if (ft_strcmp("render", cmdbuf) == 0)
		cl_main_krl_exec(cl);
}

void
	client_loop
	(int sockfd
	, t_vect *data
	, t_cl *cl)
{
	char	cmdbuf[10];
	int		ret;
	size_t	data_size;

	if ((ret = recv(sockfd, cmdbuf, sizeof(cmdbuf), 0)) <= 0)
		return ;
	cmdbuf[ret] = '\0';
	data->used = 0;
	if ((ret = recv(sockfd, &data_size, 8, 0)) <= 0)
		return ;
	if (data_size)
	{
		vect_req(data, data_size);
		recv(sockfd, data->data, data_size, 0);
	}
	process_command(cmdbuf, data, cl);
	client_loop(sockfd, data, cl);
}
