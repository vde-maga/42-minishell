// #include "../../includes/minishell.h"

// char	*expand_env_vars(const char *input, char **envp)
// {
// 	return ft_strdup(input);
// }

// void	ft_expander(t_minishell *ms_data, char **envp)
// {
// 	char	*sanitized_str;

// 	ft_handle_qutoes(ms_data->input_line)
// 		ft_
// 	if (ms_data->input_line)
// 	{
// 		char *expanded = expand_env_vars(ms_data->input_line, envp);
// 		free(ms_data->input_line);
// 		ms_data->input_line = expanded;
// 	}
// }

/**
* # Expander
*
* > Sanitizar o conteudo pelo lexer, ao lidar com aspas (`"` e `'`)
* >
* > Substituir as variaveis `$VAR` pelo correspondente em `envp`
* >
* > Devolver o conteudo recebido, limpo de aspas e as $VAR substituidas
*
* ## Como deve Funcionar
*
* 1. Detetar Aspas
* 	1. Aspas simples, limpar e armazenar o conteudo original
*	2. Aspas duplas, limpar e verificar se e uma `$VAR` valida
* 2. Detetar $
* 	1. Identificar o `$` e o chars depois
* 	2. Substituir esses chars, pelo correspondente em `envp`
* 3. Sanitize
* 	1. Limpar aspas
* 	2. Substituir Vars
*
* ## Pseudocodigo
*
*```c
* char	*ft_expander(t_minishell *ms_data, char **envp)
* {
* 	char	*sanitized_input;
*
*	sanitized_input = ft_handle_quotes(ms_data->input_line / input);
*	sanitized_input = ft_expande_variables(ms_data->input_line / input);
*	return (sanitized_input);
*}
* ```
*/
