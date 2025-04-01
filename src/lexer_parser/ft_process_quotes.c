/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:18:02 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 15:19:34 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_concat_and_free(char *str1, char *str2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!str1)
		str1 = (char *)ft_calloc(1, sizeof(char));
	if (!str1 || !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str1, len1 + 1);
	ft_strlcpy(&result[len1], str2, len2 + 1);
	free(str1);
	free(str2);
	return (result);
}

char	*ft_process_quotes(char *result, char *input_str, int *pos,
		t_env *env_list)
{
	char	*expanded;
	char	quote_type;
	int		i;

	i = *pos;
	quote_type = input_str[i];
	while (input_str[++i] && input_str[i] != quote_type)
	{
		expanded = NULL;
		if (input_str[i] == '$' && quote_type == '"')
			expanded = ft_extract_env_var(input_str, &i, env_list);
		if (expanded)
			result = ft_concat_and_free(result, expanded);
		else
			result = ft_concat_and_free(result, ft_substr(&input_str[i], 0, 1));
	}
	*pos = i;
	return (result);
}
