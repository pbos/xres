// xres - Print X Display Resolution
// Written by Peter Boström, 2009.
// No Rights Reserved

#include <X11/Xlib.h>
#include <stdio.h>

char *help = "\
Usage:  xres \n\
	xres [-adr]...\n\
\n\
Print display information (resolution by default).\n\
\n\
  -a        print ALL info, same as -dr\n\
  -d        print display name\n\
  -r        print display resolution\n\
\n\
  --help    display this help and exit\n\
";


void print_help()
{
	printf("%s", help);
}

int main(int argc, char *argv[])
{
	char *prog = argv[0];

	unsigned char print_flags = 0;

	#define FLAG_DISPLAY		0x02
	#define FLAG_RESOLUTION		0x01

	#define FLAG_ALL 		(FLAG_DISPLAY | FLAG_RESOLUTION)

	int i, j;

	for(i = 1; i < argc; ++i)
	{
		if(argv[i][0] == '-')
		{
			if(argv[i][1] == '\0')
			{
				print_help();
				return -1;
			}

			j = 1;
			do{
				switch(argv[i][j])
				{
					case 'a':
						print_flags |= FLAG_ALL;
						break;
					case 'd':
						print_flags |= FLAG_DISPLAY;
						break;
					case 'r':
						print_flags |= FLAG_RESOLUTION;
						break;
					default:
						print_help();
						return -1;
				}
				++j;
			} while(argv[i][j] != '\0');
		}
		else
		{
			print_help();
			return -1;
		}
	}

	if(print_flags == 0)
		print_flags = FLAG_RESOLUTION;

	char *display_name = NULL;
	Display *display;

	if((display = XOpenDisplay(display_name)) == NULL)
	{
		fprintf(stderr, "%s: cannot connect to X server (%s)\n", argv[0], XDisplayName(display_name));
		return -1;
	}

	if(print_flags & FLAG_DISPLAY)
	{
		printf("%s", DisplayString(display));
		if(print_flags != FLAG_DISPLAY)
			putchar(' ');
		else
			putchar('\n');
	}

	if(print_flags & FLAG_RESOLUTION)
	{
		int screen_num = DefaultScreen(display);
		printf("%dx%d\n", DisplayWidth(display, screen_num), DisplayHeight(display, screen_num));
	}

	return 0;
}

