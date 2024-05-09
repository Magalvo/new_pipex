/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:57:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 12:51:04 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_infile(t_pipex *pipex, char **argv)
{
	if (pipex->here_doc)
		here_doc(argv[2], pipex);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			error_msg("infile err");
	}
}

void	ft_outfile(t_pipex *pipex, char *argv)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (pipex->outfile < 0)
		error_msg("outfile err");
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
