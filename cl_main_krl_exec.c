/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:07:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/26 13:48:31 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_client.h"

static void
	cpy_kernel_args
	(t_cl *cl)
{
	CL_KRL_ARG(cl->main_krl.krl, 2, cl->objs);
	CL_KRL_ARG(cl->main_krl.krl, 3, cl->lgts);
	CL_KRL_ARG(cl->main_krl.krl, 4, cl->n_objs);
	CL_KRL_ARG(cl->main_krl.krl, 5, cl->n_lgts);
}

bool
	cl_main_krl_exec
	(t_cl *cl)
{
	int				ret;
	static size_t	work_size[2] = {REND_W, REND_H};

	cpy_kernel_args(cl);
	if ((ret = cl_krl_exec(&cl->info, cl->main_krl.krl, 2, work_size))
		!= CL_SUCCESS)
		return (ERR("cannot exec kernel, err %a\n", false, ret));
	return (true);
}
