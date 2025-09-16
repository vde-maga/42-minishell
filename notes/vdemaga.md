# Armazenar a envp, numa linked list

> envp todo numa linked list que estara na struct do minishell

```c
typedef struct s_env
{                                                                               
	char *var;                                                              
	char *value;                                                            
	s_env next;                                                                                 
}	t_env;
```

Para tal, eu preciso de

1. Mandar o envp para uma funcao
2. Percorrer o envp
3. Fazer um split, onde o separador e o `=`
	1. Com base no comando `env` no terminal
	2. Var = MAIL
	3. value = vde-maga@student.42porto.com

# Expander


> sanitize do conteudo recebido pelo lexer ("" e '')
>
> Substituir o conteudo dentro de aspas, pelo verdadeiro `env`


- criar funcao para dar parse
	- detetar as path variables (envp)
- se detetar $, checkar o proximo


