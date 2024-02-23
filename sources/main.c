/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:19:35 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/23 17:51:18 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_childs(t_cmd *list)
{
	waitpid(list->next->pid, NULL, 0);
	waitpid(list->pid, NULL, 0);
}

void	open_files(t_files *fd, t_cmd *list, char **argv)
{
	fd->infile = open(argv[1], O_RDONLY);
	if (fd->infile == -1)
		perror(argv[1]);
	fd->outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd->outfile == -1)
		post_parser_exit(&list, fd->infile, fd->outfile, argv[4]);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*list;
	t_files	fd;

	if (argc != 5)
	{
		ft_putendl_fd("Error: there must be 4 arguments", 2);
		return (1);
	}
	list = create_cmds_list(argv + 2, envp);
	open_files(&fd, list, argv);
	exec_cmds(list, fd, envp);
	wait_childs(list);
	ft_cmdclear(&list, free_array);
	return (EXIT_SUCCESS);
}
