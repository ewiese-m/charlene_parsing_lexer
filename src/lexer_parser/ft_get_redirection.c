/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:35:43 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_redirection(char *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(token, "<", 1) == 0)
		return (IN_REDIR);
	if (ft_strncmp(token, ">", 1) == 0)
		return (OUT_REDIR);
	return (0);
}
