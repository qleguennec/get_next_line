/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:49:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/26 16:47:46 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_client.h"

#define CMD(cmd, buf, n) (n == sizeof(cmd) - 1 && ft_memcmp(cmd, buf, n) == 0)

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
	client_loop
	(int sockfd
	, t_vect *data
	, t_cl *cl)
{
	char	cmdbuf[10];
	int		nbytes;

	if ((nbytes = recv(sockfd, cmdbuf, sizeof(cmdbuf), 0)) <= 0)
		return ;
	data->used = 0;
	vect_req(data, nbytes);
	recv(sockfd, data->data, data->used, 0);
	if (CMD("cam", cmdbuf, nbytes))
		update_camera(data, cl);
	if (CMD("lgts", cmdbuf, nbytes))
	{
		update_buffer(data, &cl->lgts, nbytes / sizeof(t_cl_lgt), cl);
		cl->n_lgts = nbytes / sizeof(t_cl_lgt);
		printf("%d\n", cl->n_lgts);
	}
	if (CMD("objs", cmdbuf, nbytes))
	{
		update_buffer(data, &cl->objs, nbytes / sizeof(t_cl_obj), cl);
		cl->n_objs = nbytes / sizeof(t_cl_obj);
	}
	if (CMD("render", cmdbuf, nbytes))
		cl_main_krl_exec(cl);
	client_loop(sockfd, data, cl);
}
