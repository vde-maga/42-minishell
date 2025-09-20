#ifndef COLORS_H
# define COLORS_H

/*
    Readline is a kind of strange library, so, to color the prompt,
    we need to wrap the ANSI code with \001 and \002
*/
# define RL_BOLD_RED   "\001\x1b[1;31m\002"
# define RL_BLUE       "\001\x1b[34m\002"
# define RL_GREEN      "\001\x1b[32m\002"
# define RL_YELLOW     "\001\x1b[33m\002"
# define RL_RESET      "\001\x1b[0m\002"

# define ANSI_BOLD_RED "\x1b[1;31m"
# define ANSI_BLUE     "\x1b[34m"
# define ANSI_GREEN    "\x1b[32m"
# define ANSI_YELLOW   "\x1b[33m"
# define ANSI_RESET    "\x1b[0m"

#endif
