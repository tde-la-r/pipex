/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:05:13 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/23 17:52:28 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# define ERR_MALLOC "malloc"
# define ERR_PIPE "pipe"
# define ERR_FORK "fork"
# define ERR_DUP "dup2"
# define ERR_EXECVE "execve"
# define ERR_NO_PATH "Error : path to cmds not found"
# define ERR_HERE_DOC "pipex: warning: here-document delimited by end-of-file"
# define TMP_FILE "tmp"

typedef struct s_cmd
{
	char			**args;
	pid_t			pid;
	int				fd_stdin;
	int				fd_stdout;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_files
{
	int	infile;
	int	outfile;
}		t_files;

void	parser_exit(char **paths, char **args, t_cmd **list, char *err);
void	post_parser_exit(t_cmd **list, int infile, int outfile, char *err);
void	free_array(char **array);
void	close_fds(t_cmd *list, int infile, int outfile);
void	delete_here_document(void);

t_cmd	*create_cmds_list(char **argv, char **envp);
void	exec_cmds(t_cmd *list, t_files fd, char **envp);

void	ft_cmdclear(t_cmd **lst, void (*del)(char **));
t_cmd	*ft_cmdnew(char **args);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);

#endif
