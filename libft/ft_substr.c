/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 08:52:42 by ewiese-m          #+#    #+#             */
/*   Updated: 2024/10/24 14:55:35 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	m_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	m_len = s_len - start;
	if (m_len > len)
		m_len = len;
	substr = (char *)malloc(m_len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < m_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[m_len] = '\0';
	return (substr);
}
