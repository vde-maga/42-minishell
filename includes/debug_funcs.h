#ifndef DEBUG_FUNCS_H
# define DEBUG_FUNCS_H

// Test / debug helpers functions
void	ft_parser_test(t_token *tokens);
void	ft_parser_tree_test(t_token *tokens);
void	print_tokens(t_token *tokens);
void	ft_test_heredoc(t_minishell *ms);

#endif