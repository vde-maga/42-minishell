/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:27:52 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:43:45 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structs.h"

// envp_to_env_struct.c
t_env	*ft_env_create_node(char *envp_line);
t_env	**ft_env_to_array(t_env *env_list, int count);
char	**ft_env_list_to_array(t_env *env_list);

// free.c
void	ft_free_env_list(t_env *head);

// getters.c
t_env	*ft_get_env_list(char **envp);
t_env	*ft_get_env_var(t_env *env_list, char *var_name);
int		ft_env_count_vars(t_env *env_list);

// setters.c
void	ft_env_add_back(t_env **lst, t_env *new_node);
int		ft_update_env_var(t_env *env_list, char *var_name, char *new_value);
int		ft_set_env_var(t_env **env_list, char *var_name, char *value);
int		ft_unset_env_var(t_env **env_list, char *var_name);

#endif
