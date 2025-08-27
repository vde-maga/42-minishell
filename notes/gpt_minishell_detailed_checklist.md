# CHECKLIST DETALHADA - MINISHELL 42

# Fase 1 - Estrutura Básica

## Setup Inicial
[ ] Criar estrutura de diretórios (src/, includes/, Makefile)
[ ] Configurar Makefile com flags da 42 (-Wall -Wextra -Werror)
[ ] Incluir readline na compilação (-lreadline)
[ ] Definir header principal (minishell.h)
[ ] Integrar libft se necessário

## Loop Principal
[ ] Implementar prompt básico com readline()
[ ] Adicionar histórico com add_history()
[ ] Tratar EOF (Ctrl+D) graciosamente
[ ] Implementar comando 'exit' básico
[ ] Free da linha de input após uso

## Sinais
[ ] Handler para SIGINT (Ctrl+C) - nova linha + prompt
[ ] Ignorar SIGQUIT (Ctrl+\) no shell principal
[ ] Usar apenas 1 variável global para sinais
[ ] Restaurar prompt após sinal
[ ] Testar comportamento em diferentes contextos

---

# Fase 2 - Parsing

## Lexer/Tokenizador
[ ] Definir enum para tipos de tokens (WORD, PIPE, REDIRECT, etc.)
[ ] Implementar função de tokenização
[ ] Criar lista ligada de tokens
[ ] Tratar espaços e tabs corretamente
[ ] Identificar operadores: |, <, >, >>, <<

## Tratamento de Aspas
[ ] Estado para aspas simples (') - literal
[ ] Estado para aspas duplas (") - permite expansão
[ ] Detectar aspas não fechadas
[ ] Remover aspas do token final
[ ] Testar aspas aninhadas: "hello 'world'"

## Parser
[ ] Definir estrutura de comando
[ ] Implementar parsing recursivo ou state machine
[ ] Construir lista/árvore de comandos
[ ] Validar sintaxe: detectar |, ||, > >, etc.
[ ] Integrar redirecionamentos na estrutura

## Testes Críticos
[ ] echo "hello world"
[ ] echo 'hello $USER' (não expandir)
[ ] ls | wc -l
[ ] echo hello > file.txt
[ ] Syntax errors: |, >, ||

---

# Fase 3 - Variáveis

## Gerenciamento Básico
[ ] Copiar environ inicial do sistema
[ ] Implementar lista ligada própria de variáveis
[ ] Função get_env_value(key)
[ ] Função set_env_value(key, value)
[ ] Função unset_env_value(key)

## Expansão
[ ] Expandir $VARIABLE em contexto normal
[ ] Expandir $? (exit status anterior)
[ ] NÃO expandir dentro de aspas simples
[ ] Expandir dentro de aspas duplas
[ ] Casos especiais: $, $$, ${} se implementar

## Integração
[ ] Converter env list para array para execve()
[ ] Atualizar $? após cada comando
[ ] Sincronização com built-ins
[ ] Testes com variáveis vazias e inexistentes

---

# Fase 4 - Built-ins

## echo
[ ] echo sem argumentos
[ ] echo com argumentos múltiplos
[ ] echo -n (sem newline)
[ ] echo -n -n -n (múltiplas flags)
[ ] echo -n hello world

## cd
[ ] cd sem argumentos (vai para $HOME)
[ ] cd - (vai para $OLDPWD)
[ ] cd path (absoluto e relativo)
[ ] Atualizar PWD após mudança
[ ] Atualizar OLDPWD antes da mudança

## export/unset/env
[ ] export sem args (lista declare -x)
[ ] export VAR=value
[ ] export VAR (criar vazia)
[ ] unset VAR
[ ] env (listar todas variáveis)
[ ] Validar nomes de variáveis

## pwd/exit
[ ] pwd sem argumentos
[ ] exit sem argumentos
[ ] exit com número
[ ] exit com argumento inválido

---

# Fase 5 - Execução

## Resolução PATH
[ ] Buscar executável em $PATH
[ ] Tratar caminhos absolutos (/bin/ls)
[ ] Tratar caminhos relativos (./programa)
[ ] Retornar erro se comando não encontrado

## Fork e Execve
[ ] fork() para criar processo filho
[ ] execve() no filho com argumentos corretos
[ ] Converter environ para execve
[ ] Tratar erros de fork e execve

## Gerenciamento Processos
[ ] waitpid() para esperar filho
[ ] Capturar exit status com WEXITSTATUS
[ ] Atualizar $? com exit status
[ ] Evitar processos zumbi

---

# Fase 6 - Redirecionamentos

## Saída (>, >>)
[ ] Redirecionar > (truncar arquivo)
[ ] Redirecionar >> (append arquivo)
[ ] Usar dup2() para redirecionar STDOUT
[ ] Criar arquivo com permissões 644
[ ] Tratar erros de permissão

## Entrada (<)
[ ] Redirecionar < (ler de arquivo)
[ ] Usar dup2() para redirecionar STDIN
[ ] Verificar se arquivo existe
[ ] Tratar erros de leitura

## Heredoc (<<)
[ ] Ler linhas até delimiter
[ ] Criar pipe ou arquivo temporário
[ ] Redirecionar entrada do heredoc
[ ] Tratar Ctrl+C durante heredoc
[ ] Cleanup automático

---

# Fase 7 - Pipes

## Pipe Simples
[ ] Criar pipe com pipe()
[ ] Fork para cada comando
[ ] Conectar stdout do cmd1 com stdin do cmd2
[ ] Fechar FDs desnecessários em cada processo
[ ] Exit status = status do último comando

## Múltiplos Pipes
[ ] Implementar pipeline de N comandos
[ ] Gerenciar N-1 pipes para N comandos
[ ] Coordenar fechamento de todos os FDs
[ ] Built-ins em pipes executam em child

## Casos Complexos
[ ] ls | cat | wc -l
[ ] echo hello | cat > output.txt
[ ] Pipelines com redirecionamentos
[ ] Testar com built-ins em pipelines

---

# Fase 8 - Finalização

## Tratamento de Erros
[ ] Mensagens consistentes com bash
[ ] Tratar todos os códigos de erro
[ ] Syntax errors bem formatados
[ ] Não usar errno diretamente

## Gerenciamento Memória
[ ] Valgrind limpo (exceto readline)
[ ] Free todas as estruturas
[ ] Cleanup em casos de erro
[ ] Evitar double-free

## Testes Finais
[ ] Comparar comportamento com bash
[ ] Testar todos os built-ins
[ ] Testar combinações complexas
[ ] Testar casos extremos e edge cases
[ ] Performance adequada

---


