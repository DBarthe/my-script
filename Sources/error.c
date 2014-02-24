/*
** error.c for myscript in /home/bade/Dev/tek2/Unix/PSU_2013_myscript/Includes
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Mon Feb 24 11:35:34 2014 Barthelemy Delemotte
** Last update Mon Feb 24 11:37:31 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<unistd.h>

#include		"myscript.h"

void			die(const char *s)
{
  if (s)
    perror(s);
  exit(EXIT_FAILURE);
}

void			error_usage(const char *msg, const char *token)
{
  fprintf(stderr, "myscript: %s", msg);
  if (token)
    fprintf(stderr, " -- '%s'", token);
  fprintf(stderr, "\n\n");
  usage(stderr);
  exit(EXIT_FAILURE);
}

int			error_close(int fd)
{
  close(fd);
  return (-1);
}
