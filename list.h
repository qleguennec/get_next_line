/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:17:47 by qle-guen          #+#    #+#             */
/*   Updated: 2016/06/28 16:38:31 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

#include <string.h>

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
	size_t			size;
}					t_list;

void				list_del_one(t_list **alst);
void				list_del(t_list **alst);
void				list_add(t_list **alst, t_list *new);
t_list				*list_new(void const *data, size_t size);
int					list_concat(t_list *alst);

#endif
