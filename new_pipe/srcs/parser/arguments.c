/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:10:49 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/08 22:40:47 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

/* char	*args_parsing(char **argv, char **envp)
{
	char	**paths;
	char	**args;
	int		i;
	
	args = ft_split(argv[2], ' ');
	
	i = -1;
	char *cmd;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], args[0]);
		if (execve(cmd, args, envp) == -1)
			perror("execve fail: \n");
		free(cmd);
	}
	exit(EXIT_FAILURE);
} */

void	free_paths(char **paths, int i)
{
	int ctd;

	ctd = 0;
	if (!paths)
		return ;
	while (ctd < i)
	{
		if (paths[i])
			free(paths[i]);
		ctd++;
	}
	free(paths);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	content_check(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (!argv[i][0])
			return (0);
		i++;
	}
	return (1);
}

int	arg_check(char **argv, t_pipex *pipex)
{
	if (argv[1] && !ft_strncmp("here_doc", argv[1], 9))
		return (pipex->here_doc = 1, 6);
	else
		return (pipex->here_doc = 0, 5);
}

char *env_paths(t_pipex *pipx, char **envp)
{
    char **paths;
    char *slash;
    int i;
    int len;

    len = 0;
    i = 0;
    while (ft_strncmp(*envp, "PATH=", 5) != 0)
        envp++;
    paths = ft_split(*envp + 5, ':');
    if (!paths)
        return NULL;
    while (paths[i])
    {
        len = ft_strlen(paths[i]);
        if (paths[i][len - 1] != '/')
        {
            slash = ft_strjoin(paths[i], "/");
            if (!slash)
            {
                free_paths(paths, i);
                return NULL;
            }
            free(paths[i]);
            paths[i] = slash;   
        }
        i++;
    }
    pipx->cmd_paths = paths;
    return NULL;
}


