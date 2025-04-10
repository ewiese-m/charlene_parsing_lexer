/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_io_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:23:15 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 21:12:36 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **ft_add_io_file(char **old_files, char *new_file, int len_redirection)
{
    int     size;
    char    **files;
    int     i;

    size = 0;
    if (old_files)
    {
        while (old_files[size])
            size++;
    }
    files = (char **)malloc((size + 2) * sizeof(char *));
    if (!files)
        return (NULL);
    i = 0;
    while (i < size)
    {
        files[i] = old_files[i];
        i++;
    }
    files[size] = ft_substr(new_file, len_redirection, ft_strlen(new_file));
    files[size + 1] = NULL;
    if (old_files)
        free(old_files);
    return (files);
}
