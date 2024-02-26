/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:19:04 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/26 15:44:33 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**find_cmds_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		parser_exit(NULL, NULL, NULL, ERR_NO_PATH);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		parser_exit(NULL, NULL, NULL, ERR_MALLOC);
	return (paths);
}

void	test_access(char **paths, char **args, t_cmd **list)
{
	int		i;
	char	*path_to_test;
	char	*slash_prefix;

	i = 0;
	slash_prefix = ft_strjoin("/", args[0]);
	if (!slash_prefix)
		parser_exit(paths, args, list, ERR_MALLOC);
	while (paths[i])
	{
		path_to_test = ft_strjoin(paths[i], slash_prefix);
		if (!path_to_test)
			break ;
		if (!access(path_to_test, X_OK))
		{
			free(args[0]);
			args[0] = path_to_test;
			break ;
		}
		free(path_to_test);
		i++;
	}
	free(slash_prefix);
	if (!path_to_test)
		parser_exit(paths, args, list, ERR_MALLOC);
}

char	**parse_command(char *cmd, char **paths, t_cmd *list)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		parser_exit(paths, args, &list, ERR_MALLOC);
	if (!args[0])
		parser_exit(paths, args, &list, ERR_NO_ARGS);
	if (access(args[0], X_OK))
		test_access(paths, args, &list);
	return (args);
}

t_cmd	*create_cmds_list(char **argv, char **envp)
{
	char	**args;
	char	**paths;
	t_cmd	*list;
	t_cmd	*new_node;
	int		i;

	list = NULL;
	paths = find_cmds_paths(envp);
	i = 0;
	while (argv[i + 1])
	{
		args = parse_command(argv[i], paths, list);
		new_node = ft_cmdnew(args);
		if (!new_node)
			parser_exit(paths, args, &list, ERR_MALLOC);
		ft_cmdadd_back(&list, new_node);
		i++;
	}
	free_array(paths);
	return (list);
}
