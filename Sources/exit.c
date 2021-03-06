/*
** exit.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Feb 21 12:33:49 2014 Barthelemy Delemotte
** Last update Fri Feb 28 18:02:54 2014 Barthelemy Delemotte
*/

#include		<stdio.h>
#include		<termios.h>

#include		"myscript.h"

void			reset_term(void)
{
  tcsetattr(0, TCSANOW, &g_myscript_vars.original_term);
}

void			close_output(void)
{
  fflush(g_myscript_vars.output);
  fclose(g_myscript_vars.output);
}

void			close_timing(void)
{
  fflush(g_myscript_vars.timing);
  fclose(g_myscript_vars.timing);
}
