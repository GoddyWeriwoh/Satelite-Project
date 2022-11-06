#include <stdio.h>

int sevenDigCheck(int num){
  int is_seven = 0;
  int checker = 0;
  int check_count = 0;

  checker = num;
  while(checker != 0){
      checker = checker / 10;
      check_count++;
  }
  if(check_count <= 7){

      is_seven = 1;
  }

  return is_seven;
}

int isPrime(int num){
    int is_prime = 0;
    int i = 0;
    int out = 0;

    for(i = num - 1; i > 1 && !out; i--){
        if((num % i) == 0){
            out = 1;
        }
    }

    if(!out){
        is_prime = 1;
    }

    return is_prime;
}

int divisorChecker(int num, int divisor){
    int prop_divisor = 0;

    if(num % divisor == 0){
        prop_divisor = 1;
    }

    return prop_divisor;
}

int reverseNumber(int num){

    int rev = 0;
    int user = 0;

    user = num;
    while(user > 0){
        rev = rev * 10 + user % 10;
        user = user / 10;
    }

    return rev;
}

int main() {
    int done = 0;
    int opt = 0;
    int opt1_done = 0;
    int opt2_done = 0;
    int num = 0;
    int is_seven = 0;
    int is_prime = 0;
    int divisor[3] = {0, 0 , 0};
    int i = 0;
    int j = 0;
    int rep = 0;
    int prop_divisor = 1;
    int pass = 0;
    int rev = 0;
    char key = 'r';
    char buf = 'j';
    int counter = 0;
    int maze[2] = {0, 0};
    int m_done = 0;
    int opt3_done = 0;

    printf("Welcome to amongLs\n");
    opt1_done = opt2_done = opt3_done = 0;

    do{
        do{
            printf("\nWhat task would you like to do?\n\n1. Guess divisors | 2. The reverse password | 3. The labyrinth | 4. Exit\nSelected action: ");
            scanf("%d", &opt);

            if(opt < 1 || opt > 4){
                printf("\nERROR: The correct actions are between [1, 4]\n");
            }

        }while(opt < 1 || opt > 4);

        switch (opt){

            case 1:
                if(!opt1_done){
                    do{
                        printf("\nEnter number: ");
                        scanf("%d", &num);
                        is_seven = sevenDigCheck(num);

                    }while(num <= 0 || !is_seven);

                    is_prime = isPrime(num);

                    //in case the user enters prime or a 1.
                    if(is_prime || num == 1){
                        printf("\nNumber not valid.\n\nTask failed!\n");
                    }
                    else{
                        rep = 0;
                        prop_divisor = 1;
                        for(i = 0; i < 3 && !rep && prop_divisor; i++){
                            do{
                                printf("\nDivisor %d.\n", i+1);

                                printf("\nEnter number: ");
                                scanf("%d", &divisor[i]);

                                is_seven = sevenDigCheck(divisor[i]);

                            }while(!is_seven);

                            for(j = 0; j < i; j++){
                                if(divisor[i] == divisor[j]){
                                    rep = 1;
                                }
                            }
                            if(!rep){
                                prop_divisor = divisorChecker(num, divisor[i]);
                            }
                        }
                        if(rep){
                            printf("\nYou have already tried that number!\n\nTask failed!\n");
                        }
                        else{
                            if(!prop_divisor){
                                printf("\n%d is not a divisor of %d!\n\nTask failed!\n", divisor[i - 1], num);
                            }
                            else{
                                if(opt2_done && opt3_done){
                                    printf("\nTask done!\n\nAll tasks done! You completed 3 tasks!\n\nThanks for playing!\n");
                                    done = 1;
                                }
                                else{
                                    printf("\nTask done!\n");
                                    opt1_done = 1;
                                }
                            }
                        }
                    }
                }
                else{
                    printf("Task already done\n\n");
                }

            break;


            case 2:
                if(!opt2_done){
                    //checking if the input is a valid one or not.
                    do{
                        printf("\nEnter number: ");
                        scanf("%d", &num);
                        is_seven = sevenDigCheck(num);

                    }while(num <= 0 || !is_seven);

                    printf("\nPassword: ");
                    scanf("%d", &pass);

                    rev = reverseNumber(num);

                    if(rev == pass){
                        if(opt1_done && opt3_done){
                            printf("\nTask done!\n\nAll tasks done! You completed 3 tasks!\n\nThanks for playing!\n");
                            done = 1;
                        }
                        else{
                            printf("\nTask done!\n");
                            opt2_done = 1;
                        }
                    }
                    else{
                        printf("\nTask failed!\n");
                    }
                }
                else{
                    printf("\nTask already done\n");
                }
            break;


            case 3:
                if(!opt3_done){

                    printf("\nYou are located at the coordinates (0,0) of the maze. The coordinates to exit are (3,4)\n\nMove around the map using cardinal keys N,S,E,W\n\n");

                    counter = 0;
                    m_done = 0;
                    maze[0] = maze[1] = 0;

                    while(counter < 10 && !m_done){
                        do{
                            printf("Enter key to move: ");
                            scanf("%c", &buf);
                            scanf("%c", &key);


                            if(key != 'N' && key != 'W' && key != 'E' && key != 'S'){

                                printf("\nError, to move use the keys N,S,E,W\n\n");
                            }

                        }while(key != 'N' && key != 'W' && key != 'E' && key != 'S');

                        if(key == 'N'){
                            maze[1] = maze[1] + 1;

                            printf("\nYou are in (%d,%d) of the maze\n\n", maze[0], maze[1]);
                        }

                        if(key == 'W'){
                            maze[0] = maze[0] - 1;
                            printf("\nYou are in (%d,%d) of the maze\n\n", maze[0], maze[1]);
                        }

                        if(key == 'S'){
                            maze[1] = maze[1] - 1;
                            printf("\nYou are in (%d,%d) of the maze\n\n", maze[0], maze[1]);
                        }

                        if(key == 'E'){
                            maze[0] = maze[0] + 1;
                            printf("\nYou are in (%d,%d) of the maze\n\n", maze[0], maze[1]);
                        }

                        counter++;

                        if(maze[0] == 3 && maze[1] == 4){
                            m_done = 1;
                        }

                    }

                    if(counter >= 10){
                        printf("Task failed!\n");

                    }
                    else{
                        if(opt1_done && opt2_done){
                            printf("\nTask done!\n\nAll tasks done! You completed 3 tasks!\n\nThanks for playing!\n");
                            done = 1;
                        }
                        else{
                            printf("Task done!\n");
                            opt3_done = 1;
                        }
                    }

                }
                else{
                    printf("Task already done\n\n");
                }
            break;


            case 4:

                printf("\nThanks for playing!\n");

                done = 1;
            break;

        }

    }while(!done);

    return 0;
}
