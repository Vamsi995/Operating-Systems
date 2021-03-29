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

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}


int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}


int main()
{
	srand(time(0));
	int pipefd_rep_tur[2], pipefd_rep_hare[2];

	int pipefd_tur_rep[2], pipefd_hare_rep[2];

	int pipefd_tpos[2], pipefd_hpos[2];

	int pipefd_god_tur[2], pipefd_god_hare[2];

	int pipefd_god_rep[2], god_rep_exit[2];

    int pipefd_god_hare_wakeup[2];

    int pipefd_hare_rep2[2];

    int god_sync_hare[2], god_sync_tur[2];


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
	else if(pipe(pipefd_god_hare) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	else if(pipe(pipefd_god_tur) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	else if(pipe(pipefd_god_rep) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(pipe(pipefd_god_hare_wakeup) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(pipe(pipefd_hare_rep2) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(pipe(god_sync_hare) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(pipe(god_sync_tur) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(pipe(god_rep_exit) == -1) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	else if(fcntl(pipefd_god_tur[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(fcntl(god_rep_exit[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	else if(fcntl(pipefd_god_hare[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(fcntl(pipefd_god_hare_wakeup[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
    else if(fcntl(pipefd_god_rep[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
  




	int a = fork();
	int b = fork();

	int utime = 0;

	if(a > 0 && b > 0) {
	// Reporter process

		int a = 1;
		int b = 1;

		close(pipefd_rep_tur[0]);
		close(pipefd_rep_hare[0]);

		close(pipefd_hare_rep[1]);
		close(pipefd_tur_rep[1]);

		close(pipefd_hpos[1]);
		close(pipefd_tpos[1]);

		close(pipefd_god_rep[1]);
        close(pipefd_hare_rep2[0]);

        close(god_sync_hare[1]);
        close(god_sync_tur[1]);
        close(god_rep_exit[0]);


		printf("Reporter starting the race\n");
		
        int hare_c = 0;
        int tur_c = 0;

        int hpos = 0;
        int tpos = 0;

        int zero = 0;
        int one = 1;
        int two = 2;
        int three = 3;
        int four = 4;

        int neg = -1;
        int godpos = -1;
        int temp;

        int sync_tur = 0;
        int sync_hare = 0;
				
		while(1) {

            while(1) {

                read(pipefd_hare_rep[0], &hare_c, sizeof(int));
                read(pipefd_tur_rep[0], &tur_c, sizeof(int));
                

                if(hare_c == 3){

                    read(pipefd_god_rep[0], &godpos, sizeof(int));

                    write(pipefd_hare_rep2[1], &neg, sizeof(int));

                    

                    if(godpos > 0) {

                        write(pipefd_hare_rep2[1], &godpos, sizeof(int));
                        write(pipefd_rep_tur[1], &three, sizeof(int));
                       
                        printf("God is repositioning hare and turtle\n");
                      
                        hpos = godpos;

                        read(god_sync_hare[0], &sync_hare, sizeof(int));
                        read(god_sync_tur[0], &sync_tur, sizeof(int));

                        if(sync_hare == 1 && sync_tur == 1){
                            godpos = -1;

                            sync_hare = 0;
                            sync_tur = 0;

                             write(pipefd_rep_hare[1], &zero, sizeof(int));
                             write(pipefd_rep_tur[1], &zero, sizeof(int));


                            while(1) {
                                read(pipefd_hare_rep[0], &hare_c, sizeof(int));

                                if(hare_c == 1) {
                                    break;
                                }

                            }

                            continue;
                        }

                    }


                    read(pipefd_tpos[0], &tpos, sizeof(int));
                    printf("H: %d T: %d\n", hpos, tpos);


                    if(hpos == END ) {
                        printf("Hare won!\n");
                        write(pipefd_rep_hare[1], &two, sizeof(int));
                        write(pipefd_rep_tur[1], &two, sizeof(int));
                        write(god_rep_exit[1], &one, sizeof(int));
                        wait(NULL);
                        exit(0);
                    }
                    else if(tpos == END) {
                        printf("Turtle won!\n");
                        write(pipefd_rep_hare[1], &two, sizeof(int));
                        write(pipefd_rep_tur[1], &two, sizeof(int));
                        write(god_rep_exit[1], &one, sizeof(int));
                        wait(NULL);
                        exit(0);
                    }

                    
                    // sleep(1);

                    write(pipefd_rep_tur[1], &zero, sizeof(int));
                    continue;
                }

                if(hare_c == 1 && tur_c == 1) {

                    read(pipefd_hpos[0], &hpos, sizeof(int));
                    read(pipefd_tpos[0], &tpos, sizeof(int));
                    printf("H: %d T: %d\n", hpos, tpos);



                    if(hpos == END ) {
                        printf("Hare won!\n");
                        write(pipefd_rep_hare[1], &two, sizeof(int));
                        write(pipefd_rep_tur[1], &two, sizeof(int));
                        write(god_rep_exit[1], &one, sizeof(int));
                        wait(NULL);
                        exit(0);
                    }
                    else if(tpos == END) {
                        printf("Turtle won!\n");
                        write(pipefd_rep_hare[1], &two, sizeof(int));
                        write(pipefd_rep_tur[1], &two, sizeof(int));
                        write(god_rep_exit[1], &one, sizeof(int));
                        wait(NULL);
                        exit(0);
                    }


                    if((hpos - tpos) >= MAX_SEP) {
                        write(pipefd_rep_hare[1], &three, sizeof(int));
                        write(pipefd_rep_tur[1], &zero, sizeof(int));
                        write(pipefd_hare_rep2[1], &neg, sizeof(int));
                        continue;
                    }

                    sleep(1);
                    break;

                }

               
            }

             write(pipefd_rep_hare[1], &zero, sizeof(int));
             write(pipefd_rep_tur[1], &zero, sizeof(int));

		}
		


	}
	else if(a == 0 && b > 0){
	// Hare process			
	close(pipefd_rep_hare[1]); // closing write fd
	close(pipefd_hare_rep[0]); // closing read fd
	close(pipefd_hpos[0]);
	close(pipefd_god_hare[1]);
    close(pipefd_god_hare_wakeup[1]);
    close(pipefd_hare_rep2[1]);
    close(god_sync_hare[0]);
	
                
    int hare = 0;
    int hare_bin = 0;
    int exit_hare = 0;
    int god_hare = -1;
    int zero = 0;
    int wakeup = -1;
    int one = 1;
    

				while(1) {
					

					while(1) {
                        
                        if(hare_bin == 0){
                            break;
                        }
                        else if(hare_bin == 1) {
                            read(pipefd_rep_hare[0], &hare_bin, sizeof(int));
                            continue;
                        }
                        else if(hare_bin == 2) {
                            exit_hare = 1;
                            break;
                        }
                        else if(hare_bin == 3) {
                            int count = generate_random(90, 180);
                            for(int i=0;i < count ; i++){
                                int r = read(pipefd_hare_rep2[0], &wakeup, sizeof(int));
                                if(wakeup > 0) {
                                  
                                    hare = wakeup;
                                    wakeup = -1;
                                    write(pipefd_hpos[1], &hare, sizeof(int));
                                    read(pipefd_god_hare[0], &god_hare, sizeof(int));
                                    hare_bin = 4;
                                    god_hare = -1;                                    
                                    break;
                                }

                                write(pipefd_hare_rep[1], &hare_bin, sizeof(int));
                                // write(pipefd_hpos[1], &hare, sizeof(int));
                            }
                            if(hare_bin == 4){
                                hare_bin = 1;
                                write(pipefd_hare_rep[1], &one, sizeof(int));
                                write(god_sync_hare[1], &one, sizeof(int));
                                continue;
                            }
                            else
                                break;
                        }
                     

                    }

                    if(exit_hare == 1) {
                        exit(0);
                    }

 
                    read(pipefd_god_hare[0], &god_hare, sizeof(int));

                    if(god_hare > 0){
                        hare = god_hare;
                        god_hare = -1;
                    }
                    else
                        hare+=2;

                    hare_bin = 1;
                    write(pipefd_hare_rep[1], &hare_bin, sizeof(int));
                    write(pipefd_hpos[1], &hare, sizeof(int));

                }
		
	}
	else if(a > 0 && b == 0){
	// Turtle process

	close(pipefd_rep_tur[1]);
	close(pipefd_tur_rep[0]);
	close(pipefd_tpos[0]);
	close(pipefd_god_tur[1]);
    close(god_sync_tur[0]);

	
    int turtle = 0;
    int tur_bin = 0;
    int exit_tur = 0;
    int god_tur = -1;
    int one = 1;


                while(1) {	

                        while(1) {
                        
                            if(tur_bin == 0){
                                break;
                            }
                            else if(tur_bin == 1) {
                                read(pipefd_rep_tur[0], &tur_bin, sizeof(int));
                                continue;
                            }
                            else if(tur_bin == 2) {
                                exit_tur = 1;
                                break;
                            }
                            else if(tur_bin == 3) {
                                write(god_sync_tur[1], &one,sizeof(int));
                                tur_bin = 1;
                                // write(pipefd_tur_rep[1], &tur_bin, sizeof(int));
                                continue;
                            }
                           

                        }

                        if(exit_tur == 1){
                            exit(0);
                        }

                        read(pipefd_god_tur[0], &god_tur, sizeof(int));

                        if(god_tur > 0) {
                            turtle = god_tur;
                            god_tur = -1;
                        }
                        else {
                            turtle+=1;
                        }


                    tur_bin = 1;
                    write(pipefd_tur_rep[1], &tur_bin, sizeof(int));
                    write(pipefd_tpos[1], &turtle, sizeof(int));
				
                }


	}

	else {
		// God Process
		close(pipefd_god_tur[0]);
		close(pipefd_god_hare[0]);

		close(pipefd_god_rep[0]);
        close(pipefd_god_hare_wakeup[0]);
        close(god_rep_exit[1]);

		int x,y;
		int god = -1;
        int siggod = 1;
        int counter = 0;
        int exit_god = 0;

        int ch;

        while (1) { 
            
            read(god_rep_exit[0], &exit_god, sizeof(int));

            if(exit_god == 1) {
                exit(0);
            }
  
            if ( kbhit() ) {



                int res = scanf("%d %d", &x, &y);


                if(res > 0) {
                    write(pipefd_god_hare[1], &x, sizeof(int));
                    write(pipefd_god_hare_wakeup[1], &x, sizeof(int));
                    write(pipefd_god_tur[1], &y, sizeof(int));
                    fflush(stdin);
                    write(pipefd_god_rep[1], &x, sizeof(int));
                    write(pipefd_god_hare_wakeup[1], &x, sizeof(int));
                }

            } 
        }
		
	}

}