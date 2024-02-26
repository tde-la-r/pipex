/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:21:17 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/26 15:43:05 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execve_error(t_cmd *to_exec, t_cmd *list, t_files fd)
{
	char	*err_msg;

	if (errno != ENOENT)
		post_parser_exit(&list, fd.infile, fd.outfile, ERR_EXECVE);
	err_msg = ft_strjoin(to_exec->args[0], ": command not found");
	ft_putendl_fd(err_msg, STDERR_FILENO);
	if (err_msg)
		free(err_msg);
	close_fds(list, fd.infile, fd.outfile);
	ft_cmdclear(&list, free_array);
	exit (EXIT_FAILURE);
}

void	exec_child(t_cmd *to_exec, char **envp, t_cmd *list, t_files fd)
{
	to_exec->pid = fork();
	if (to_exec->pid < 0)
		post_parser_exit(&list, fd.infile, fd.outfile, ERR_FORK);
	if (!to_exec->pid)
	{
		if (dup2(to_exec->fd_stdin, STDIN_FILENO) == -1)
			post_parser_exit(&list, fd.infile, fd.outfile, ERR_DUP);
		if (dup2(to_exec->fd_stdout, STDOUT_FILENO) == -1)
			post_parser_exit(&list, fd.infile, fd.outfile, ERR_DUP);
		close_fds(list, fd.infile, fd.outfile);
		execve(to_exec->args[0], to_exec->args, envp);
		execve_error(to_exec, list, fd);
	}
}

void	init_child_fds(t_cmd *to_exec, t_files fd, t_cmd *list)
{
	int	fd_pipe[2];

	if (to_exec->next)
	{
		if (pipe(fd_pipe))
			post_parser_exit(&list, fd.infile, fd.outfile, ERR_PIPE);
		to_exec->fd_stdout = fd_pipe[1];
		to_exec->next->fd_stdin = fd_pipe[0];
	}
	else
		to_exec->fd_stdout = fd.outfile;
}

void	exec_cmds(t_cmd *list, t_files fd, char **envp)
{
	t_cmd	*to_exec;

	to_exec = list;
	to_exec->fd_stdin = fd.infile;
	while (to_exec)
	{
		init_child_fds(to_exec, fd, list);
		exec_child(to_exec, envp, list, fd);
		to_exec = to_exec->next;
	}
	close_fds(list, fd.infile, fd.outfile);
}
