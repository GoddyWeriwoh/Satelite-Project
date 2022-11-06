#include <stdio.h>

int main() {
    int opt = 0;
    int opt2 = 0;
    int out = 0;
    int i = 0;
    int start = 0;
    int tmp = 0;
    int out2 = 0;
    int num_sat = 0;
    int wel_show = 0;

    //main menu display
    //menu implementation
    do{
        out = 0;
        if(!wel_show){
            printf("Welcome to LS Satellite!\n\n");
        }
        wel_show = 1;
        printf("1. Manage satellites | 2. Start transmission | 3. Exit\nSelected action: ");
        scanf("%d", &opt);
        printf("\n");

        if(opt < 1 || opt > 3){
            printf("ERROR: Wrong action number\n\n");
        }
        else{
            switch(opt){
                //managing satellites
                case 1:
                    //num_sat = 0;
                    out2 = 0;
                    do{
                        //Submenu for satellite management
                        printf("1. Add satellite | 2. Delete satellite | 3. Back\nSelected action: ");
                        scanf("%d", &opt2);
                        printf("\n");

                        if(opt2 < 1 || opt2 > 3){
                            printf("ERROR: Wrong action number\n\n");
                        }
                        else{
                            switch(opt2){
                                //Adding satellite
                                case 1:
                                    num_sat++;
                                    printf("Total satellites: %d\n\n", num_sat);
                                    break;

                                    //removing satellite
                                case 2:
                                    //when no satellites present
                                    if(num_sat == 0){
                                        printf("Total satellites: 0\n\n");
                                    }
                                        //when there are satellites
                                    else{
                                        num_sat--;
                                        printf("Total satellites: %d\n\n", num_sat);
                                    }
                                    break;

                                    //going back to main menu
                                case 3:
                                    out2 = 1;

                                    break;
                            }
                        }
                    }while(!out2);

                    break;

                    //Transmissions
                case 2:
                    //If there's no satellite
                    if(num_sat == 0){
                        printf("ERROR: There are no satellites\n\n");
                    }
                        //If there are satellites
                    else{
                        printf("Total satellites: %d\n\n", num_sat);

                        //loop to make sure the starting point entered is correct
                        do{
                            printf("Starting point:");
                            scanf("%d", &start);
                            printf("\n");

                            //Error message
                            if(start < 1 || start > num_sat){
                                printf("ERROR: Nonexistent satellite!\n\n");
                            }

                        }while(start < 1 || start > num_sat);

                        printf("Transmission: ");

                        tmp = start;
                        //looping the transmissions from start to total
                        while(start <= num_sat){
                            printf("%d ", start);
                            start++;
                        }
                        //from 1 to the starting point if they are
                        if(tmp > 1){
                            for(i = 1; i < tmp; i++){
                                printf("%d ", i);
                            }
                        }
                        printf("\n\n");
                    }

                    break;

                    //Exiting program
                case 3:
                    printf("Bye!");

                    out = 1;

                    break;
            }

        }

    }while(!out);

    return 0;
}
