# Esboço de Parser utilizando a Abstract Syntax Tree (AST)

Na pesquisa encontrei vários métodos "optimizados" para a realizacao do parsing. Visto que o **output do lexer** já **possui** uma **estrutura** que contém elementos como:
  - **Tipo** de **Token** (WORD, PIPE, REDIRECT, AND_IF, etc...)
  - **Value** (no caso de ser do tipo WORD)
  - **Was Quoted** (isto indica se o conteúdo da WORD está entre aspas. Isto é extremamente útil e será usado em casos onde **a expansão será necessária** (ex: heredoc/expander))
  - **Quote** (indica qual quote foi usada, se single quotes ou double quotes)

---

Para aproveitar essa nossa estrutura já feita, estava a pensar propor a seguinte estrutura para o parser:

```c
/*
  Esta primeira struct é muito similar á usada no lexer, porém serve para ser usada entre nodes
*/

typedef enum e_node_type
{
    NODE_CMD,       // Command
    NODE_PIPE,      // pipe |
    NODE_AND,       // AND lógico &&
    NODE_OR         // OR lógico ||
}   t_node_type;

/* 
  Esta struct t_redir aproveita o facto de termos criado/usar os tokens do lexer para descrever que tipo de redirect é.
  Assim como o ficheiro referente ao redirect, afinal, sempre depois de um redirect temos um ficheiro.
*/

typedef struct s_redir
{
    t_token_type    type;       // REDIRECT_IN, REDIRECT_OUT, etc.
    char            *filename;
    struct s_redir  *next;      // Torna-a numa linked list
}   t_redir;

/*
  Nesta struct meio "que temos meio caminho andado".
  Temos uma matriz com os argumentos necessários para enviar para o execve (que seria um dos últimos passos na execucão).
  Temos também uma linked list com a estrutura anterior para dar handle aos redirects.
*/

typedef struct s_cmd_node
{
    char            **args;     // Array de strings prontas para execve (ex: {"ls", "-l", NULL})
    t_redir         *redirs;    // Linked list com os diversos redirects necessários
}   t_cmd_node;

/*
  Esta seria a struct principal do nosso "parser em árvore".
*/

typedef struct s_parser_node
{
    t_node_type     type;
    struct s_parser_node *left;    // Filho esquerdo (para operadores binários como PIPE)
    struct s_parser_node *right;   // Filho direito

    // Dados específicos do nó (usado apenas se o type for NODE_CMD)
    t_cmd_node      *cmd_data;
}   t_ast_node;
```

### Ok, temos a struct e agora?
A ideia agora seria aplicar algo como **parsing recursivo descendente**, isso significa que devemos procurar os "tokens" com menor importancia até o mais importante.

#### Lista de prioridades
- `&&` e `||`
- `|`
- Comandos e Redirects

### Exemplo e resultado da struct com um comando de exemplo
Imaginando que temos o seguinte comando: 
```bash
cat > outfile.txt | echo "lolz" > outfile2.txt
```

Em teoria, a respresentacão em JSON do resultado depois de passar pelo parser seria o seguinte:
```json
{
  "type": "NODE_PIPE",
  "cmd_data": null,
  "left": {
    "type": "NODE_CMD",
    "left": null,
    "right": null,
    "cmd_data": {
      "args": ["cat", null],
      "redirs": [
        {
          "type": "TOKEN_REDIRECT_OUT",
          "filename": "outfile.txt",
          "next": null
        }
      ]
    }
  },
  "right": {
    "type": "NODE_CMD",
    "left": null,
    "right": null,
    "cmd_data": {
      "args": ["echo", "lolz", null],
      "redirs": [
        {
          "type": "TOKEN_REDIRECT_OUT",
          "filename": "outfile2.txt",
          "next": null
        }
      ]
    }
  }
}
```
