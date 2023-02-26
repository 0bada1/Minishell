/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/23 22:12:39 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define TRUE 0
# define FALSE 1

/* T_COUNTER
- This struct is just for general use to save lines.
It is used so I can easily pass multiple counters between functions and declare
many counters using one variable.
*/
typedef struct s_counter
{
	int	i;
	int	j;
	int	k;
	int	m;
	int	n;
	int	x;
	int	y;
	int	trigger;
	int	trigger2;
	int	counter;
}t_counter;

/* T_LEXER
- This is where tokenization take place. I sepearate everything into tokens
* What is a token?
- A token is any word seperated by space with a few exceptions.
These exceptions include double and single quotes. If a word is joined with double quotes,
the word outside the quotes and the everything within the quotes will be in the same token
regardless of spaces within the quotes. If two quotes are joined together, they will also be
in the same token regardless of space.
* Will I need this struct?
- I assume not, you'll mostly be using the t_shell_s as it contains everything parsed and ready to use.
If anything you need to check, you have the tokens if you had to use it for anything.
*/
typedef struct s_lexer
{
	char	**command_blocks;
	char	**raw_tokens;
	char	**tokens;
	int		num_of_tokens;
	int		num_of_pipes;
	int		num_of_commands;
	int		infile;
	int		outfile;
}t_lexer;

typedef struct s_env_s
{
    int		env_size;
    char	**envp;
    char	**key;
    char	**value;
}t_env_s;

typedef struct s_files
{
	int		**infile;
	int		**outfile;
	char	**filename;
}t_files;

/* T_SHELL_S
This is the main and most important struct that contains everything

* What is the scary triple pointer char ***flags?
- This is related to char **commands. Flags contain every argument to every command
The reason it is a triple pointer is the way it works. It is quite simple so don't be intimidated
Example:
minishell🤓$ ls -l -la -a | head -n5
Here commands will store "ls" and "head"
commands[0] = "ls"
commands[1] = "head"
Here flags will store the arguments for every command
flags[0][0] = "ls"
flags[0][1] = "-l"
flags[0][2] = "-a"
flags[1][0] = "head"
flags[1][1] = "-n5"
flags[1][1][0] = '-'
flags[1][1][1] = 'n'
flags[1][1][2] = '5'
and so on

* How do I use flags and why do I need it?
- Flags will be used in the second parameter of the function execve.
execve will take the parameters as such: execve(commands[i], flags[i], envp);
Commands and flags take the same counter. The reason this works is that execve
takes (char *cmd, char **flags, char **envp). So we have an extra pointer on
commands AND flags since we have a list of them.

* What is pipe_fd and why is an int **?
- Pipe_fd is a list of file descriptors. These file descriptors are from the external function pipe()
They are int ** because we have a list of fds because we also have a list of commands
- The number of pipes should always be number_of_commands - 1
The second pointer is the read and write fds that are opened by pipe()
You will be able to write the output of cmd1 into pipe[0][1] and then cmd2 will
read the output of cmd1 as cmd2's input from pipe[0][0]. This is just an example, so
it should work on any number of commands.

* Things I will add later:
- Infile and outfile must be int * since bash accepts more than one redirection of the same type
in the same prompt
*/
typedef struct s_shell_s
{
    int		num_commands; // number of all commands
    int		infile;  //file descriptor for redirect in file
    int		outfile;  // file descriptor for redirect out file
    int		num_pipes;  // number of all pipes
    int 	pipe_num;     // number of pipe process (get it after split) (What is this? -Obada)
	int		**pipe_fd; // List of pipe file descriptors used to pipe() between commands
	char	***flags;	// List of arguments of every command
    char	**commands; // Simple commands
    char	**path;    // a path for the list of path direcotories separeted by ':' (DONE)
    char	*home;  //  a path for a home directory (DONE)
    char	*cmd_line; // read the command line (DONE)
    t_env_s	envp;	// Has data about environment variables
	t_lexer	*lexer;	// Used for tokenisation. Has tokens with quotes and without.
	t_files	*files;	// Has all infiles and outfiles for every command block
}   t_shell_s;

/*--------------------------------SAMIYA-------------------------------*/
/*---------------------------------MAIN--------------------------------*/
void ft_signal();
void ft_ctrl_c();

/*--------------------------------OBADA--------------------------------*/
/*-------------------------------PARSING-------------------------------*/
t_shell_s		*parse(char *str, char **envp);

/*--------------------------------UTSIL1-------------------------------*/
int				skip_spaces(char *str, int i);
int				skip_token(char *str, int i);
int				skip_symbols(char *str, int i);
char			*check_for_input(char *str);
char			*check_for_output(char *str);
int				ft_strlen_spaces(char *str, int i);
int				count_pipes(char *str);
int				ft_strlen_equals(char *str);

/*--------------------------------UTSIL2-------------------------------*/
t_shell_s		*get_path(t_shell_s	*minishell, char **envp);
t_shell_s		*get_home(t_shell_s *minishell, char **envp);
t_shell_s		*get_env_struct(t_shell_s *minishell, char *envp[]);
t_shell_s		*get_commands(t_shell_s *minishell, char *str);
t_shell_s		*get_num_commands(t_shell_s *minishell, char *str);
t_shell_s		*get_command_blocks(t_shell_s *minishell, char *str);
t_shell_s		*get_redirections(t_shell_s *minishell);

/*--------------------------------UTSIL3-------------------------------*/
t_shell_s		*lexer(t_shell_s *minishell, char *str);
char			*lexer_dquotes(t_shell_s *minishell, char *str, int i);
char			*lexer_squotes(t_shell_s *minishell, char *str, int i); // NOT DONE
int				number_of_dquotes(char *str);
int				number_of_squotes(char *str);
int				ft_strlen_dquotes(char *str, int i);
int				ft_strlen_squotes(char *str, int i);
// char			*dqouted_string(char *str, int i);
// char			*sqouted_string(char *str, int i); // NOT DONE
void			print_struct(t_shell_s *args);

/*--------------------------------UTSIL4-------------------------------*/
int				num_of_tokens(char *str);
int				token_size(char *str, int i);
char    		*get_next_word(char *str, int i);

/*--------------------------------UTSIL5-------------------------------*/
int				check_if_command(t_shell_s *minishell, char *token);
int				get_num_flags(char **token, int i);
int				check_validity(t_shell_s *minishell, char *str);

/*--------------------------------UTSIL6-------------------------------*/
t_shell_s		*raw_lexer(t_shell_s *minishell, char *str);
int				raw_token_size(char *str, int i);
char			**split_pipes(char	*str);
int				length_to_pipe(char *str, int i);

/*--------------------------------UTSIL7-------------------------------*/
t_shell_s	   *dollar_sign(t_shell_s *minishell);
t_shell_s	   *dollar_sign_env_variables(t_shell_s *minishell);

/*---------------------------------FREE--------------------------------*/
void		    free_everything(t_shell_s *minishell);
void    		free_2d(char **array);

#endif