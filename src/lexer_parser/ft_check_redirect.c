/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:24:59 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/07 13:41:09 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_redirect_length(int redirect_type)
{
	if (redirect_type & (HEREDOC | APPEND))
		return (2);
	else
		return (1);
}

static int	process_redirection(t_command *cmd, char **cmd_table, int i,
		int redirect_type)
{
	int	redirect_len;
	int	old_redirect;

	redirect_len = get_redirect_length(redirect_type);
	old_redirect = cmd->redirect;
	cmd->redirect = redirect_type;
	if (ft_add_redirection(cmd_table, cmd, i, redirect_len))
		return (1);
	cmd->redirect = redirect_type | old_redirect;
	ft_arrange_table(cmd_table, i, redirect_len);
	return (0);
}

int ft_check_redirect(t_command *cmd, char **cmd_table)
{
    int i;
    int redirect_type;
    int process_result;

    i = 0;
    while (cmd_table[i])
    {
        redirect_type = ft_get_redirection(cmd_table[i]);
        if (redirect_type)
        {
            process_result = process_redirection(cmd, cmd_table, i, redirect_type);
            if (process_result)
                return (1);
        }
        else
        {
            i++;
        }
    }
    return (0);
}
