/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:24:59 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/30 13:59:35 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redirect(t_command *cmd, char **cmd_table)
{
	int	i;
	int	redirect_type;
	int	redirect_len;
	int	old_redirect;

	i = 0;
	while (cmd_table[i])
	{
		redirect_type = ft_get_redirection(cmd_table[i]);
		if (redirect_type)
		{
			redirect_len = 1;
			if ((redirect_type & HEREDOC) || (redirect_type & APPEND))
				redirect_len = 2;
			old_redirect = cmd->redirect;
			cmd->redirect = redirect_type;
			if (ft_add_redirection(cmd_table, cmd, i, redirect_len))
				return (1);
			cmd->redirect = redirect_type | old_redirect;
			ft_arrange_table(cmd_table, i, redirect_len);
			continue ;
		}
		i++;
	}
	return (0);
}
