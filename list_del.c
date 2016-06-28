/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:28:15 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/28 16:38:42 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void		list_del
	(t_list **alist)
{
	t_list	*buf;

	if (*alist)
	{
		buf = (*alist)->next;
		list_del_one(alist);
		list_del(&buf);
	}
}
