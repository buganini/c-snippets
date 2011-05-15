#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/*
 * sh evuivalent:
 * sh -c 'kill -SIGTERM `ps -p $$ -o ppid=`'
*/

int main(int argc, char *argv[]){
	kill(getppid(), SIGTERM);
	return 0;
}
