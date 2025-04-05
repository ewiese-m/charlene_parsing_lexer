/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:30:00 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 13:33:54 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_signals(void)
{
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

static void	process_command(char *line, t_env *env_list)
{
	t_command	*cmds;

	if (!line || *line == '\0')
		return ;
	printf("You entered: %s\n", line);
	add_history(line);
	cmds = ft_parse_input(line, env_list);
	if (cmds)
		display_command_info(cmds);
	else
		printf("Command parsing failed or empty input\n");
	if (cmds)
		ft_free_cmdlist(&cmds);
	free(line);
}

static void	cleanup_resources(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	clear_history();
}

static void	minishell_loop(t_env *env_list)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_command(line, env_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	setup_signals();
	env_list = ft_get_envp(envp);
	if (!env_list)
	{
		fprintf(stderr, "Error: Failed to initialize environment\n");
		return (1);
	}
	minishell_loop(env_list);
	cleanup_resources(env_list);
	return (0);
}
