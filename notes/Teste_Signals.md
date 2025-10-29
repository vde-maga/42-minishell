# Teste Signals

## Tabela Original

| Sinal / Ação | Cenário de Teste | Comando de Exemplo | Comportamento Esperado | Código de Saída (`echo $?`) |
| :--- | :--- | :--- | :--- | :--- |
| **`SIGINT` (Ctrl+C)** | No prompt vazio | *(Nenhum)* | Imprime uma nova linha (`^C` é opcional) e exibe um novo prompt. O shell continua a correr. | `130` |
| **`SIGINT` (Ctrl+C)** | Com texto no prompt | Digitar `ls -la` (sem Enter) | Descarta o texto digitado, imprime nova linha e exibe novo prompt. | `130` |
| **`SIGINT` (Ctrl+C)** | Durante processo *foreground* | `sleep 5` | O processo `sleep` é terminado imediatamente. O shell recupera o controlo e exibe um novo prompt. | `130` |
| **`SIGINT` (Ctrl+C)** | Durante processo bloqueado em `stdin` | `cat` | O processo `cat` é terminado imediatamente. O shell recupera o controlo e exibe um novo prompt. | `130` |
| **`SIGINT` (Ctrl+C)** | Durante a entrada de um *heredoc* | `cat << EOF` | O `heredoc` é cancelado, e o comando inteiro é abortado. O shell retorna ao prompt principal. | `130` |
| **`SIGQUIT` (Ctrl+\)** | No prompt vazio | *(Nenhum)* | **Nada acontece.** O shell em modo interativo deve ignorar este sinal completamente. | Mantém o valor anterior |
| **`SIGQUIT` (Ctrl+\)** | Durante processo *foreground* | `sleep 5` | O processo `sleep` é terminado. O shell imprime `Quit (core dumped)` e exibe um novo prompt. | `131` |
| **`EOF` (Ctrl+D)** | No prompt com linha vazia | *(Nenhum)* | **O minishell termina.** O `bash` imprime "exit" antes de sair; este comportamento é opcional. | O código de saída do shell será o do último comando executado. |
| **`EOF` (Ctrl+D)** | No prompt com texto | Digitar `echo hi` (sem Enter) | **Nada acontece.** O `Ctrl+D` é ignorado se o buffer de leitura não estiver vazio. | Mantém o valor anterior |
| **`EOF` (Ctrl+D)** | Para um processo bloqueado em `stdin` | `cat` | O `EOF` é enviado ao `stdin` do `cat`. O `cat` termina normalmente (como se o ficheiro tivesse acabado). O shell exibe novo prompt. | `0` |

---

### Notas Importantes

*   **Código de Saída:** O código de saída para um processo terminado por um sinal é `128 + número_do_sinal`.
    *   `SIGINT` é o sinal 2, logo `128 + 2 = 130`.
    *   `SIGQUIT` é o sinal 3, logo `128 + 3 = 131`.
*   **Comportamento Interativo vs. Execução:** A chave é ter handlers de sinais diferentes para quando o shell está à espera de input (interativo) e para quando um processo filho está a correr.
    *   **Interativo:** `Ctrl+C` redesenha o prompt; `Ctrl+\` é ignorado.
    *   **Execução:** Os sinais são passados ao processo filho, que reage com o seu comportamento padrão (terminar). O teu shell (pai) deve ignorar os sinais enquanto espera pelo filho para não terminar também.

## Testes

Claro, excelente ideia para acompanhar o progresso! Usar a tabela como uma checklist é a forma mais eficaz de garantir que cobres todos os casos.

Aqui está a versão atualizada da tabela com uma coluna adicional para o status do teste.

### Tabela de Testes para Signals e EOF com Checklist

| Sinal / Ação | Cenário de Teste | Comando de Exemplo | Comportamento Esperado | Código de Saída (`echo $?`) | Status (Passou?) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **`SIGINT` (Ctrl+C)** | No prompt vazio | *(Nenhum)* | Imprime nova linha (`^C` opcional) e exibe novo prompt. Shell continua a correr. | `130` | ✅ |
| **`SIGINT` (Ctrl+C)** | Com texto no prompt | Digitar `ls -la` (sem Enter) | Descarta texto, imprime nova linha e exibe novo prompt. | `130` | ✅ |
| **`SIGINT` (Ctrl+C)** | Durante processo *foreground* | `sleep 5` | Processo `sleep` termina. Shell recupera controlo e exibe novo prompt. | `130` | ✅ |
| **`SIGINT` (Ctrl+C)** | Durante processo bloqueado em `stdin` | `cat` | Processo `cat` termina. Shell recupera controlo e exibe novo prompt. | `130` | ✅ |
| **`SIGINT` (Ctrl+C)** | Durante a entrada de um *heredoc* | `cat << EOF` | *Heredoc* e comando são cancelados. Shell retorna ao prompt. | `130` | ❌ |
| **`SIGQUIT` (Ctrl+\)** | No prompt vazio | *(Nenhum)* | **Nada acontece.** O shell em modo interativo ignora este sinal. | Mantém valor anterior | ✅ |
| **`SIGQUIT` (Ctrl+\)** | Durante processo *foreground* | `sleep 5` | Processo `sleep` termina. Shell imprime `Quit (core dumped)` e exibe novo prompt. | `131` | ✅ |
| **`EOF` (Ctrl+D)** | No prompt com linha vazia | *(Nenhum)* | **O minishell termina.** (Opcional: imprimir "exit" antes de sair). | Código de saída do último comando | ✅ |
| **`EOF` (Ctrl+D)** | No prompt com texto | Digitar `echo hi` (sem Enter) | **Nada acontece.** `Ctrl+D` é ignorado se o buffer não estiver vazio. | Mantém valor anterior | ✅ |
| **`EOF` (Ctrl+D)** | Para um processo bloqueado em `stdin` | `cat` | `EOF` é enviado ao `cat`. `cat` termina normalmente. Shell exibe novo prompt. | `0` | ✅ |

---

# Teste Signals Heredocs

## Teste 1 - `cat << EOF`

```bash

cat << EOF

linha 1
linha 2

EOF

```

## Teste 2 - CTRL+C

```bash
cat << END + CTRL + C
```



