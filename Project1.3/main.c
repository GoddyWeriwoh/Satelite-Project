#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_NAME 50
#define SIZE 200
#define PI 3.14159

typedef struct {
    char name[MAX_NAME];
    char loc_type[MAX_NAME];
    int loc_rating;
    float position[2];
    int hours[2];
}Location;

float myAttoi1(char buffer[MAX_NAME], int mx){

    int j = 0;
    float num1 = 0;
    int sign = 1;
    float sum = 0;
    int is_zero = 0;
    float num2 = 0;
    int is_neg = 0;


    while (buffer[j] != '.') {

        if(buffer[j] == '-'){
            sign = -sign;
            j++;
        }
        num1 = num1 * 10 +  (float)(buffer[j] - '0');
        j++;
    }
    if(num1 != 0 && sign < 0){
        is_neg = 1;
    }
    else{
        is_zero = 1;
    }

    //atoi after the "."
    j++;
    num2 = 0;

    while (j < mx) {
        num2 = num2 * 10 + (float)(buffer[j] - '0');
        j++;
    }

    num2 = (float)num2 / 1000;

    if(is_zero){
        num2 = num2 * sign;
    }

    //adding the two numbers
    sum = (num1 + num2);

    if(is_neg){
        sum = -sum;
    }

    return sum;
}


int myAttoi2(char buffer[MAX_NAME], int mx){
    int j = 0;
    int num1 = 0;

    while (j < mx) {
        num1 = num1 * 10 + (buffer[j] - '0');
        j++;
    }

    return num1;
}


//function to calculate the distance
float calDist(float lat1, float long1, float lat2, float long2){
    float d;
    float lat12 = 0;
    float lat22 = 0;
    float long12 = 0;
    float long22 = 0;

    lat12 = (float)(PI * lat1) / 180;
    lat22 = (float)(PI * lat2) / 180;
    long12 = (float)(PI * long1) / 180;
    long22 = (float)(PI * long2) / 180;

    d = (6378.137) * acos(sin(lat12) * sin(lat22) + cos(lat12) * cos(lat22) * cos(long22 - long12));

    return d;
}

void sortByDist(float dist_chosen[10], Location locs_chosen[10], int max_chosen){

    int i = 0;
    Location tmp;
    float tmp1 = 0;

    for(i = 0; i < max_chosen - 1; i++){
        if(dist_chosen[i] == 0){
            i++;
        }
        if(dist_chosen[i] > dist_chosen[i+1]){
            tmp = locs_chosen[i];
            locs_chosen[i] = locs_chosen[i + 1];
            locs_chosen[i + 1] = tmp;


            tmp1 = dist_chosen[i];
            dist_chosen[i] = dist_chosen[i + 1];
            dist_chosen[i + 1] = tmp1;
        }
    }
}

int main() {
    int opt = 0;
    int good = 1;
    int ok = 0;
    int first_menu = 1;
    Location locations[10];
    int i = 0;
    int free_pos = 0;
    //int full = 0;
    char info[SIZE];
    Location buf_loc;
    int j = 0;
    char buffer[MAX_NAME];
    char aux = 'v';
    int mx = 0;
    int buf_time = 0;
    float buf_lat = 0;
    float buf_long = 0;
    float distances[10];
    Location locs_chosen[10];
    float dist_chosen[10];
    int max_chosen = 0;


    do{
        do{
            if(first_menu){
                printf("Welcome to LS Maps!\n\n");
            }
            printf("1. Add location | 2. List locations | 3. Show suggestions | 4. Exit\n");
            printf("Selected action: ");
            scanf("%d", &opt);
            scanf("%c", &aux);

            //checking if first time we seeing the menu or not.
            first_menu = 0;


            if(opt < 1 || opt > 4){
                printf("\nERROR: Wrong action number\n\n");
            }
        }while(opt < 1 || opt > 4);


        switch (opt) {

            case 1:
                //checking if the array is full
                if (free_pos == 10) {
                    //full = 1;
                    printf("The system has reached the maximum number of locations\n");
                }
                    //in case there's still space
                else {
                    do {

                        good = 1;

                        printf("\nLocation information: ");
                        fgets(info, SIZE, stdin);
                        info[strlen(info) - 1] = '\0';

                        j = 0;
                        i = 0;
                        while (info[i] != '#') {
                            buf_loc.name[j] = info[i];
                            i++;
                            j++;
                        }
                        buf_loc.name[j] = '\0';
                        j = 0;
                        i++;

                        while (info[i] != '#') {
                            buf_loc.loc_type[j] = info[i];
                            i++;
                            j++;
                        }
                        buf_loc.loc_type[j] = '\0';
                        i++;
                        j = 0;

                        buf_loc.loc_rating = info[i] - '0';
                        i++;

                        //To be on first latitude position
                        i++;

                        //Latitude
                        while (info[i] != '|') {
                            buffer[j] = info[i];
                            i++;
                            j++;
                        }
                        buffer[j] = '\0';
                        mx = j;
                        i++;

                        //latitude atoi
                        buf_loc.position[0] = myAttoi1(buffer, mx);

                        j = 0;


                        if ((buf_loc.position[0] < -90) || (buf_loc.position[0] > 90)) {
                            printf("\nERROR: Wrong information! Try again!\n");
                            good = 0;
                        }
                        else{
                            //longitude
                            while (info[i] != '#') {
                                buffer[j] = info[i];
                                i++;
                                j++;
                            }

                            buffer[j] = '\0';
                            i++;
                            mx = j;

                            //Longitude atoi
                            buf_loc.position[1] = myAttoi1(buffer, mx);

                            if((buf_loc.position[1] >= -180) && (buf_loc.position[1] <= 180)) {
                                j = 0;
                                //Opening hours
                                while (info[i] != '-') {
                                    buffer[j] = info[i];
                                    i++;
                                    j++;
                                }
                                buffer[j] = '\0';
                                i++;
                                mx = j;

                                //atoi of first hour
                                buf_loc.hours[0] = myAttoi2(buffer, mx);


                                if (buf_loc.hours[0] < 0 || buf_loc.hours[0] > 23) {

                                    printf("\nERROR: Wrong information! Try again!\n");
                                    good = 0;
                                } else {
                                    j = 0;
                                    //closing hours
                                    while (info[i] != '\0') {
                                        buffer[j] = info[i];
                                        i++;
                                        j++;
                                    }
                                    buffer[j] = '\0';
                                    mx = j;
                                    i++;

                                    //atoi of second hour
                                    buf_loc.hours[1] = myAttoi2(buffer, mx);

                                    if (buf_loc.hours[1] < 0 || buf_loc.hours[1] > 23) {

                                        printf("\nERROR: Wrong information! Try again!\n");

                                        good = 0;
                                    }
                                }

                            }
                            else{
                                printf("\nERROR: Wrong information! Try again!\n");
                                good = 0;
                            }

                        }
                        //Checking the longitude state

                    }while (!good);
                    //alls good
                    locations[free_pos] = buf_loc;
                    free_pos++;
                    printf("\nLocation added successfully\n\n");
                }
                break;

            case 2:
                if(free_pos == 0){
                    printf("\nERROR: No locations to show\n\n");
                }
                else{
                    i = 0;
                    for(i = 0; i < free_pos; i++){
                        if(i == 0){
                            printf("\nLocation %d\n\tName: %s\n\tType of location: %s\n\tQualification: %d\n\tLatitude: %.3f\n\tLongitude: %.3f\n\tOpening hours: %dh - %dh\n\n", i+1, locations[i].name, locations[i].loc_type, locations[i].loc_rating, locations[i].position[0], locations[i].position[1], locations[i].hours[0], locations[i].hours[1]);
                        }
                        else{
                            printf("Location %d\n\tName: %s\n\tType of location: %s\n\tQualification: %d\n\tLatitude: %.3f\n\tLongitude: %.3f\n\tOpening hours: %dh - %dh\n\n", i+1, locations[i].name, locations[i].loc_type, locations[i].loc_rating, locations[i].position[0], locations[i].position[1], locations[i].hours[0], locations[i].hours[1]);
                        }

                    }
                }
                break;

            case 3:

                if(free_pos == 0){
                    printf("\nERROR: No locations to show\n\n");
                }
                else{
                    printf("\n");
                    do{
                        printf("Introduce time: ");
                        scanf("%d", &buf_time);

                        if(buf_time < 0 || buf_time > 24){

                            printf("\nERROR: Wrong  value\n\n");
                        }
                    }while(buf_time < 0 || buf_time > 24);

                    do{
                        printf("\nIntroduce latitude: ");
                        scanf("%f", &buf_lat);

                        if(buf_lat < -90 || buf_lat > 90){
                            printf("\nERROR: Wrong  value\n");

                        }

                    }while(buf_lat < -90 || buf_lat > 90);

                    do{
                        printf("\nIntroduce longitude: ");
                        scanf("%f", &buf_long);

                        if(buf_long < -180 || buf_long > 180){
                            printf("\nERROR: Wrong  value\n");
                        }
                    }while(buf_long < -180 || buf_long > 180);

                    //Display of available locations

                    //printf("\n");

                    j = 0;
                    for(i = 0; i < free_pos; i++){
                        if(locations[i].hours[0] <= buf_time && locations[i].hours[1] >= buf_time){
                            distances[i] = calDist((double)buf_lat, (double)buf_long, (double)locations[i].position[0], (double)locations[i].position[1]);

                            dist_chosen[j] = distances[i];
                            locs_chosen[j] = locations[i];
                            j++;
                        }
                    }
                    max_chosen = j;

                    //Sorting by distance
                    sortByDist(dist_chosen, locs_chosen, max_chosen);

                    //printing the values to be printed
                    for(i = 0; i < max_chosen; i++){
                        if(i == 0){
                            printf("\nLocation %d:\n\tName: %s\n\tDistance: %.3f Km\n\n", i+1, locs_chosen[i].name, dist_chosen[i]);
                        }
                        else{
                            printf("Location %d:\n\tName: %s\n\tDistance: %.3f Km\n\n", i+1, locs_chosen[i].name, dist_chosen[i]);
                        }

                    }


                }
                break;

            case 4:

                printf("\nBye!\n");

                ok = 1;

                break;
        }

    }while(!ok);

    return 0;
}