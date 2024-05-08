/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:49:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/08 22:35:12 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"


static void	pipe_creation(t_pipex *pipex)
{
	int	ctd;

	ctd = 0;
	while (ctd < (pipex->cmd_nbr) - 1)
	{
		if (pipe(pipex->pipes + 2 * ctd) < 0)
			free_parent(pipex);
		ctd++;
	}
}
void	pipe_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nbr))
	{
		close(pipex->pipes[i]);
		i++;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_pipex	d;
	
	if (argc < arg_check(argv, &d) || !content_check(argv))
	{
		ft_putstr_fd("Too few OR invalid arguments\n", 2);
		return (1);
	}
	ft_infile(&d, argv);
	ft_outfile(&d, argv[argc-1]);
	d.cmd_nbr = argc - 3 - d.here_doc;
	d.pipe_nbr = (2 * (d.cmd_nbr - 1));
	d.pipes = (int *)malloc(sizeof(int) * d.pipe_nbr);
	if (!d.pipes)
		error_msg("err creating pipes");
	env_paths(&d, envp);
	if(!d.cmd_paths)
		free_pipes(&d);
	pipe_creation(&d);
	d.id_n = -1;
	while (++(d.id_n) < d.cmd_nbr)
		child(d, argv, envp);
	pipe_close(&d);
	waitpid(-1, NULL, 0);
	free_parent(&d);
	return (0);
}

