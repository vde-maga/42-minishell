# CHECKLIST DETALHADA - MINISHELL 42

# Fase 1 - Estrutura Básica

## Setup Inicial
- [X] Criar estrutura de diretórios (src/, includes/, Makefile)
- [X] Configurar Makefile com flags da 42 (-Wall -Wextra -Werror)
- [X] Incluir readline na compilação (-lreadline)
- [X] Definir header principal (minishell.h)
- [X] Integrar libft se necessário

## Loop Principal
- [X] Implementar prompt básico com readline()
- [X] Adicionar histórico com add_history()
- [X] Tratar EOF (Ctrl+D) graciosamente
- [X] Implementar comando 'exit' básico
- [X] Free da linha de input após uso

## Sinais
- [ ] Handler para SIGINT (Ctrl+C) - nova linha + prompt
- [ ] Ignorar SIGQUIT (Ctrl\\) no shell principal
- [ ] Usar apenas 1 variável global para sinais
- [ ] Restaurar prompt após sinal
- [ ] Testar comportamento em diferentes contextos

---

# Fase 2 - Parsing

## Lexer/Tokenizador
- [X] Definir enum para tipos de tokens (WORD, PIPE, REDIRECT, etc.)
- [X] Implementar função de tokenização
- [X] Criar linked list dos tokens
- [X] Tratar espaços e tabs corretamente
- [X] Identificar operadores: |, <, >, >>, <<, &&, &

## Tratamento de Aspas
- [ ] Estado para aspas simples (') - literal
- [ ] Estado para aspas duplas (") - permite expansão
- [X] Detectar aspas não fechadas
- [ ] Remover aspas do token final
- [ ] Testar aspas aninhadas: "hello 'world'"

## Parser
- [X] Definir estrutura de comando
- [X] Implementar parsing recursivo ou state machine
- [X] Construir lista/árvore de comandos
- [X] Validar sintaxe: detectar |, ||, > >, etc.
- [X] Integrar redirecionamentos na estrutura

## Testes Críticos
- [ ] echo "hello world"
- [ ] echo 'hello $USER' (não expandir)
- [X] ls | wc -l
- [X] echo hello > file.txt
- [ ] Syntax errors: |, >, ||

---

# Fase 3 - Variáveis

## Gerenciamento Básico
- [X] Copiar environ inicial do sistema
- [X] Implementar lista ligada própria de variáveis
- [X] Função get_env_value(key)
- [X] Função set_env_value(key, value)
- [X] Função unset_env_value(key)

## Expansão
- [X] Expandir $VARIABLE em contexto normal
- [X] Expandir $? (exit status anterior)
- [ ] NÃO expandir dentro de aspas simples
- [ ] Expandir dentro de aspas duplas
- [X] Casos especiais: $, $$, ${} se implementar

## Integração
- [X] Converter env list para array para execve()
- [X] Atualizar $? após cada comando
- [X] Sincronização com built-ins
- [ ] Testes com variáveis vazias e inexistentes

---

# Fase 4 - Built-ins

## echo
- [X] echo sem argumentos
- [X] echo com argumentos múltiplos
- [X] echo -n (sem newline)
- [X] echo -n -n -n (múltiplas flags)
- [X] echo -n hello world

## cd
- [X] cd sem argumentos (vai para $HOME)
- [ ] cd - (vai para $OLDPWD)
- [X] cd path (absoluto e relativo)
- [X] Atualizar PWD após mudança
- [ ] Atualizar OLDPWD antes da mudança

## export/unset/env
- [ ] export sem args (lista declare -x)
- [X] export VAR=value
- [ ] export VAR (criar vazia)
- [X] unset VAR
- [X] env (listar todas variáveis)
- [ ] Validar nomes de variáveis

## pwd/exit
- [X] pwd sem argumentos
- [X] exit sem argumentos
- [X] exit com número
- [X] exit com argumento inválido

---

# Fase 5 - Execução

## Resolução PATH
- [X] Buscar executável em $PATH
- [X] Tratar caminhos absolutos (/bin/ls)
- [X] Tratar caminhos relativos (./programa)
- [X] Retornar erro se comando não encontrado

## Fork e Execve
- [X] fork() para criar processo filho
- [X] execve() no filho com argumentos corretos
- [X] Converter environ para execve
- [X] Tratar erros de fork e execve

## Gerenciamento Processos
- [X] waitpid() para esperar filho
- [X] Capturar exit status com WEXITSTATUS
- [X] Atualizar $? com exit status
- [X] Evitar processos zumbi

---

# Fase 6 - Redirecionamentos

## Saída (>, >>)
- [X] Redirecionar > (truncar arquivo)
- [X] Redirecionar >> (append arquivo)
- [X] Usar dup2() para redirecionar STDOUT
- [X] Criar arquivo com permissões 644
- [X] Tratar erros de permissão

## Entrada (<)
- [X] Redirecionar < (ler de arquivo)
- [X] Usar dup2() para redirecionar STDIN
- [X] Verificar se arquivo existe
- [X] Tratar erros de leitura

## Heredoc (<<)
- [X] Ler linhas até delimiter
- [X] Criar pipe ou arquivo temporário
- [X] Redirecionar entrada do heredoc
- [ ] Tratar Ctrl+C durante heredoc
- [ ] Cleanup automático

---

# Fase 7 - Pipes

## Pipe Simples
- [X] Criar pipe com pipe()
- [X] Fork para cada comando
- [X] Conectar stdout do cmd1 com stdin do cmd2
- [X] Fechar FDs desnecessários em cada processo
- [X] Exit status = status do último comando

## Múltiplos Pipes
- [ ] Implementar pipeline de N comandos
- [ ] Gerenciar N-1 pipes para N comandos
- [ ] Coordenar fechamento de todos os FDs
- [ ] Built-ins em pipes executam em child

## Casos Complexos
- [ ] ls | cat | wc -l
- [ ] echo hello | cat > output.txt
- [ ] Pipelines com redirecionamentos
- [ ] Testar com built-ins em pipelines

---

# Fase 8 - Finalização

## Tratamento de Erros
- [ ] Mensagens consistentes com bash
- [ ] Tratar todos os códigos de erro
- [ ] Syntax errors bem formatados
- [ ] Não usar errno diretamente

## Gerenciamento Memória
- [ ] Valgrind limpo (exceto readline)
- [ ] Free todas as estruturas
- [ ] Cleanup em casos de erro
- [ ] Evitar double-free

## Testes Finais
- [ ] Comparar comportamento com bash
- [ ] Testar todos os built-ins
- [ ] Testar combinações complexas
- [ ] Testar casos extremos e edge cases
- [ ] Performance adequada

---


