/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:24:48 by ewiese-m          #+#    #+#             */
/*   Updated: 2024/10/25 16:35:01 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int c, int fd)
{
	char	digit;

	if (c == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	else if (c < 0)
	{
		ft_putstr_fd("-", fd);
		ft_putnbr_fd(-c, fd);
	}
	else
	{
		if (c >= 10)
		{
			ft_putnbr_fd(c / 10, fd);
		}
		digit = '0' + (c % 10);
		ft_putchar_fd(digit, fd);
	}
}
