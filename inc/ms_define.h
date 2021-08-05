/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:32:12 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/05 07:55:28 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEFINE_H
# define MS_DEFINE_H

//# define environ g_shell.env

/*
** TOKEN TYPES
*/
# define WORD 0
# define OP_PIPE 1
# define OP_AND 2
# define OP_OR 3
# define STRING_DQ 2
# define STRING_SQ 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define REDIR_IN_A 6
# define REDIR_OUT_A 7
/*
** BUILT IN FUNCTIONS
*/
# define BI_CD 1
# define BI_ECHO 2
# define BI_PWD 3
# define BI_EXPORT 4
# define BI_UNSET 5
# define BI_ENV 6
# define BI_EXIT 7
/** ERRORS
*/
# define ERR_SYN -1
# define ERR_TK -2
# define ERR_DQUT -3
# define ERR_SQUT -4
# define ERR_OPEN -5
# define ERR_PIPE -6
# define ERR_WRT -7
# define ERR_READ -8
# define ERR_REDIR_IN 9
# define ERR_CD -10
# define ERR_MEM -11
# define ERR_PAREN -12

# define KEY_NONE 0
# define KEY_CTRL_C 3
# define KEY_CTRL_D 4 

/*
** WILDCARD
*/

# define OP_WCARD 1
# define OP_STERM 2
# define OP_FAIL_ 0

/*
** CD BUILDIN CONSTANTS
*/

# define CD_NONE 0
# define CD_HOME 1
# define CD_UP_ONE 2
# define CD_CURRENT 3
# define CD_RELATIVE 4
# define CD_BACK 5
# define CD_CURRENT_R 6
# define CD_NOT 7
# define CD_RELATIVE_R 8

/*
** BUILT IN COMMANDS
*/

#endif
