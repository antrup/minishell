/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:32:12 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/21 09:53:09 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEFINE_H
# define MS_DEFINE_H

# define WORD 0
# define OP_PIPE 1
# define OP_AND 2
# define OP_OR 3
# define COMMAND 4
# define STRING_DQ 2
# define STRING_SQ 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define REDIR_IN_A 6
# define REDIR_OUT_A 7
# define BI_ECHO 1
# define BI_CD 2
# define BI_PWD 3
# define BI_EXPORT 4
# define BI_UNSET 5
# define BI_ENV 6
# define BI_EXIT 7
# define ERR_OPEN -1
# define ERR_SYM -2

/*
** ERRORS
*/
# define ERR_SYN -1
# define ERR_TK -2
# define ERR_DQUT -3
# define ERR_SQUT -4

#endif
