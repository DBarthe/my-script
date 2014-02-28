/*
** main.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb 20 16:35:02 2014 Barthelemy Delemotte
** Last update Fri Feb 28 18:03:48 2014 Barthelemy Delemotte
*/

#include		"myscript.h"

int			main(int ac, char **av)
{
  t_myscript_opts	opts;

  parse_opts(ac, av, &opts);
  return (myscript(&opts));
}
