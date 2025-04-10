/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 09:43:39 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 21:00:46 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

/*
** Environment variable structure for linked list
*/
typedef struct s_env
{
	char				*key;
	char				*value;
	int					custom;
	int					exit_status;
	int					index;
	struct s_env		*next;
}						t_env;

/*
** Main shell structure
*/

/*
** Command structure for parsing and execution
*/

/* Command name */
/* Arguments */
/* Full command array for execve */
/* Input redirection file */
/* Heredoc delimiters */
/* Output redirection files */
/* Redirection flags */
/* Input source fd */
/* Output destination fd */
/* Next command in pipeline */

typedef struct s_command
{
	char				*command;
	char				**args;
	char				**full_cmd;
	char **from_file; // Changed from char* to char**
	char				**hdocs_end;
	char				**to_file;
	int					redirect;
	int					input;
	int					output;
	struct s_command	*next;
}						t_command;

/* Pipeline structure for command execution */
/* Array of commands */
/* Number of commands */
/* Array of pipe file descriptors */

typedef struct s_pipeline
{
	t_command			**commands;
	int					cmd_count;
	int					**pipes;
}						t_pipeline;

/*
** Redirection flags
*/
# define IN_REDIR 1 /* Input redirection (<) */
# define HEREDOC 2 /* Here document (<<) */
# define OUT_REDIR 4 /* Output redirection (>) */
# define APPEND 8 /* Append redirection (>>) */

/*
** Environment management functions
*/
char					**free_list(char **list);
t_env					*ft_create_env_node(char *envp, int index);
t_env					*ft_get_envp(char **envp);

/*
** Lexer and Parser functions
*/
char					*ft_expand_variable(char *input, t_env *env_list);
char					*ft_extract_env_var(char *in_put, int *index,
							t_env *env_list);
char					*handle_expansion(char *result, char *input, int *i,
							t_env *env_list);
char					*ft_process_quotes(char *str, char *input, int *index,
							t_env *env_list);
char					**ft_realloc(char **ptr, size_t new_size);
char					*ft_tokenize(char *str, char *input, int *index,
							t_env *env_list);
/* tokenize utils */

/* tokenize utils end */
char					**ft_lexer(char *line, t_env *env_list);
char					*ft_concat_and_free(char *str1, char *str2);
char					**ft_resize_string_array(char **array, int current_size,
							int target_size);
int						ft_get_redirection(char *token);
void					ft_arrange_table(char **table, int index, int len);
char					**ft_add_io_file(char **old_files, char *new_file,
							int len_redirection);
char					**ft_many_redirect(char **old_files, char *new_file,
							int len);
int						ft_add_redirection(char **table, t_command *cmd,
							int index, int len);
int						ft_check_redirect(t_command *cmd, char **cmd_table);
void					ft_free_dstr(char **str);
t_command				*ft_parser(char **cmd_table);
int						count_command(char *line);
int						extract_command(char *line, int i, char **cmd);
char					**parse_cmd_into_array(char *line);
void					ft_free_cmdlist(t_command **cmd);
t_command				*ft_many_cmd(t_command *cmd, char **full_cmd,
							t_env *env_list);
t_command				*tokenize_parse_and_link_commands(char *line,
							t_env *env_list);
int						ft_checkforgarbage(t_command *cmd);
void					ft_removesurplusspaces(t_command *cmd);
void					ft_create_fullcmd(t_command *cmd);
t_command				*ft_parse_input(char *line, t_env *env_list);

/*
** Signal handling functions
*/
void					ft_signal_ctrl_c(int signal);

/*
** Main program functions
*/
int						main(int argc, char **argv, char **envp);
/* Display functions */
void					display_command_info(t_command *cmds);
void					display_command_name(t_command *cmd);
void					display_arguments(t_command *cmd);
void					display_full_command(t_command *cmd);
void					display_redirections(t_command *cmd);

#endif
