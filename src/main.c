#include "../includes/minishell.h"

static void ft_init_vars(t_minishell *ms_data)
{
    ms_data->env = NULL;
    ms_data->exit_status = -1;
}

int main(int ac, char **av, char **envp)
{
    t_minishell ms_data;
    char *line;
    // TODO: Check possibility to add the lexer structs to the main minishell struct
    // t_lexer *lexer;
    // t_token *tokens;

    (void)ac;
    (void)av;
    (void)envp;
    ft_init_vars(&ms_data);
    while (1)
    {
        // 1 - Get line from user
        line = get_str_readline();
        printf("%s", line);
        if (!line)
            break;
    
        // TODO: 2 - Tokenize the input (Lexing)
        
        // TODO: 3 - Parsing -> Evaluating -> Exec and repeat
    }
    return EXIT_SUCCESS;
}
