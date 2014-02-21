/*
** myscript.h for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb 20 16:06:44 2014 Barthelemy Delemotte
** Last update Fri Feb 21 16:22:30 2014 Barthelemy Delemotte
*/

#ifndef			MYSCRIPT_H_
# define		MYSCRIPT_H_

# include		<stdio.h>
# include		<termios.h>
# include		<sys/ioctl.h>

typedef	struct
{
  char			*output_file;
  char			*timing_file;
  char			*command;
  enum
    {
      MS_OPT_APPEND	= 0x1,
      MS_OPT_COMMAND 	= 0x2,
      MS_OPT_RETURN	= 0x4,
      MS_OPT_FLUSH	= 0x8,
      MS_OPT_QUIET	= 0x10,
      MS_OPT_TIMING	= 0x20
    }			flags;
}			t_myscript_opts;

struct
{
  int			master_fd;
  pid_t			slave_pid;
  FILE			*output;
  int			ret;
  struct termios	original_term;
}			g_myscript_vars;

# define		BUFFER_SIZE	4096

int			myscript(t_myscript_opts *opts);
int			master(t_myscript_opts *opts);

void			die(const char *s);
void			reset_term(void);
void			close_output(void);

void			sigchild_handler(int signum);
void			sigwinch_handler(int signum);

int			parse_opts(int ac, char **av, t_myscript_opts *opts);

pid_t			myforkpty(int *amaster, char *name,
				  struct termios *termp,
				  struct winsize *winp);

#endif /* MYSCRIPT_H_ */
