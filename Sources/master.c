/*
** master.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Feb 21 12:25:56 2014 Barthelemy Delemotte
** Last update Fri Feb 21 18:39:53 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<assert.h>
#include		<signal.h>
#include		<string.h>
#include		<unistd.h>
#include		<fcntl.h>
#include		<time.h>
#include		<sys/select.h>
#include		<sys/types.h>
#include		<sys/wait.h>

#include		"myscript.h"

static void		master_open_outputs(t_myscript_opts *opts)
{
  g_myscript_vars.output =
    fopen(opts->output_file, opts->flags & MS_OPT_APPEND ? "a" : "w");
  if (!g_myscript_vars.output)
    die("typescript");
  atexit(&close_output);
  if (opts->flags & MS_OPT_TIMING)
    {
      g_myscript_vars.timing =
	fopen(opts->timing_file, opts->flags & MS_OPT_APPEND ? "a" : "w");
      if (!g_myscript_vars.timing)
	die(opts->timing_file);
      atexit(&close_timing);
      gettimeofday(&g_myscript_vars.last_time, NULL);
    }
}

static void		master_init(t_myscript_opts *opts, fd_set *fds)
{
  struct termios	t;

  signal(SIGCHLD, &sigchild_handler);
  signal(SIGWINCH, &sigwinch_handler);
  FD_ZERO(fds);
  FD_SET(0, fds);
  FD_SET(g_myscript_vars.master_fd, fds);
  master_open_outputs(opts);
  if (tcgetattr(0, &t) == -1)
    die("tcgetattr");
  g_myscript_vars.original_term = t;
  atexit(&reset_term);
  t.c_lflag &= ~(ICANON | ISIG | ECHO);
  t.c_cc[VMIN] = 1;
  t.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &t))
    die("tcsetattr");
  print_start(opts);
}

static void		master_record(t_myscript_opts *opts,
				      const char *buffer,
				      size_t size)
{
  if (!fwrite(buffer, sizeof(char), size, g_myscript_vars.output))
    die(opts->output_file);
  if (opts->flags & MS_OPT_FLUSH)
    fflush(g_myscript_vars.output);
  if (opts->flags & MS_OPT_TIMING)
    print_timing(opts, size);
}

static void		master_loop(t_myscript_opts *opts)
{
  fd_set		original_fds;
  fd_set		current_fds;
  int			master_fd;
  ssize_t		ret;
  char			buffer[BUFFER_SIZE];

  master_fd = g_myscript_vars.master_fd;
  master_init(opts, &original_fds);
  while (g_myscript_vars.slave_pid != -1)
    {
      memcpy(&current_fds, &original_fds, sizeof(fd_set));
      if (select(master_fd + 1, &current_fds, NULL, NULL, NULL) == -1)
	continue;
      if (FD_ISSET(0, &current_fds) &&
	  (ret = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
	write(master_fd, buffer, ret);
      if (FD_ISSET(master_fd, &current_fds) &&
	  (ret = read(master_fd, buffer, BUFFER_SIZE)) > 0)
	{
	  write(STDOUT_FILENO, buffer, ret);
	  master_record(opts, buffer, (size_t)ret);
	}
    }
}

int			master(t_myscript_opts *opts)
{
  master_loop(opts);
  print_end(opts);
  return (opts->flags & MS_OPT_RETURN ?
	  g_myscript_vars.ret : EXIT_SUCCESS);
}
