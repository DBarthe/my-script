/*
** main.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <bade@epitech.net>
**
** Started on Thu Feb 20 16:35:02 2014 Barthelemy Delemotte
** Last update Fri Feb 21 13:06:09 2014 Barthelemy Delemotte
*/

#include		"myscript.h"

static void dump_opts(const t_myscript_opts *opts)
{
  printf("options :\n"
	 "  - output_file = %s\n"
	 "  - timing_file = %s\n"
	 "  - command = %s\n"
	 "  - flags :\n"
	 "    - append = %d\n"
	 "    - command = %d\n"
	 "    - return = %d\n"
	 "    - flush = %d\n"
	 "    - quiet = %d\n"
	 "    - timing = %d\n",
	 opts->output_file, opts->timing_file, opts->command,
	 opts->flags & MS_OPT_APPEND, opts->flags & MS_OPT_COMMAND,
	 opts->flags & MS_OPT_RETURN, opts->flags & MS_OPT_FLUSH,
	 opts->flags & MS_OPT_QUIET, opts->flags & MS_OPT_TIMING);
}

int			main(int ac, char **av)
{
  t_myscript_opts	opts;

  parse_opts(ac, av, &opts);
  dump_opts(&opts);
  return (myscript(&opts));
}
