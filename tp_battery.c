/** tp_battery, a small battery indicator
 *  for use in the wmii statusbar.
 *
 * Copyright © 2010 by Thomas Roth <code@leveldown.de>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Configuration: */
#define SHOW_PERCENTAGE
#define SHOW_BAR
#define SHOW_AC

#define AC_YES     "+"
#define AC_NO      "-"
#define BAR_LENGTH 10
#define BAR_FRONT  " ["
#define BAR_REAR   "]"
#define BAR_FILL   "#"
#define BAR_BLANK  " "
/* End Configuration */

inline void show_bar(int energy_blocks) {
	int i;
	printf(BAR_FRONT);
	for(i=0;i<energy_blocks;i++) {
		printf(BAR_FILL);
	}
	for(;i<BAR_LENGTH;i++) {
		printf(BAR_BLANK);
	}
	printf(BAR_REAR);
}

int main(int argc, char *argv[])
{
	if((argc < 3) || (argc > 4)) {
		printf("Usage:   %s [energy now] [energy full] (ac)\n"
		       "Example: %s 123 456 1\n", argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned int energy_now;
	unsigned int energy_full;

	if(sscanf(argv[1], "%d", &energy_now) != 1) {
		printf("Error: Argument 1: %s is not an integer.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(sscanf(argv[2], "%d", &energy_full) != 1) {
		printf("Error: Argument 2: %s is not an integer.\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	#ifdef SHOW_AC
		if(argv[3]) {
			int ac;
			if(sscanf(argv[3], "%d", &ac) != 1) {
				printf("Error: Argument 3: %s is not an integer.\n", argv[3]);
				exit(EXIT_FAILURE);
			}
			printf("%s", ac > 0 ? AC_YES : AC_NO);
		}
	#endif

	#ifdef SHOW_PERCENTAGE
		float energy_percentage = ((float)energy_now / (float)energy_full) * 100.0;
		printf("%.0f%%", energy_percentage);
	#endif

	#ifdef SHOW_BAR
		int energy_blocks = (int)round((float)energy_now / ((float)energy_full / (float)BAR_LENGTH));
		show_bar(energy_blocks);
	#endif
}
