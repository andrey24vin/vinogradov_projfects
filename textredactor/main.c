#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

//#define CTRL_KEY(k) ((k) & 0x1f)
struct termios orig_termios;

void disableRawMode()
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode()
{
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw=orig_termios;
  raw.c_lflag &= ~(ECHO|ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main()
{
  char c;
  while (read(STDIN_FILENO,&c,1)==1 && c !='q')
  {
    if(iscntrl(c))
    {
      printf("%d\n",c);
    } else {
      printf("%d ('%c')\n", c,c);
      }
  //if (c==CTRL_KEY('q'))break;
  }
  return 0;
}
