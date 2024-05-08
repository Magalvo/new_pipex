/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:26:23 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/08 13:03:40 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../lib/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void here_doc(char *delimiter, t_pipex *pipx) 
{
    int     file;
    char    *line = NULL;

    file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file == -1) {
        perror("open");
        exit(EXIT_FAILURE); 
    }

    while (1) {
        write(1, "here_doc> ", 10);
        line = get_next_line(0);
        if (line == NULL) {
            perror("get_next_line");
            exit(EXIT_FAILURE); 
        }
        if (ft_strcmp(delimiter, line, ft_strlen(delimiter)) == 0)
            break;
        ft_putstr_fd(line, file);
        free(line);
    }
    free(line);
    close(file);
    pipx->infile = open(".heredoc_tmp", O_RDONLY);
    if (pipx->infile < 0) {
        unlink(".heredoc_tmp"); 
        perror("open");
        exit(EXIT_FAILURE); 
	}
}

