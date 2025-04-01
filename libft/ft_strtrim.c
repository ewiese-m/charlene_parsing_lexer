/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:54:24 by ewiese-m          #+#    #+#             */
/*   Updated: 2024/10/24 14:58:43 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	first;
	size_t	last;
	size_t	len;
	size_t	len_s1;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_s1 = ft_strlen((char *)s1);
	first = 0;
	while (first < len_s1 && ft_strchr(set, s1[first]) != (void *)0)
		first++;
	last = len_s1;
	while (last > first && ft_strchr(set, s1[last - 1]) != (void *)0)
		last--;
	len = last - first;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1 + first, len + 1);
	return (res);
}
