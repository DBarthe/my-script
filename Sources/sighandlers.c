/*
** sighandlers.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Feb 21 12:39:23 2014 Barthelemy Delemotte
** Last update Fri Feb 21 16:19:30 2014 Barthelemy Delemotte
*/

#include		<signal.h>
#include		<sys/wait.h>
#include		<sys/ioctl.h>

#include		"myscript.h"

void			sigchild_handler(__attribute__((__unused__))
					 int signum)
{
  int			status;

  signal(SIGCHLD, &sigchild_handler);
  if (waitpid(g_myscript_vars.slave_pid, &status, WNOHANG) > 0)
    {
      if (WIFEXITED(status))
	g_myscript_vars.ret = WEXITSTATUS(status);
      g_myscript_vars.slave_pid = -1;
    }
}

void			sigwinch_handler(__attribute__((__unused__))
					 int signum)
{
  struct winsize	ws;

  signal(SIGWINCH, &sigwinch_handler);
  ioctl(1, TIOCGWINSZ, &ws);
  ioctl(g_myscript_vars.master_fd, TIOCSWINSZ, &ws);
}
