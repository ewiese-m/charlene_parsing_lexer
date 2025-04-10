/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:22:23 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 21:01:38 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_redirection(char **table, t_command *cmd, int index, int len)
{
    int	count;

    printf("\033[31mDEBUG: Entering ft_add_redirection\033[0m\n");
    printf("\033[31mDEBUG: table[index] = '%s'\033[0m\n", table[index]);
    printf("\033[31mDEBUG: index = %d, len = %d\033[0m\n", index, len);
    printf("\033[31mDEBUG: Current redirect flags = %d\033[0m\n", cmd->redirect);

    count = 0;
    while (table[index][count] && (table[index][count] == '<'
            || table[index][count] == '>'))
        count++;

    printf("\033[31mDEBUG: count of redirections = %d\033[0m\n", count);

    if (count != len)
    {
        printf("\033[31mDEBUG: Syntax error - unexpected token length (count=%d, len=%d)\033[0m\n",
               count, len);
        return (printf("syntax error near unexpected token `%c'\n",
                table[index][0]), 1);
    }

    if (table[index][len] == '\0')
    {
        printf("\033[31mDEBUG: Empty redirection token, checking next token\033[0m\n");
        len = 0;
        index++;
        if (table[index] == NULL)
        {
            printf("\033[31mDEBUG: No filename after redirection\033[0m\n");
            return (printf("syntax error near unexpected token `newline'\n"),
                1);
        }
        printf("\033[31mDEBUG: Found filename token: '%s'\033[0m\n", table[index]);
    }

    printf("\033[31mDEBUG: Processing redirection with filename = '%s', len = %d\033[0m\n",
           table[index], len);

    if (cmd->redirect & IN_REDIR)
    {
        printf("\033[31mDEBUG: Adding input redirection file\033[0m\n");
        cmd->from_file = ft_add_io_file(cmd->from_file, table[index], len);
/*         if (cmd->from_file)
            printf("\033[31mDEBUG: Input file set to '%s'\033[0m\n", cmd->from_file);
        else
            printf("\033[31mDEBUG: Failed to set input file\033[0m\n"); */
    }
    else if (cmd->redirect & HEREDOC)
    {
        printf("\033[31mDEBUG: Adding heredoc delimiter\033[0m\n");
        cmd->hdocs_end = ft_many_redirect(cmd->hdocs_end, table[index], len);
        if (cmd->hdocs_end)
            printf("\033[31mDEBUG: Heredoc delimiter added\033[0m\n");
        else
            printf("\033[31mDEBUG: Failed to add heredoc delimiter\033[0m\n");
    }
    else
    {
        printf("\033[31mDEBUG: Adding output redirection file\033[0m\n");
        cmd->to_file = ft_many_redirect(cmd->to_file, table[index], len);
        if (cmd->to_file)
            printf("\033[31mDEBUG: Output file added\033[0m\n");
        else
            printf("\033[31mDEBUG: Failed to add output file\033[0m\n");
    }

    printf("\033[31mDEBUG: Exiting ft_add_redirection successfully\033[0m\n");
    return (0);
}
