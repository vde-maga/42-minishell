#include "minishell.h"

/*
Essa saída do Valgrind é **excelente**. Você não tem nenhum Memory Leak real!

```
==1282920== LEAK SUMMARY:
==1282920==    definitely lost: 0 bytes in 0 blocks  <-- ISSO É O MAIS IMPORTANTE
==1282920==    still reachable: 216 bytes in 11 blocks
```

### O que está acontecendo?

O erro **"Still Reachable"** (Ainda alcançável) significa que o programa terminou, mas ainda existiam ponteiros válidos apontando para esses blocos de memória. Diferente de "Definitely Lost", você não perdeu a referência da memória, apenas não deu `free` nela antes do programa morrer.

No contexto do **Minishell** e **Heredoc**, isso acontece quase sempre por causa do **`fork()`**.

1.  O seu processo pai (minishell) faz o parse do comando. Ele aloca memória para tokens, árvore de parser, envs, etc.
2.  Você faz um `fork()` para executar o Heredoc ou o comando `cat`.
3.  O **processo filho** herda toda a memória do pai (copiada).
4.  O filho faz o trabalho dele (lê o input, escreve no pipe) e chama `exit()` (ou `_exit`).
5.  Nesse momento do `exit` do filho, ele ainda tem os ponteiros para a árvore de parser e tokens que herdou do pai. Como ele morre sem limpar tudo (porque não é necessário, o OS limpa), o Valgrind reporta como "Still Reachable".

### Análise do Trace
Se olhar o seu log, as alocações vêm de:
*   `ft_parser_build_node_tree` (criando a estrutura do comando)
*   `ft_expand_variables` (expandindo o `$USER` e `$HOME` dentro do heredoc ou comando)
*   `ft_lexer` (tokens)

Isso confirma que é a estrutura do comando atual que ficou na memória do processo que finalizou.

### Preciso corrigir?

**Para a 42:**
*   **Definitely Lost:** É reprovação.
*   **Still Reachable:** Geralmente é aceitável, **especialmente em processos filhos**. A regra costuma ser: "Se o OS limpa quando o processo morre e não é um vazamento contínuo (que aumenta infinitamente enquanto o shell roda), está OK".

**Se você quiser limpar para ficar "Zero Bytes":**
No ponto onde o processo filho termina (provavelmente onde você processa o heredoc ou executa o cmd), você teria que chamar a função de limpeza total antes do `exit`.

Exemplo conceitual no filho do Heredoc:

```c
if (pid == 0) // Processo filho
{
    ft_process_heredoc(...);
    // Para evitar "still reachable", você teria que fazer:
    ft_free_shell(shell); 
    ft_free_env_list(env);
    // E qualquer outra coisa alocada
    exit(0);
}
```

**Resumo:**
O seu código está seguro. `0 definitely lost` é o que importa para não quebrar o sistema. O "still reachable" nesse cenário de Heredoc/Fork é um falso-positivo de problema, pois o Sistema Operacional reclama toda a memória do filho instantaneamente após o `exit`.

Pode seguir em frente! 🚀
*/

t_minishell	*shell_struct(t_minishell *shell, int flag)
{
	static t_minishell	*ptr;

	if (flag)
		return (ptr);
	ptr = shell;
	return (ptr);
}

static void ft_signals_heredoc_sigint_handler(int signal)
{
    // Recuperamos a struct apenas para fechar FDs, o que é seguro
    const t_minishell *ms_data = shell_struct(NULL, 1);

    (void)signal;
    
    // write é async-signal-safe: OK
    write(2, "\n", 1); 
    
    // close é async-signal-safe: OK
    if (ms_data) // Verificação de segurança
    {
        if (ms_data->hdc_fds[0] >= 0)
            close(ms_data->hdc_fds[0]);
        if (ms_data->hdc_fds[1] >= 0)
            close(ms_data->hdc_fds[1]);
    }
    
    // Atualizamos o código de erro (sua função estática)
    ft_exit_code(130);
    
    // NÃO usamos free aqui. O OS limpa a memória do filho ao morrer.
    // Usamos _exit para garantir segurança em sinais.
    _exit(130); 
}

void	ft_signals_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_signals_heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

