#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv )
{
    int status;
    char *args[4];

    args[0] = "/sbin/hdparm";        // first arg is the full path to the executable
    args[1] = "--fibmap";
    args[2] = argv[1];
    args[3] = NULL;             // list of args must be NULL terminated

    if ( fork() == 0 )
        execv( args[0], args ); // child: call execv with the path and the args
    else
        wait( &status );        // parent: wait for the child (not really necessary)

    return 0;
}
