/*
** mypty.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <bade@epitech.net>
**
** Started on Fri Feb 21 13:13:40 2014 Barthelemy Delemotte
** Last update Fri Feb 21 18:47:22 2014 Barthelemy Delemotte
*/

#define			_XOPEN_SOURCE

#include		<pty.h>
#include		<utmp.h>
#include		<stdlib.h>

#include		<string.h>
#include		<termios.h>
#include		<unistd.h>
#include		<fcntl.h>
#include		<sys/ioctl.h>

#include		"myscript.h"

static int		error_close(int fd)
{
  close(fd);
  return (-1);
}

static int		myunlockpt(int fd)
{
  int			unlock;

  unlock = 0;
  return (ioctl(fd, TIOCSPTLCK, &unlock));
}

static int		myopenpty(int *amaster, int *aslave, char *name,
				  struct termios *termp,
				  struct winsize *winp)
{
  char			*pts_name;

  if ((*amaster = open("/dev/ptmx", O_RDWR | O_NOCTTY)) == -1)
    return (-1);
  if (myunlockpt(*amaster) == -1)
    return (error_close(*amaster));
  if ((pts_name = ptsname(*amaster)) == NULL)
    return (error_close(*amaster));
  if (name)
    strcpy(name, pts_name);
  if ((*aslave = open(pts_name, O_RDWR)) == -1)
    return (error_close(*amaster));
  if (termp && tcgetattr(0, termp) != -1)
    tcsetattr(1, TCSANOW, termp);
  if (winp && ioctl(1, TIOCGWINSZ, winp) != -1)
    ioctl(g_myscript_vars.master_fd, TIOCSWINSZ, winp);
  return (0);
}

static int		mylogin_tty(int fd)
{
  setsid();
  if (ioctl(fd, TIOCSCTTY, NULL) == -1)
    return (-1);
  if (dup2(fd, 0) == -1 ||
      dup2(fd, 1) == -1 ||
      dup2(fd, 2) == -1)
    return (-1);
  if (fd > 2)
    close(fd);
  return (0);
}

pid_t			myforkpty(int *amaster, char *name,
				  struct termios *termp,
				  struct winsize *winp)
{
  int			slave;
  pid_t			pid;

  if (myopenpty(amaster, &slave, name, termp, winp) == -1)
    return (-1);
  if ((pid = fork()) == -1)
    return (-1);
  if (pid == 0)
    {
      if (mylogin_tty(slave) == -1)
	return (-1);
      close(*amaster);
    }
  return (pid);
}
