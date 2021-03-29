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
	else if(fcntl(pipefd_hpos[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}

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

			write(pipefd_rep_tur[1], &hpos, sizeof(int));
        while(1) {

      


            if(bin_hare == 1 && bin_tur == 1) {


				// if(flag == 0)
				int r = read(pipefd_hpos[0], &hpos, sizeof(int));
				printf("rv: %d\n",r);
                read(pipefd_tpos[0], &tpos, sizeof(int));
                printf("H: %d T: %d\n", hpos, tpos);

				if((hpos - tpos) >= MAX_SEP) {

                    write(pipefd_rep_hare[1], &two, sizeof(int));
					flag = 1;
                    // write(pipefd_rep_tur[1], &zero, sizeof(int));
                }
				else {
					write(pipefd_rep_hare[1], &zero, sizeof(int));
					flag = 0;
				}



                if(hpos == END) {
                    printf("Hare Won\n");
                    // write(pipefd_rep_hare[1], &t2, sizeof(int));
                    // write(pipefd_rep_tur[1], &t2, sizeof(int));
                    wait(NULL);
                    exit(0);
                }
                else if(tpos == END) {
                    printf("Hare Won\n");
                    // write(pipefd_rep_hare[1], &t2, sizeof(int));
                    // write(pipefd_rep_tur[1], &t2, sizeof(int));
                    wait(NULL);
                    exit(0);
                }



				// write(pipefd_rep_tur[1], &hpos, sizeof(int));

                // write(pipefd_rep_tur[1], &zero, sizeof(int));


            }
            
            // read(pipefd_hare_rep[0], &bin_hare, sizeof(int));

            // read(pipefd_tur_rep[0], &bin_tur, sizeof(int));

			sleep(2);
        }

		


	}

	else if(a == 0 && b > 0) { // Hare process			

	close(pipefd_rep_hare[1]); // closing write fd
	close(pipefd_hare_rep[0]); // closing read fd
	close(pipefd_hpos[0]);

	close(pipefd_tur_hare[1]);


        int hare = 0;

        int hare_bin = 0;
        int one = 1;
        int two = 2;
		int tur_pos = 0;

        while(1) {


                // while(1) {

						// int r = read(pipefd_tur_hare[0], &hare_bin, sizeof(int));
						// if(hare_bin == 1) {
						// 	continue;
						// }
                        // else if(hare_bin == 2){
                        //     write(pipefd_hare_rep[1], &one, sizeof(int));
                        //     // close(pipefd_hare_rep[1]);
                        //     sleep(2);
                        //     break;
                        // }
						// else {
						// 	break;
						// }

				// }

				// if(hare_bin == 0) {

					hare += 2;
					printf("hare pos: %d\n", hare);

					hare_bin = 1;
					write(pipefd_hare_rep[1],&hare_bin, sizeof(int));
					write(pipefd_hpos[1], &hare, sizeof(int));

					// if(hare == END) {
					// 	exit(0);
					// }
				// }

				// else {
				// 	for(int i=0;i<3;i++) {
				// 		write(pipefd_hpos[1], &hare, sizeof(int));
				// 	}
				// }


                
            

        }
	
	
	}


	else if(a > 0 && b == 0) { // Turtle process

	close(pipefd_rep_tur[1]);
	close(pipefd_tur_rep[0]);
	close(pipefd_tpos[0]);
	
	close(pipefd_tur_hare[0]);

        int turtle = 0;

        int turtle_bin = 0;

		int hare_pos = 0;

		int one = 1;

        while(1) {
            

                // while(1) {

				// 		if(turtle_bin == 1) {
				// 			continue;
				// 		}
				// 		else {
				// 			break;
				// 		}

				// }


                turtle += 1;
				printf("turtle pos: %d\n", turtle);


                // turtle_bin = 1;
                // write(pipefd_tur_rep[1],&turtle_bin, sizeof(int));
                write(pipefd_tpos[1], &turtle, sizeof(int));
				// write(pipefd_tur_hare[1], &turtle, sizeof(int));
				// int r = read(pipefd_rep_tur[0], &hare_pos, sizeof(int));

				// if((hare_pos - turtle) >= MAX_SEP) {
				// 	write(pipefd_tur_hare[1], &one, sizeof(int));
				// }

				// if(turtle == END) {
				// 	exit(0);
				// }
        }


	}

	else {
		// God Process
		
		
		

	
	}

}
