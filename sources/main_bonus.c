/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:19:35 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/23 20:24:12 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_childs(t_cmd *list)
{
	if (list->next)
		wait_childs(list->next);
	waitpid(list->pid, NULL, 0);
}

void	read_here_document(char *limiter, int limiter_len, int fd_infile)
{
	char	*line;

	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, limiter_len + 1) && line)
	{
		ft_putstr_fd(line, fd_infile);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	close (fd_infile);
	if (!line)
		ft_putendl_fd(ERR_HERE_DOC, STDERR_FILENO);
	else
		free(line);
}

int	create_here_document(char *to_format, t_cmd *list)
{
	char	*limiter;
	int		limiter_len;
	int		fd_infile;

	fd_infile = open(TMP_FILE, O_WRONLY | O_CREAT, 0644);
	if (fd_infile == -1)
		post_parser_exit(&list, -1, -1, TMP_FILE);
	limiter = ft_strjoin(to_format, "\n");
	if (!limiter)
		post_parser_exit(&list, fd_infile, -1, ERR_MALLOC);
	limiter_len = ft_strlen(limiter);
	read_here_document(limiter, limiter_len, fd_infile);
	free(limiter);
	fd_infile = open(TMP_FILE, O_RDONLY);
	if (fd_infile == -1)
		perror(TMP_FILE);
	return (fd_infile);
}

t_cmd	*parse_pipex(int argc, char **argv, char **envp, t_files *fd)
{
	t_cmd	*list;

	if (ft_strncmp("here_doc", argv[1], 9))
	{
		list = create_cmds_list(argv + 2, envp);
		fd->infile = open(argv[1], O_RDONLY);
		if (fd->infile == -1)
			perror(argv[1]);
		fd->outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd->outfile == -1)
			post_parser_exit(&list, fd->infile, fd->outfile, argv[argc - 1]);
	}
	else
	{
		list = create_cmds_list(argv + 3, envp);
		fd->infile = create_here_document(argv[2], list);
		fd->outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd->outfile == -1)
			post_parser_exit(&list, fd->infile, fd->outfile, argv[argc - 1]);
	}
	return (list);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*list;
	t_files	fd;

	if (argc < 5)
	{
		ft_putendl_fd("Error: there must be at least 4 arguments", 2);
		return (EXIT_FAILURE);
	}
	list = parse_pipex(argc, argv, envp, &fd);
	exec_cmds(list, fd, envp);
	wait_childs(list);
	ft_cmdclear(&list, free_array);
	delete_here_document();
	return (EXIT_SUCCESS);
}
