#pragma once
#ifndef GETOPT_H
#define GETOPT_H

// Put this into its own namespace to disambiguate from globals.
namespace parsing
{
	extern char	*optarg;	/* Global argument pointer. */
	extern int	optind;	/* Global argv index. */

						/// Function to parse a command line argument.
	int getopt(int argc, char *argv[], const char *optstring);
}

#endif /* GETOPT_H */