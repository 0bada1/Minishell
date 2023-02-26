#include "../include/minishell.h"

t_shell_s   *dollar_sign(t_shell_s *minishell)
{
    t_counter   count;
    char        *str;
    char        *pid;

    if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens)
        return (NULL);
    count.i = 0;
    while (minishell->lexer->raw_tokens[count.i])
    {
        count.j = 0;
        while (minishell->lexer->raw_tokens[count.i][count.j])
        {
            if (minishell->lexer->raw_tokens[count.i][count.j] == '\'')
            {
                count.j++;
                while (minishell->lexer->raw_tokens[count.i][count.j] && minishell->lexer->raw_tokens[count.i][count.j] != '\'')
                    count.j++;
                count.j++;
            }
            if (minishell->lexer->raw_tokens[count.i][count.j] == '$' && minishell->lexer->raw_tokens[count.i][count.j + 1] && minishell->lexer->raw_tokens[count.i][count.j + 1] == '$')
            {
                str = ft_strdup(minishell->lexer->raw_tokens[count.i]);
                free(minishell->lexer->raw_tokens[count.i]);
                minishell->lexer->raw_tokens[count.i] = malloc(sizeof(char) * (ft_strlen(str) + (ft_strlen(ft_itoa(getpid())) - 2) + 1));
                count.k = 0;
                count.m = 0;
                count.n = 0;
                while (str[count.k])
                {
                    if (str[count.k] == '$' && str[count.k + 1 && str[count.k + 1] == '$'])
                    {
                        pid = ft_itoa(getpid());
                        while (pid[count.n] && minishell->lexer->raw_tokens[count.i][count.m])
                            minishell->lexer->raw_tokens[count.i][count.m++] = pid[count.n++];
                        count.k += 2;
                    }
                    else
                        minishell->lexer->raw_tokens[count.i][count.m++] = str[count.k++];
                }
                minishell->lexer->raw_tokens[count.i][count.m] = '\0';
                free(str);
                if (pid)
                    free(pid);
            }
            count.j++;
        }
        printf("token[%i] after dollar sign function = %s\n", count.i, minishell->lexer->raw_tokens[count.i]);
        count.i++;
    }
    return (minishell);
}

t_shell_s   *dollar_sign_env_variables(t_shell_s *minishell)
{
    t_counter   count;
    char        *str;

    if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens)
        return (NULL);
    count.i = 0;
    while (minishell->lexer->raw_tokens[count.i])
    {
        count.j = 0;
}