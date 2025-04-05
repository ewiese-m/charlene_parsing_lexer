/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:11 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 13:30:38 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_join_free_both(char *s1, char *s2)
{
	char	*nstr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	nstr = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1, len_s1 + 1);
	ft_strlcpy(&nstr[len_s1], s2, len_s2 + 1);
	free(s1);
	free(s2);
	return (nstr);
}

static char	*handle_quotes(char *str, char *input, int *i, t_env *env_list)
{
	return (ft_process_quotes(str, input, i, env_list));
}

static char	*handle_dollar_sign(char *str, char *input, int *i, t_env *env_list)
{
	char	*expanded;
	char	*old;

	expanded = ft_extract_env_var(input, i, env_list);
	old = str;
	str = ft_strjoin(str, expanded);
	free(old);
	free(expanded);
	(*i)++;
	return (str);
}

static char	*handle_regular_char(char *str, char *input, int *i)
{
	char	tmp[2];
	char	*old;

	tmp[0] = input[*i];
	tmp[1] = '\0';
	old = str;
	str = ft_strjoin(str, tmp);
	free(old);
	(*i)++;
	return (str);
}

static void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || (input[*i] >= '\t'
				&& input[*i] <= '\r')))
		(*i)++;
}

char	*ft_tokenize(char *str, char *input, int *index, t_env *env_list)
{
	int		i;
	int		in_quotes;
	char	quote_type;

	i = *index;
	in_quotes = 0;
	quote_type = 0;
	while (input[i] && (in_quotes || (input[i] != ' ' && input[i] != '<'
				&& input[i] != '>')))
	{
		if (!in_quotes && (input[i] == '"' || input[i] == '\''))
		{
			in_quotes = 1;
			quote_type = input[i];
			str = ft_join_free_both(str, ft_substr(&input[i], 0, 1));
			i++;
		}
		else if (in_quotes && input[i] == quote_type)
		{
			in_quotes = 0;
			quote_type = 0;
			str = ft_join_free_both(str, ft_substr(&input[i], 0, 1));
			i++;
		}
		else if (!in_quotes && (input[i] == '<' || input[i] == '>'))
			break ;
		else if (input[i] == '"' || input[i] == '\'')
		{
			str = handle_quotes(str, input, &i, env_list);
		}
		else if (input[i] == '$')
		{
			str = handle_dollar_sign(str, input, &i, env_list);
		}
		else
			str = handle_regular_char(str, input, &i);
	}
	skip_whitespace(input, &i);
	*index = i;
	return (str);
}
