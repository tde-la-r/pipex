/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:13:53 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/23 17:50:03 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	parser_exit(char **paths, char **args, t_cmd **list, char *err)
{
	free_array(args);
	ft_cmdclear(list, free_array);
	free_array(paths);
	if (!ft_strncmp(err, ERR_MALLOC, 7))
		perror(ERR_MALLOC);
	else
		ft_putendl_fd(err, 2);
	exit (EXIT_FAILURE);
}

void	post_parser_exit(t_cmd **list, int infile, int outfile, char *err)
{
	if (ft_strncmp(ERR_DUP, err, 5) || errno != EBADF)
		perror(err);
	close_fds(*list, infile, outfile);
	ft_cmdclear(list, free_array);
	exit (EXIT_FAILURE);
}

void	close_fds(t_cmd *list, int infile, int outfile)
{
	while (list)
	{
		if (list->fd_stdin > -1)
			close(list->fd_stdin);
		if (list->fd_stdout > -1)
			close(list->fd_stdout);
		list = list->next;
	}
	if (infile > -1)
		close(infile);
	if (outfile > -1)
		close(outfile);
}
