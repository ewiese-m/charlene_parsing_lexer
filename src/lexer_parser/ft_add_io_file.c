/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_io_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:23:15 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_add_io_file(char *old_file, char *new_file, int len_redirection)
{
	if (old_file)
		free(old_file);
	return (ft_substr(new_file, len_redirection, ft_strlen(new_file)));
}
