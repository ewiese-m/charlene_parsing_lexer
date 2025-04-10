/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:20:08 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 20:59:06 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_free_cmdlist(t_command **cmd)
{
    t_command *tmp;

    tmp = *cmd;
    while (tmp)
    {
        *cmd = (*cmd)->next;
        if (tmp->command)
            free(tmp->command);
        if (tmp->args)
            ft_free_dstr(tmp->args);
        if (tmp->full_cmd)
            ft_free_dstr(tmp->full_cmd);
        if (tmp->redirect & IN_REDIR)
            ft_free_dstr(tmp->from_file);  // Changed to use ft_free_dstr
        if (tmp->redirect & HEREDOC)
            ft_free_dstr(tmp->hdocs_end);
        if ((tmp->redirect & OUT_REDIR) || (tmp->redirect & APPEND))
            ft_free_dstr(tmp->to_file);
        free(tmp);
        tmp = *cmd;
    }
}
