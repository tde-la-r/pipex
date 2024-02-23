/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:50:47 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/23 17:31:07 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_cmddelone(t_cmd *lst, void (*del)(char **))
{
	if (!lst || !del)
		return ;
	del(lst->args);
	free(lst);
}

void	ft_cmdclear(t_cmd **lst, void (*del)(char **))
{
	if (!del || !lst)
		return ;
	if (!*lst)
		return ;
	if ((*lst)->next)
		ft_cmdclear(&(*lst)->next, del);
	ft_cmddelone(*lst, del);
	*lst = NULL;
}

t_cmd	*ft_cmdnew(char **args)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = args;
	new_node->pid = 0;
	new_node->fd_stdin = -1;
	new_node->fd_stdout = -1;
	new_node->next = NULL;
	return (new_node);
}

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	if (!lst->next)
		return (lst);
	return (ft_cmdlast(lst->next));
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_cmdlast(*lst)->next = new;
}
