/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:28:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2024/10/29 11:31:23 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	const char		*s;

	s = src;
	d = dest;
	if ((!dest) && (!src))
		return (NULL);
	while (n > 0)
	{
		*(d++) = *(s++);
		n--;
	}
	return (dest);
}
