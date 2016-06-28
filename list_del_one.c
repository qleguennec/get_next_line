/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:17:06 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/28 16:39:27 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "list.h"
#include <stdlib.h>

void		ft_listdelone
	(t_list **alist)
{
	free((*alist)->data);
	ft_memdel((void**)alist);
}
