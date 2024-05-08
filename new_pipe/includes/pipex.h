/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:22:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/08 19:13:49 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>
#include "../srcs/lib/libft.h"
#include "../srcs/lib/gnl/gnl.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

#ifndef FOPEN_MAX
#define FOPEN_MAX 1024
#endif

# define	MAX_ARGS 10
# define	MAX_CMDS 10

typedef struct	s_pipex	t_pipex;
typedef	struct	s_cmds	t_cmds;

/* struct				s_pipex
{	
	int				prev_pipe[2];
	int				next_pipe[2];
	pid_t			pid1;
	pid_t			pid2;
	char			**cmd_paths;
	char			*cmd;
	char			**cmd_args;
	int				pipxfd[2];
	int				infile;
	int				outfile;
	int				here_doc;
	int				cmd_nbr;
	int				pipe_nbr;
	int				*pipes;
	int				id_n;
}; */

struct				s_pipex
{	
	pid_t			pid;
	char			*env_path;
	char			**cmd_paths;
	char			*cmd;
	char			**cmd_args;
	int				infile;
	int				outfile;
	int				here_doc;
	int				cmd_nbr;
	int				pipe_nbr;
	int				*pipes;
	int				id_n;
};


//Error And Free
void	error_msg(char *str);
void	free_parent(t_pipex *pipx);
void	free_pipes(t_pipex *pipex);
void	pipe_msg(char *arg);
void	pipe_close(t_pipex *pipex);
void	child_free(t_pipex *pipex);
int		content_check(char **argv);

//Files
void	ft_infile(t_pipex *pipex, char **argv);
void	ft_outfile(t_pipex *pipex, char *argv);

//Args
//char	*args_parsing(char **argv, char **envp);
int		arg_check(char **argv, t_pipex *pipex);


void	child(t_pipex d, char **argv, char **envp);


void	here_doc(char *delimiter, t_pipex *pipx);
char	*env_paths(t_pipex *pipx, char **envp);
#endif
