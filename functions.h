#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <sys/msg.h>
#include <omp.h>
static struct termios orig_term;
void u_cleanup(void)
{
tcsetattr(0, TCSANOW, &orig_term);
}
void die(char *str) {
perror(str);
exit(1);
}
int u_kbhit()
{
struct termios t;
int ret;
fd_set rfd;
struct timeval to;
static int first_hit=0;

if(first_hit==0)
{
if(tcgetattr(0, &t)!=0) exit(0);
orig_term=t;
cfmakeraw(&t);
if(tcsetattr(0, TCSANOW, &t)!=0) exit(0);
atexit(u_cleanup);
first_hit=1;
}

FD_ZERO(&rfd);
FD_SET(0, &rfd);
to.tv_sec=0;
to.tv_usec=0;
if(select(1, &rfd, NULL, NULL, &to)==1) return 1;
return 0;
}

int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
int getche(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
