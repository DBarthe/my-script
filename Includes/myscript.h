/*
** myscript.h for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb 20 16:06:44 2014 Barthelemy Delemotte
** Last update Fri Feb 28 19:13:04 2014 Barthelemy Delemotte
*/

#ifndef			MYSCRIPT_H_
# define		MYSCRIPT_H_

# include		<stdio.h>
# include		<termios.h>
# include		<sys/time.h>
# include		<sys/ioctl.h>

# define		BUFFER_SIZE	4096
# define		DEVPT_PATH	"/dev/pts/"

typedef	struct
{
  char			*output_file;
  char			*timing_file;
  char			*command;
  enum
    {
      MS_OPT_APPEND	= 0x1,
      MS_OPT_COMMAND	= 0x2,
      MS_OPT_RETURN	= 0x4,
      MS_OPT_FLUSH	= 0x8,
      MS_OPT_QUIET	= 0x10,
      MS_OPT_TIMING	= 0x20
    }			flags;
}			t_myscript_opts;

typedef	struct
{
  struct termios	*termp;
  struct winsize	*winp;
}			t_term;

struct
{
  int			master_fd;
  pid_t			slave_pid;
  FILE			*output;
  FILE			*timing;
  struct timeval	last_time;
  int			ret;
  struct termios	original_term;
}			g_myscript_vars;

/*
** myscript.c
*/
int			myscript(t_myscript_opts *opts);

/*
** mater.c
*/
int			master(t_myscript_opts *opts);

/*
** exit.c
*/
void			reset_term(void);
void			close_output(void);
void			close_timing(void);

/*
** error.c
*/
void			die(const char *s);
void			error_usage(const char *msg, const char *token);
int			error_close(int fd);

/*
** sighandlers.c
*/
void			sigchild_handler(int signum);
void			sigwinch_handler(int signum);

/*
** options.c
*/
int			parse_opts(int ac, char **av, t_myscript_opts *opts);
void			usage(FILE *stream);

/*
** mypty.c
*/
pid_t			myforkpty(int *amaster, char *name,
				  struct termios *termp,
				  struct winsize *winp);

/*
** print.c
*/
void			print_start(t_myscript_opts *opts);
void			print_end(t_myscript_opts *opts);
void			print_timing(t_myscript_opts *opts, size_t size);

#endif /* MYSCRIPT_H_ */
