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


int main()
{
	srand(time(0));
	int pipefd_rep_tur[2], pipefd_rep_hare[2];

	int pipefd_tur_rep[2], pipefd_hare_rep[2];

	int pipefd_tpos[2], pipefd_hpos[2];

	int pipefd_god_tur[2], pipefd_god_hare[2];

	int pipefd_god_rep[2];


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
	// else if(fcntl(pipefd_hare_rep[0], F_SETFL, O_NONBLOCK)) {
	// 		printf("Unable to create rep hare pipe");
	// 		return -1;
	// }
	// else if(fcntl(pipefd_hpos[0], F_SETFL, O_NONBLOCK)) {
	// 		printf("Unable to create rep hare pipe");
	// 		return -1;
	// }

	else if(fcntl(pipefd_god_rep[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	else if(fcntl(pipefd_god_tur[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}
	else if(fcntl(pipefd_god_hare[0], F_SETFL, O_NONBLOCK)) {
			printf("Unable to create rep hare pipe");
			return -1;
	}




	int a = fork();
	int b = fork();

	int lock = 1;
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


		write(pipefd_rep_hare[1], &utime, sizeof(int));
		write(pipefd_rep_tur[1], &utime, sizeof(int));



		printf("Reporter starting the race\n");
		
		int temp = 0;
		int temp1 = 0;
		int t = 0;
		int t1 = 2;
		int t2 = 3;
		int hpos = 0;
		int tpos = 0;

		int godpos = 0;

		int four = 4;
				
		while(1) {

				
			read(pipefd_hare_rep[0], &temp, sizeof(int));
			read(pipefd_tur_rep[0], &temp1, sizeof(int));


			if(temp == 2 && temp1 == 1) {
				utime++;
				// write(pipefd_rep_hare[1], &t, sizeof(int));
				write(pipefd_rep_tur[1], &t, sizeof(int));
				temp1 = 0;
			}

			else if(temp == 1 && temp1 == 1) {

					read(pipefd_god_rep[0], &godpos, sizeof(int));

					if(godpos == 1){
						printf("here at\n");
						write(pipefd_rep_hare[1], &four, sizeof(int));
						write(pipefd_rep_tur[1], &four, sizeof(int));
						godpos = 0;
						// continue;
					}

					// if(godpos == 0){

							read(pipefd_hpos[0], &hpos, sizeof(int));
							read(pipefd_tpos[0], &tpos, sizeof(int));

							printf("H: %d T: %d\n", hpos, tpos);
					// }

				// godpos = 0;
			
				if(hpos == END){
					printf("Hare Won\n");
					write(pipefd_rep_hare[1], &t2, sizeof(int));
					write(pipefd_rep_tur[1], &t2, sizeof(int));
					wait(NULL);
					exit(0);
				}
				else if(tpos == END) {
					printf("Turtle Won\n");
					write(pipefd_rep_hare[1], &t2, sizeof(int));
					write(pipefd_rep_tur[1], &t2, sizeof(int));
					wait(NULL);
					exit(0);
				}

				// read(pipefd_god_rep[0], &godpos, sizeof(int));

				// if(godpos == 1){
				// 	printf("here at\n");
				// 	write(pipefd_god_rep[1], &four, sizeof(int));
				// 	write(pipefd_god_rep[1], &four, sizeof(int));
				// 	continue;
				// }


					if((hpos - tpos) >= 50) {
						temp = 2;
						printf("here\n");
						write(pipefd_rep_hare[1], &t1, sizeof(int));
						write(pipefd_rep_tur[1], &t, sizeof(int));
						temp1 = 0;
						continue;
					}



				write(pipefd_rep_hare[1], &t, sizeof(int));
				write(pipefd_rep_tur[1], &t, sizeof(int));
				// temp1 = 0;
				// temp = 0;
			}

			sleep(3);

		}
		


	}
	else if(a == 0 && b > 0){
	// Hare process			
	close(pipefd_rep_hare[1]); // closing write fd
	close(pipefd_hare_rep[0]); // closing read fd
	close(pipefd_hpos[0]);
	close(pipefd_god_hare[1]);
	
	int time = 0;

	int exit = 0;

	int god_pos = -1;

	
		   int hare = 0;
		//    write(pipefd_hpos[1], &hare, sizeof(int));
                
				while(1) {
					

					while(1) {

						int r = read(pipefd_rep_hare[0], &time, sizeof(int));
							// read(pipefd_god_hare[0], &god_pos, sizeof(int));
						if(time == 1) {
							continue;
						}
						else if(time == 2){
							int count = generate_random(90,180);
							for(int i = 0;i < count;i++){
									write(pipefd_hare_rep[1],&time, sizeof(int));
									write(pipefd_hpos[1], &hare, sizeof(int));
							}
							break;
						}
						else if(time == 3){
							exit = 1;
							break;
						}
						else if(time == 4){
							// printf("hitting this\n");
							while(god_pos < 0) {
								read(pipefd_god_hare[0], &god_pos, sizeof(int));
							// 	printf("godpos in hare: %d\n",god_pos);
							}
							hare = god_pos;
							god_pos = -1;
							time = 1;
							write(pipefd_hare_rep[1],&time, sizeof(int));
							write(pipefd_hpos[1], &hare, sizeof(int));	
							continue;
						}
						else {
							break;
						}

					}

					if(exit){
						break;
					}

					


					// if(god_pos > 0) {
					// 	hare = god_pos;
					// 	god_pos = -1;
					// }
					// else {
						hare += 2;
						// printf("hare postition: %d\n", hare);
					// }

					time = 1;
					write(pipefd_hare_rep[1],&time, sizeof(int));
					write(pipefd_hpos[1], &hare, sizeof(int));				

                }
		
	}
	else if(a > 0 && b == 0){
	// Turtle process

	close(pipefd_rep_tur[1]);

	close(pipefd_tur_rep[0]);

	close(pipefd_tpos[0]);

	close(pipefd_god_tur[1]);

	

	int time1 = 0;
	int exit1 = 0;
	int god_pos = -1;

                int turtle = 0;

				// write(pipefd_tpos[1], &turtle, sizeof(int));


                while(1) {	

					while(1){

						int r = read(pipefd_rep_tur[0], &time1, sizeof(int));
							// read(pipefd_god_tur[0], &god_pos, sizeof(int));
						if(time1 == 1) {
							// printf("im here\n");
							continue;
						}
						else if(time1 == 3){
							exit1 = 1;
							break;
						}
						else if(time1 == 4){
							
							while(god_pos < 0) {
								read(pipefd_god_tur[0], &god_pos, sizeof(int));
							}
							turtle = god_pos;
							god_pos = -1;
							time1 = 1;
							write(pipefd_tur_rep[1], &time1, sizeof(int));
							write(pipefd_tpos[1], &turtle, sizeof(int));
							continue;
						}
						else {
							break;
						}

					}

					if(exit1) {
						break;
					}
					

					// if(god_pos > 0) {
					// 	turtle = god_pos;
					// 	god_pos = -1;
					// }
					// else {
						turtle += 1;
						// printf("turtle postition: %d\n", turtle);
					// }

					time1 = 1;
					write(pipefd_tur_rep[1], &time1, sizeof(int));
					write(pipefd_tpos[1], &turtle, sizeof(int));


                }


	}

	else {
		// God Process
		close(pipefd_god_tur[0]);
		close(pipefd_god_hare[0]);

		close(pipefd_god_rep[0]);

		int x,y;
		int god = 1;



		while(1){
			
			// printf("this\n");
			// write(pipefd_god_tur[1], &god, sizeof(int));
			// write(pipefd_god_hare[1], &god, sizeof(int));

			// x = getchar();
			// y = getchar();

			// if(x != EOF){
				// printf("no\n");
			// }

			if(scanf("%d %d", &x, &y) > 0){
				write(pipefd_god_tur[1], &y, sizeof(int));
				write(pipefd_god_hare[1], &x, sizeof(int));
				write(pipefd_god_rep[1], &god, sizeof(int));
				fflush(stdin);
			}

			// else {

					

			// }

			// break;
		}
		
	}

}