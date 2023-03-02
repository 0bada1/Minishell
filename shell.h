typedef struct s_shell_s
{
    int		    num_commands; // number of all commands
    int		    num_pipes;  // number of all pipes
    char	    **path;    // a path for the list of path direcotories separeted by ':' (DONE)
    char	    *cmd_line; // read the command line (DONE)
    t_env_s	    envp;	// Has data about environment variables
	t_lexer	    *lexer;	// Used for tokenisation. Has tokens with quotes and without.
    t_execute   **command_blocks // has execution data for every command block
}   t_shell_s;

typedef struct s_execute
{
    int     num_commands;
    int     num_pipes;
    char    **args;
    char    *command;
    t_files *files;
    t_env   *env;
}t_execute;

typedef struct s_files
{
    int     num_of_redirections;
    char    **infile_name;
    char    **outfile_name;
    int     infile_fd;
    int     outfile_fd;
    char    *here_doc;
    char    *limter;
    char    *redirect_type;
}
