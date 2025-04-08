/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:22:23 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/08 15:21:12 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_redirection(char **table, t_command *cmd, int index, int len)
{
    int	count;

    printf("DEBUG: Entering ft_add_redirection\n");
    printf("DEBUG: table[index] = %s\n", table[index]);
    printf("DEBUG: index = %d, len = %d\n", index, len);
    printf("DEBUG: Current redirect flags = %d\n", cmd->redirect);

    count = 0;
    while (table[index][count] && (table[index][count] == '<'
            || table[index][count] == '>'))
        count++;

    printf("DEBUG: count of redirections = %d\n", count);

    if (count != len)
    {
        printf("DEBUG: Syntax error - unexpected token length\n");
        return (printf("syntax error near unexpected token `%c'\n",
                table[index][0]), 1);
    }

    if (table[index][len] == '\0')
    {
        printf("DEBUG: Empty redirection token\n");
        len = 0;
        index++;
        if (table[index] == NULL)
        {
            printf("DEBUG: No filename after redirection\n");
            return (printf("syntax error near unexpected token `newline'\n"),
                1);
        }
    }

    printf("DEBUG: Filename = %s\n", table[index]);

    if (cmd->redirect & IN_REDIR)
    {
        printf("DEBUG: Adding input redirection file\n");
        cmd->from_file = ft_add_io_file(cmd->from_file, table[index], len);
    }
    else if (cmd->redirect & HEREDOC)
    {
        printf("DEBUG: Adding heredoc delimiter\n");
        cmd->hdocs_end = ft_many_redirect(cmd->hdocs_end, table[index], len);
    }
    else
    {
        printf("DEBUG: Adding output redirection file\n");
        cmd->to_file = ft_many_redirect(cmd->to_file, table[index], len);
    }

    printf("DEBUG: Exiting ft_add_redirection successfully\n");
    return (0);
}
