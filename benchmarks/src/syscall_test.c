/*******************************************************************************
 *  The BYTE UNIX Benchmarks - Release 3
 *          Module: syscall.c   SID: 3.3 5/15/91 19:30:21
 *
 *******************************************************************************
 * Bug reports, patches, comments, suggestions should be sent to:
 *
 *	Ben Smith, Rick Grehan or Tom Yager at BYTE Magazine
 *	ben@bytepb.byte.com   rick_g@bytepb.byte.com   tyager@bytepb.byte.com
 *
 *******************************************************************************
 *  Modification Log:
 *  $Header: syscall.c,v 3.4 87/06/22 14:32:54 kjmcdonell Beta $
 *  August 29, 1990 - Modified timing routines
 *  October 22, 1997 - code cleanup to remove ANSI C compiler warnings
 *                     Andy Kahn <kahn@zk3.dec.com>
 *
 ******************************************************************************/
/*
 *  syscall  -- sit in a loop calling the system
 *
 */
char SCCSid[] = "@(#) @(#)syscall.c:3.3 -- 5/15/91 19:30:21";

#include <stdio.h>
// #include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

unsigned long iter;

void report()
{
	printf(2,"COUNT|%ld|1|lps\n", iter);
	exit(0);
}

int main(argc, argv)
int	argc;
char	*argv[];
{
        char   *test;
        test = "mix";
        iter = 0;

        switch (test[0]) {
        case 'm':
            while (iter <= 1000000l) {
                close(dup(0));
                getpid();
                // getuid();
		// umask(022);
                iter++;
            }
            break;
            /* NOTREACHED */
        case 'c':
           while (1) {
                close(dup(0));
                iter++;
           }
           /* NOTREACHED */
        case 'g':
           while (1) {
                getpid();
                iter++;
           }
           /* NOTREACHED */
        case 'e':
           while (1) {
                pid_t pid = fork();
                if (pid < 0) {
                    printf(2,"%s: fork failed\n", argv[0]);
                    exit(1);
                } else if (pid == 0) {
                    exec("/bin/true", (char *) 0);
                    printf(2,"%s: exec /bin/true failed\n", argv[0]);
                    exit(1);
                } else {
                    //if (waitpid(pid, NULL, 0) < 0) {
		    if(wait() < 0){
                        printf(2,"%s: waitpid failed\n", argv[0]);
                        exit(1);
                    }
                }
                iter++;
           }
           /* NOTREACHED */
        }

        exit(9);
}
