/*
** print.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Feb 21 17:21:30 2014 Barthelemy Delemotte
** Last update Fri Feb 21 18:40:05 2014 Barthelemy Delemotte
*/

#include		<time.h>

#include		"myscript.h"

void			print_start(t_myscript_opts *opts)
{
  time_t		t;

  if (!(opts->flags & MS_OPT_QUIET))
    printf("The script has started, the file is %s\n", opts->output_file);
  t = time(NULL);
  fprintf(g_myscript_vars.output, "The script has started at %s", ctime(&t));
  fflush(g_myscript_vars.output);
}

void			print_end(t_myscript_opts *opts)
{
  time_t		t;

  if (!(opts->flags & MS_OPT_QUIET))
    printf("Script terminated, the file is %s\n", opts->output_file);
  t = time(NULL);
  fprintf(g_myscript_vars.output, "\nScript terminated at %s", ctime(&t));
}

void			print_timing(t_myscript_opts *opts, size_t size)
{
  struct timeval	t;
  struct timeval	diff_time;
  float			seconds;

  if (opts->flags & MS_OPT_TIMING)
    {
      gettimeofday(&t, NULL);
      timersub(&t, &g_myscript_vars.last_time, &diff_time);
      seconds = (float)diff_time.tv_sec +
	(float)diff_time.tv_usec / 1000000.0F;
      if (fprintf(g_myscript_vars.timing, "%f %lu\n", seconds, size) < 0)
	die(opts->timing_file);
      if (opts->flags & MS_OPT_FLUSH)
	fflush(g_myscript_vars.timing);
      g_myscript_vars.last_time = t;
    }
}
