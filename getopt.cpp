/*
* getopt - get option letter from argv
*/
#include "stdafx.h"
#include <stdio.h>
#include <string>

static char	*scan = 0;	/* Private scan pointer. */

extern char	*index();

namespace parsing {
	char	*optarg;	/* Global argument pointer. */
	int	optind = 0;	/* Global argv index. */

	int
		getopt(int argc, char *argv[], const char *optstring)
	{
		register char c;
		register const char *place;

		optarg = 0;

		if (scan == 0 || *scan == '\0') {
			if (optind == 0)
				optind++;

			if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0')
				return(EOF);
			if (strcmp(argv[optind], "--") == 0) {
				optind++;
				return(EOF);
			}

			scan = argv[optind] + 1;
			optind++;
		}

		c = *scan++;
		place = strchr(optstring, c);

		if (place == 0 || c == ':') {
			fprintf(stderr, "%s: unknown option -%c\n", argv[0], c);
			return('?');
		}

		place++;
		if (*place == ':') {
			if (*scan != '\0') {
				optarg = scan;
				scan = 0;
			}
			else if (optind < argc) {
				optarg = argv[optind];
				optind++;
			}
			else {
				fprintf(stderr, "%s: -%c argument missing\n", argv[0], c);
				return('?');
			}
		}

		return(c);
	}
}