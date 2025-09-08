/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:31 by ruiferna          #+#    #+#             */
/*   Updated: 2025/09/08 18:31:40 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "42_libft/libft.h"
# include "42_ft_printf/ft_printf.h"
# include "42_get_next_line/get_next_line.h"
# include "structs.h"
# include "lexer.h"
# include "wrappers.h"

# include <stdio.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>

char    *get_str_readline(void);

#endif