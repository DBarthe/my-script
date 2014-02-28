/*
** myscript.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb 20 16:44:52 2014 Barthelemy Delemotte
** Last update Fri Feb 28 19:37:16 2014 Barthelemy Delemotte
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
#include		<sys/ioctl.h>

#include		"myscript.h"

static void		slave(t_myscript_opts *opts)
{
  char			*shell;

  shell = getenv("SHELL");
  if (!shell || !*shell)
    shell = "/bin/sh";
  if (opts->flags & MS_OPT_COMMAND)
    execl(shell, shell, "-c", opts->command, NULL);
  else
    execl(shell, shell, NULL);
  perror("execl");
}

int			myscript(t_myscript_opts *opts)
{
  pid_t			pid;
  struct winsize	ws;
  struct termios	term;

  memset(&g_myscript_vars, 0, sizeof(g_myscript_vars));
  pid = myforkpty(&g_myscript_vars.master_fd, NULL, &term, &ws);
  if (pid == -1)
    die("forkpty");
  if (pid == 0)
    {
      slave(opts);
      assert(1);
    }
  g_myscript_vars.slave_pid = pid;
  g_myscript_vars.ret = EXIT_SUCCESS;
  return (master(opts));
}
