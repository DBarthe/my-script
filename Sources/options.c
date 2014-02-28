/*
** options.c for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript/Sources
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Feb 21 13:01:45 2014 Barthelemy Delemotte
** Last update Fri Feb 28 19:41:06 2014 Barthelemy Delemotte
*/

#include		<string.h>
#include		<stdlib.h>
#include		<stdio.h>

#include		"myscript.h"

static int		is_opt(const char *arg, char c, const char *s)
{
  if (arg[0] == '-')
    return (strcmp(arg + 1, s) == 0);
  while (*arg)
    {
      if (*arg == c)
	return (1);
      arg++;
    }
  return (0);
}

void			usage(FILE *stream)
{
  fprintf(stream, "Usage :\n  my_script [options] [file]\n\n");
  fprintf(stream, "Options :\n");
  fprintf(stream, " -a, --append             append to the output file\n");
  fprintf(stream, " -c, --command <command>  execute the command, "
	  "not a shell\n");
  fprintf(stream, " -e, --return             return the exit code of the"
	  " child process\n");
  fprintf(stream, " -f, --flush              flush after each writting\n");
  fprintf(stream, " -q, --quiet              silence mode\n");
  fprintf(stream, " -t, --timing <file>      output timing data to standard "
	  "error\n");
  fprintf(stream, " -h, --help               display this help\n");
  fprintf(stream, "\n");
}

static int		fascist_epitech_norm(int ac, char **av, int *i,
					     t_myscript_opts *opts)
{
  int			ret;

  ret = 0;
  if (is_opt(av[*i] + 1, 't', "timing"))
    {
      if (++(*i) >= ac)
	error_usage("missing filename after option", "t");
      opts->flags |= MS_OPT_TIMING;
      opts->timing_file = av[*i];
      ret++;
    }
  else if (is_opt(av[*i] + 1, 'c', "command"))
    {
      opts->flags |= MS_OPT_COMMAND;
      if (++(*i) >= ac)
	error_usage("missing command after option", "c");
      opts->command = av[*i];
      ret++;
    }
  return (ret);
}

static int		treat_opt(int ac, char **av, int *i,
				  t_myscript_opts *opts)
{
  int			ret;

  ret = 0;
  if (is_opt(av[*i] + 1, 'a', "append") && ++ret)
    opts->flags |= MS_OPT_APPEND;
  if (is_opt(av[*i] + 1, 'e', "return") && ++ret)
    opts->flags |= MS_OPT_RETURN;
  if (is_opt(av[*i] + 1, 'f', "flush") && ++ret)
    opts->flags |= MS_OPT_FLUSH;
  if (is_opt(av[*i] + 1, 'q', "quiet") && ++ret)
    opts->flags |= MS_OPT_QUIET;
  if (is_opt(av[*i] + 1, 'h', "help") && ++ret)
    {
      usage(stdout);
      exit(EXIT_SUCCESS);
    }
  ret += fascist_epitech_norm(ac, av, i, opts);
  return (ret ? 0 : -1);
}

int			parse_opts(int ac, char **av, t_myscript_opts *opts)
{
  int			i;

  memset(opts, 0, sizeof(t_myscript_opts));
  i = 0;
  while (++i < ac)
    {
      if (av[i][0] == '-')
	{
	  if (treat_opt(ac, av, &i, opts) == -1)
	    error_usage("invalid option", av[i] + 1);
	}
      else if (opts->output_file)
	error_usage("syntax error", NULL);
      else
	opts->output_file = av[i];
    }
  if (!opts->output_file)
    opts->output_file = "typescript";
  return (0);
}
