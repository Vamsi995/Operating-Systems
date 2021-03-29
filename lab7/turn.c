#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<fcntl.h> 
#include<time.h>
#define END 1000
#define MAX_SEP 50


int generate_random(int l, int r) { //this will generate random number in range l and r

      int rand_num = (rand() % (r - l + 1)) + l;
	return rand_num;
}


void parent_read(int p[], int *hpos) 
{ 
    int nread; 
    // char buf[MSGSIZE]; 
  

    while (1) { 
  
        // read call if return -1 then pipe is 
        // empty because of fcntl 
        nread = read(p[0], hpos, sizeof(int)); 
        switch (nread) { 
        case -1: 
			return;
            // case -1 means pipe is empty and errono 
            // set EAGAIN 
            // if (errno == EAGAIN) { 
            //     printf("pipe empty\n"); 
            //     // sleep(1); 
            //     break; 
            // } 
  
            // else { 
            //     perror("read"); 
            //     exit(4); 
            // } 
			
  
        // case 0 means all bytes are read and EOF(end of conv.) 
        case 0: 
            printf("End of conversation\n"); 
			break;
            // read link 
            // close(p[0]); 
  
            // exit(0); 
        // default: 
  
        //     // text read 
        //     // by default return no. of bytes 
        //     // which read call read at that time 
        //     printf(“MSG = % s\n”, buf); 
        } 
    } 
} 



int main()
{
	srand(time(0));
	int pipefd_rep_tur[2], pipefd_rep_hare[2];

	int pipefd_tur_rep[2], pipefd_hare_rep[2];

	int pipefd_tpos[2], pipefd_hpos[2];

	int pipefd_tur_hare[2];


	if(pipe(pipefd_rep_tur) == -1) {
		printf("Unable to create rep tur pipe");
		return 1;
	}
	else if(pipe(pipefd_rep_hare) == -1) {
		printf("Unable to create rep hare pipe");
		return -1;
	}
	else if(pipe(pipefd_hare_rep) == -1) {
                printf("Unable to create rep hare pipe");
                return -1;
        }
	else if(pipe(pipefd_tur_rep) == -1) {
                printf("Unable to create rep hare pipe");
                return -1;
        }
	else if(pipe(pipefd_tpos) == -1) {
                printf("Unable to create rep hare pipe");
                return -1;
        }
	else if(pipe(pipefd_hpos) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	else if(pipe(pipefd_tur_hare) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	// else if(fcntl(pipefd_hare_rep[0], F_SETFL, O_NONBLOCK)) {
	// 		printf("Unable to create rep hare pipe");
	// 		return -1;
	// }
	// else if(fcntl(pipefd_hpos[0], F_SETFL, O_NONBLOCK)) {
	// 		printf("Unable to create rep hare pipe");
	// 		return -1;
	// }

	// else if(fcntl(pipefd_tur_rep[0], F_SETFL, O_NONBLOCK)) {
	// 		printf("Unable to create rep hare pipe");
	// 		return -1;
	// }
	// else if(fcntl(pipefd_tpos[0], F_SETFL, O_NONBLOCK)) {
	// 		printf("Unable to create rep hare pipe");
	// 		return -1;
	// }




	int a = fork();
	int b = fork();

	int utime = 0;

	if(a > 0 && b > 0) {
	// Reporter process

		close(pipefd_rep_tur[0]);
		close(pipefd_rep_hare[0]);

		close(pipefd_hare_rep[1]);
		close(pipefd_tur_rep[1]);

		close(pipefd_hpos[1]);
		close(pipefd_tpos[1]);

        write(pipefd_rep_hare[1], &utime, sizeof(int));
        write(pipefd_rep_tur[1], &utime, sizeof(int));


		printf("Reporter starting the race\n");
		
        int bin_hare = 0;
        int bin_tur = 0;

        int hpos = 0;
        int tpos = 0;

        int zero = 0;
        int two = 2;

		int flag = 0;

        int turn = 0;

        while(1) {

            while(turn != 0) {
                read(pipefd_tur_rep[1], &turn, sizeof(int));
            }

            




           
        }

		


	}

	else if(a == 0 && b > 0) { // Hare process			

	close(pipefd_rep_hare[1]); // closing write fd
	close(pipefd_hare_rep[0]); // closing read fd
	close(pipefd_hpos[0]);

	close(pipefd_tur_hare[1]);


        int hare = 0;

       
        while(1) {


              


                
            

        }
	
	
	}


	else if(a > 0 && b == 0) { // Turtle process

	close(pipefd_rep_tur[1]);
	close(pipefd_tur_rep[0]);
	close(pipefd_tpos[0]);
	
	close(pipefd_tur_hare[0]);

        int turtle = 0;


        while(1) {
            

                
        }


	}

	else {
		// God Process
		
		
		

	
	}

}
