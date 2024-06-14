//VOL 10 , need to uncomment stepper motor pynq, and side sensor lines. Matrix works (havent tested with the side sensors yet)

#include <arm_shared_memory_system.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <libpynq.h>
#include <platform.h>
#include <stdint.h>
#include <stepper.h>

void uart_read_array(const int uart, uint8_t *buf, uint8_t l) {
  for (uint8_t x = 0; x < l; x++) {
    buf[x] = uart_recv(uart);
  }
}


#define CLIFF '#'
#define UNVISITED 'N'
#define VISITED '+'
#define ROCK 'R'
#define MOUNTAIN 'M'
#define VISITED '+'
#define CURRPOS '^'
#define SIZEX 50
#define SIZEY 80



typedef struct
{
    char grid[SIZEX][SIZEY];
    
} matrix_t;

typedef struct{
    int x;
    int y;
} pos;

 //functions

//matrix related functions
matrix_t setToObstacle(pos currpos, matrix_t matrix){
    matrix.grid[currpos.x][currpos.y] = '#';
    //(" %c", matrix.grid[currpos.x][currpos.y]);
    return matrix;
}


matrix_t setToVisited(pos currpos, matrix_t matrix, int orientation){
     switch(orientation){
        case 0:
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x + i][currpos.y + k] = '+';
                }
            }
            break;
        case 90:
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x + k][currpos.y + i] = '+';
                }
            }
            break;
        case 180: 
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x - i][currpos.y - k] = '+';
                }
            }

            break;
        case 270:
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x - k][currpos.y - i] = '+';
                }
            }
            break;
        default:
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x + k][currpos.y + i] = '+';
                }
            }
            break;

    }
     //matrix.grid[currpos.x][currpos.y] = '+';
    //(" %c", matrix.grid[currpos.x][currpos.y]);
    return matrix;
}


matrix_t setToCurrpos(pos currpos, matrix_t matrix, int orientation){
   

    switch(orientation){
        case 0:
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x + i][currpos.y + k] = '-';
                }
            }
            matrix.grid[currpos.x][currpos.y] = '^';
            break;
        case 90:
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x + k][currpos.y + i] = '-';
                }
            }
            matrix.grid[currpos.x][currpos.y] = '^';
            break;
        case 180: 
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x - i][currpos.y - k] = '-';
                }
            }

            break;
        case 270:
            for(int i =-2; i<3; i++){
                for(int k=-4; k<1; k++){
                    matrix.grid[currpos.x - k][currpos.y - i] = '-';
                }
            }
            break;
        default:
            break;
    }
  matrix.grid[currpos.x][currpos.y] = '^';
        
    //(" %c", matrix.grid[currpos.x][currpos.y]);
    return matrix;
}



void printMatrix(matrix_t matrix){
for(int i=0; i<SIZEX; i++){
        for(int j=0; j<SIZEY; j++){
            printf(" %c", matrix.grid[i][j]);
        }
        printf("\n");
    }
}

char left(pos currpos, matrix_t matrix, int orientation) {
    pos tempPos = currpos;
    char cell='N';
    switch (orientation) {
        case 0: 
            for (int i = -2; i < 2; i++) {
                tempPos.y = currpos.y + i;
                if (matrix.grid[tempPos.x - 3][tempPos.y - 2] == '#') {
                    cell= '#';
                }
            }
            //return 'N';
            break;
        case 90: 
            for (int i = -2; i < 2; i++) {
                tempPos.x = currpos.x + i;
                if (matrix.grid[tempPos.x - 2][currpos.y + 3] == '#') {
                    cell= '#';
                }
            }
            //return 'N';
            break;
        case 180: 
            for (int i = -2; i < 2; i++) {
                tempPos.y = currpos.y - i;
                if (matrix.grid[tempPos.x + 3][tempPos.y + 2] == '#') {
                    cell= '#';
                }
            }
           // return 'N';
            break;
        case 270:
            for (int i = -2; i < 2; i++) {
                tempPos.x = currpos.x - i;
                if (matrix.grid[tempPos.x + 2][currpos.y - 3] == '#') {
                    cell= '#';
                }
            }
            //return 'N';
            break;
        default:
            cell= 'E'; // Error case
            break;
    }

    return cell;
}

char right(pos currpos, matrix_t matrix, int orientation) {
    pos tempPos = currpos;

    char cell='N';

    switch (orientation) {
        case 0: 
            for (int i = -2; i < 2; i++) {
                tempPos.y = currpos.y + i;
                if (matrix.grid[tempPos.x + 3][tempPos.y - 2] == '#') {
                    cell= '#';
                }
            }
            //return 'N';
            break;
        case 90: 
            for (int i = -2; i < 2; i++) {
                tempPos.x = currpos.x + i;
                if (matrix.grid[tempPos.x - 2][currpos.y - 3] == '#') {
                    cell= '#';
                }
            }
            //return 'N';
            break;
        case 180: 
            for (int i = -2; i < 2; i++) {
                tempPos.y = currpos.y - i;
                printf(" RIGHT CASE 180: %c ", matrix.grid[tempPos.x - 3][tempPos.y + 2]);
                if (matrix.grid[tempPos.x - 3][tempPos.y + 2] == '#') {
                    cell= '#';
                }
            }
            break;
            //return 'N';

        case 270:
            for (int i = -2; i < 2; i++) {
                tempPos.x = currpos.x - i;
                if (matrix.grid[tempPos.x + 2][currpos.y + 3] == '#') {
                    cell= '#';
                }
            }
            break;
            //return 'N';

        default:
            cell= 'E'; // Error case
            break;
    }
    printf("CELL %c", cell);
    return cell;
}

/*
//detecting around the currpos
char left(pos currpos,  matrix_t matrix, int orientation ){

    
      switch(orientation){
        case 0: 
            for (int i=-2; i<2; i++){
                currpos.y = currpos.y + i;
                if ( matrix.grid[currpos.x-3][currpos.y -2] == '#'){
                    return '#';

                }
            }
            return 'N';

        break;
        case 90: 
            for (int i=-2; i<2; i++){
                currpos.x = currpos.x + i;
                if ( matrix.grid[currpos.x-2][currpos.y +3] == '#'){
                    return '#';

                }
            }
            return 'N';

        break;
        case 180: 
            for (int i=-2; i<2; i++){
                currpos.y = currpos.y - i;
                if ( matrix.grid[currpos.x+3][currpos.y+2] == '#'){
                    return '#';

                }
            }
            return 'N';
            
        break;
        case 270:
            for (int i=-2; i<2; i++){
                currpos.x = currpos.x - i;
                if ( matrix.grid[currpos.x+2][currpos.y - 3] == '#'){
                    return '#';

                }
            }
            return 'N';

        break;
        default:
            return  -1;
            //in case of failure?
        break;
    }

}
char right(pos currpos, matrix_t matrix, int orientation ){

    
    
      switch(orientation){
        case 0: 
            for (int i=-2; i<2; i++){
                currpos.y = currpos.y + i;
                if ( matrix.grid[currpos.x+3][currpos.y-2] == '#'){
                    return '#';

                }
            }
            return 'N';

        break;
        case 90: 
            for (int i=-2; i<2; i++){
                currpos.x = currpos.x + i;
                if ( matrix.grid[currpos.x-2][currpos.y - 3] == '#'){
                    return '#';

                }
            }
            return 'N';

        break;
        case 180: 
            printf("OOOOOOOOOO");
            for (int i=-2; i<3; i++){
                currpos.y = currpos.y - i;
                printf("DNEWIONHDIOEIUDYH %c /", matrix.grid[currpos.x-3][currpos.y+2] );
                if ( matrix.grid[currpos.x-3][currpos.y+2] == '#'){
                    
                    return '#';

                }
            }
            return 'N';
            
        break;
        case 270:
            for (int i=-2; i<2; i++){
                currpos.x = currpos.x - i;
                if ( matrix.grid[currpos.x+2][currpos.y + 3] == '#'){
                    return '#';

                }
            }
            return 'N';

        break;
        default:
            printf("HELOOOOOO");
            return  'H';

            //in case of failure?
        break;
    }
    

}
*/

char front(pos currpos,matrix_t matrix, int orientation ){
    (void) matrix;
    int newX= currpos.x;
    int newY = currpos.y;
    switch(orientation){
        case 0: 
            newY = currpos.y + 1;
            for (int i = -2; i < 2; i++){
                if ( matrix.grid[newX+i][newY]== '#'){
                    return '#';
                }
               
            }
            return 'N';
            
            break;
        case 90: 
            newX = currpos.x + 1;
             for (int i = -2; i < 2; i++){
                if (matrix.grid[newX][newY+i] == '#'){
                    return '#';
                }
            return 'N';
            }
            break;
        case 180: 
            newY = currpos.y - 1;
                for (int i = -2; i < 2; i++){
                    if (matrix.grid[newX-i][newY] == '#'){
                    return '#';
                }
                return 'N';
                }
            break;
        case 270:
            newX = currpos.x - 1;
                for (int i = -2; i < 2; i++){
                    if (matrix.grid[newX][newY-i] == '#'){
                    return '#';
                }
                return 'N';
                }
            break;
        default:
            return 'E';
            //in case of failure?
        break;
        }
    
    return -1; // Return -1 if none of the conditions are met

    }


char behind(pos currpos, matrix_t matrix, int orientation ){

    
      switch(orientation){
        case 0: 
                return matrix.grid[currpos.x][currpos.y - 5];

        break;
        case 90: 
                return matrix.grid[currpos.x-5][currpos.y];

        break;
        case 180: 
                return matrix.grid[currpos.x][currpos.y + 5];

        break;
        case 270:
                return matrix.grid[currpos.x+5][currpos.y];

        break;
        default:
            return  -1;
            //in case of failure?
        break;
    }

}


//sensor related functions
 int get_topd_inf(){ //distance sensed by infrared sensor in mm
    int d;
    printf("input infrared distance ");
    scanf("%d", &d);
    return d;
    
 } 

 int delta_topd_inf(int prev_d_inf, int curr_topd_inf){ //returns value in CM
    //if prev_d_inf = +-0.01m curr_topd_inf -> return 0;

    int final = 0;
    if((prev_d_inf - curr_topd_inf)>-7 && (prev_d_inf - curr_topd_inf)<-4){

    }
    if(((prev_d_inf - curr_topd_inf) < 2 )){
       return 0;
    }
    else if((prev_d_inf - curr_topd_inf) < 4 ){
       return 3;
    }
    else if((prev_d_inf - curr_topd_inf) <7 ){
       return 6;
    }
    return final;
       
 }

 int get_d_ultra(){
    int d;
    printf("input ultrasound distance ");
    scanf("%d", &d);
    return d;
    
 } //distance sensed by ultrasound sensor

char get_c(){ //possible colors = R, G, B, BLACK (L), WHITE (W), error (E)

    char c;
   printf("input color ");
    scanf(" %c", &c);
    return c;
    
 } // color sensed by color sensor


pos update_coordinates(int orientation, pos currpos){

    switch(orientation){
        case 0: 
            currpos.y = currpos.y + 1;
        break;
        case 90: 
            currpos.x = currpos.x + 1;
        break;
        case 180: 
            currpos.y = currpos.y - 1;
        break;
        case 270:
            currpos.x = currpos.x - 1;
        break;
        default:
            currpos.x = -1;
            currpos.y = -1;
            //in case of failure?
        break;
    }
    return currpos;
}

pos front_left(int orientation, pos currpos){
  switch(orientation){
        case 0: 
            currpos.y = currpos.y + 1;
            currpos.x = currpos.x - 2;
        break;
        case 90: 
            currpos.x = currpos.x + 1;
             currpos.y = currpos.y + 2;
        break;
        case 180: 
            currpos.y = currpos.y - 1;
            currpos.x = currpos.x + 2;
        break;
        case 270:
            currpos.x = currpos.x - 1;
            currpos.y = currpos.y - 2;
        break;
        default:
            currpos.x = -1;
            currpos.y = -1;
            //in case of failure?
        break;
    }
    return currpos;
}

pos front_right(int orientation, pos currpos){
 switch(orientation){
        case 0: 
            currpos.y = currpos.y + 1;
            currpos.x = currpos.x + 2;
        break;
        case 90: 
            currpos.x = currpos.x + 1;
             currpos.y = currpos.y - 2;
        break;
        case 180: 
            currpos.y = currpos.y - 1;
            currpos.x = currpos.x - 2;
        break;
        case 270:
            currpos.x = currpos.x - 1;
            currpos.y = currpos.y + 2;
        break;
        default:
            currpos.x = -1;
            currpos.y = -1;
            //in case of failure?
        break;
    }
    return currpos;

}

// code deciding whether to choose
int turn_clockwise_90(int orientation) {
    return (orientation + 90) % 360;
}

int turn_anticlockwise_90(int orientation) {
    return (orientation + 270) % 360;  // equivalent to -90 in modular arithmetic
}

int count_unvisited_in_direction(pos currpos, matrix_t matrix, int orientation) {
    int count = 0;
    int x = currpos.x;
    int y = currpos.y;

    while (true) {
        switch (orientation) {
            case 0:  // North
                y++;
                break;
            case 90:  // East
                x++;
                break;
            case 180:  // South
                y--;
                break;
            case 270:  // West
                x--;
                break;
        }
        if (x < 0 || x >= SIZEX || y < 0 || y >= SIZEY || matrix.grid[x][y] == '#') {
            //300 set here as an example limit, to be changed once actual matrix size has been determined
            printf("%d %d\n", orientation, count);
            break;
        }
        count++;
    }
    return count;
}

// function to decide best direction based on unvisited spaces
char optimal_direction(pos currpos, matrix_t matrix, int orientation) {
    int right_orientation = turn_clockwise_90(orientation);
    int left_orientation = turn_anticlockwise_90(orientation);

    int right_unvisited = count_unvisited_in_direction(currpos, matrix, right_orientation);
    printf("right_unvisited : %d\n", right_unvisited);
    int left_unvisited = count_unvisited_in_direction(currpos, matrix, left_orientation);
     printf("left_unvisited : %d\n", left_unvisited);
    
    printf("RIGHT: %c \n",right(currpos, matrix, orientation) );
    printf("LEFT: %c \n", left(currpos, matrix, orientation) );
    if ((right_unvisited >= left_unvisited ) && ((right(currpos, matrix, orientation) != '#') )) {
        // yo we switched this to left dont forget
        printf(" CHAR ON THE RIGHT %c \n", right(currpos, matrix, orientation));
        return 'R';  // Turn right
    } else if((left(currpos, matrix,  orientation) != '#')){
        printf(" CHAR ON THE LEFT %c \n", left(currpos, matrix, orientation) );
        return 'L';  // Turn left
    }
    printf("Returning E\n");
    return 'E';
}
// can also set this to return integers if needed

int move_forwards(pos currpos, matrix_t matrix, int orientation){
    //move forwards 3 cm
    printf("fx move_forwards \n");
    printf("char in front: %c\n", front(currpos, matrix, orientation));
     
     
     if((front(currpos, matrix, orientation)==('N') )|| (front(currpos, matrix, orientation)== ('+'))){
    stepper_set_speed(25000,25000);
    stepper_steps(-162, -162); 
    printf("Moving forwards\n");
    
    }
     return orientation;
    
}

char detected_left_sensor(){
  char c;

  //turns 10deg or so to the left
  stepper_steps(0,-66);

  //moves slightly forward for the color sensor
  stepper_steps(-80,-80);

  //gets the color
  c = get_c();

  //moves backward
  stepper_steps(80, 80);

  //turns back
  stepper_steps(0,66);
  
  return c;
}

char detected_right_sensor(){
  char c;

  stepper_steps(-66, 0);

  stepper_steps(-80,-80);

  c = get_c();

  stepper_steps(80, 80);

  stepper_steps(66,0);
  

  return c;
}

int move_avoid_object(pos currpos, matrix_t matrix, int orientation){
   //turn 90 deg on spot
    stepper_set_speed(25000,25000);//3072 is minimum
     char direction= optimal_direction(currpos,  matrix,  orientation);
    printf("fx move_avoid_cliff \n");
    if( direction == 'L'){
         stepper_steps(630, -630); 
         orientation = turn_anticlockwise_90( orientation);
         printf("encountered cliff, turning left\n");
    }
    else{
        stepper_steps(-630, 630); 
        orientation = turn_clockwise_90( orientation);
         printf("encountered cliff, turning right\n");
    }

    
    return orientation;
    //turn 90 deg clock wise
}

void send(char *s, char c, int size, pos currpos, int orientation){
  printf("%s \n", s);
  printf("%c \n", c);
  printf("%d \n", size);
  printf("%d, %d \n", currpos.x, currpos.y);
  printf("%d \n", orientation);
}

char direction_turned(int prev_orientation, int orientation){
    if(orientation - prev_orientation == 90){
        return 'R';
    }
    else if(orientation- prev_orientation == -90){
        return 'L';
    }
    else if(orientation- prev_orientation == 180){
        return 'B';
    }
    else if(orientation- prev_orientation == -180){
        return 'B';
    }
    else if(orientation- prev_orientation == -270){
        return 'R';
    }
    else if(orientation- prev_orientation == 270){
        return 'L';
    }
    else{
        return 'E';
    }
}

pos update_coordinates_rotation(char direction, int orientation, pos currpos){
    printf("TESTING CURPOS X = %d, currpos y= %d, orientation= %d\n" , currpos.x, currpos.y, orientation);
    printf("directionaaaaaaaa: %c", direction);
    switch(orientation){
        case 0: 
            if(direction == 'L'){
              currpos.x= currpos.x -2;
              currpos.y= currpos.y-2;

            }
            else if(direction == 'R'){
              currpos.x= currpos.x +2;
                    currpos.y= currpos.y-2;
                    printf("TESTOOOOO");
            }
            else if(direction == 'B'){
                currpos.y= currpos.y-4;
            }
            
        break;
        case 90: 
             if(direction == 'L'){
              currpos.x= currpos.x -2;
                    currpos.y= currpos.y+2;

            }
            else if(direction == 'R'){
              currpos.x= currpos.x -2;
                    currpos.y= currpos.y-2;
            }
            else if(direction == 'B'){
                currpos.x= currpos.x-4;
            }
        break;
        case 180: 
             if(direction == 'L'){
              currpos.x= currpos.x +2;
                    currpos.y= currpos.y+2;

            }
            else if(direction == 'R'){
              currpos.x= currpos.x -2;
                    currpos.y= currpos.y+2;
            }
            else if(direction == 'B'){
                currpos.y= currpos.y+4;
            }
        break;
        case 270:
            if(direction == 'L'){
              currpos.x= currpos.x +2;
                    currpos.y= currpos.y-2;

            }
            else if(direction == 'R'){
               currpos.x= currpos.x +2;
                    currpos.y= currpos.y+2;
            }
            else if(direction == 'B'){
                currpos.x= currpos.x+4;
            }
            
          
        break;
        default:
            currpos.x = -1;
            currpos.y = -1;
            //in case of failure?
        break;
    }

    printf("TESTING CURPOS X = %d, currpos y= %d", currpos.x, currpos.y);
    return currpos;


}


 //recursive function explore
int explore(matrix_t matrix, int orientation, int prev_d_i, int exp_fin, pos currpos, pos prevpos ){
    if(exp_fin!=1){
      char c;
      prevpos= currpos;
         matrix =  setToCurrpos( /*update_coordinates( orientation, currpos)*/currpos,  matrix, orientation);
      int prev_orientation = orientation;
        int curr_topd_i = get_topd_inf(); //refers to middle sensor
        //int right_d_i = get_topd_inf();
        //int left_d_i = get_topd_inf();
           /*    
        if (left_d_i != curr_topd_i && left_d_i != right_d_i) {
            c = detected_left_sensor();
            matrix =  setToObstacle( front_left( orientation, currpos),  matrix);
        } else if (right_d_i != curr_topd_i && right_d_i != left_d_i) {
            c = detected_right_sensor();
             matrix =  setToObstacle( front_right( orientation, currpos),  matrix);
        } else {
            c = get_c();
        }

       */
        c = get_c();
       
        printf("color %c \n", c);

        int d_ultra= get_d_ultra();
        
                
        if(curr_topd_i <11 && curr_topd_i>9){ //if cliff, crater, nothing or potentially mountain
            if (c== 'L'){ // if cliff or crater
                
                
                matrix =  setToObstacle( update_coordinates( orientation, currpos),  matrix);
            orientation = move_avoid_object( currpos,  matrix,  orientation); //only turn
            
            send("cliff", c, curr_topd_i, update_coordinates( orientation,  currpos ), orientation);
            
        printf("1st MATRIX \n");
            printMatrix(matrix);
            
            } 
            else if(d_ultra<6){  //mountain
                
                matrix =  setToObstacle( update_coordinates( orientation, currpos),  matrix);
                orientation =move_avoid_object( currpos,  matrix,  orientation);
                send("mountain", c, 30, update_coordinates( orientation,  currpos), orientation );
            
            } 
            else{ //nothing
                
                matrix =  setToVisited( update_coordinates( orientation,  currpos),  matrix, orientation);
                //move_forwards( currpos, matrix,  orientation);
                send("nothing", c, 30, update_coordinates( orientation,  currpos), orientation );
            
            }
            
        }
        else if(curr_topd_i < 8 && curr_topd_i>6){
            
        
            matrix =  setToObstacle( update_coordinates( orientation,  currpos),  matrix);
            orientation =move_avoid_object( currpos,  matrix,  orientation);
            send("Rock", c, 3, update_coordinates( orientation,  currpos), orientation );
        
        }
        else if(curr_topd_i <5 && curr_topd_i >2){
        
            matrix =  setToObstacle( update_coordinates( orientation,  currpos),  matrix);
            orientation = move_avoid_object(currpos,  matrix,  orientation);
            send("Rock", c, 6, update_coordinates( orientation,  currpos) , orientation );//NEED TO DEDUCT 150 from currpos;
        }


        char dir;
        if(prev_orientation != orientation){
              dir = direction_turned(prev_orientation, orientation);
              printf(" DIRECTION TURNED %c \n", dir);
              currpos= update_coordinates_rotation( dir,  prev_orientation,  currpos);
              matrix = setToCurrpos(currpos, matrix, orientation);
              printf("diuxgye3vtuitd\n");
              printMatrix(matrix);
            }
        prev_orientation= orientation;

        //********testing surrounding
        if((front(currpos, matrix, orientation)==('N') )|| (front(currpos, matrix, orientation)== ('+'))){
        orientation= move_forwards(currpos,matrix, orientation);
        printf("orientationaaa %d \n", orientation);

        matrix =  setToVisited( /*update_coordinates( orientation,  currpos)*/ currpos,  matrix, orientation);
        
        currpos = update_coordinates( orientation,  currpos );
        }
        else if((left(currpos, matrix, orientation)==('N') )|| (left(currpos, matrix, orientation)== ('+'))){
        stepper_steps(630, -630); 
            orientation = turn_anticlockwise_90( orientation);

        }
        else if((right(currpos, matrix, orientation)==('N') )|| (right(currpos, matrix, orientation)== ('+'))){
        stepper_steps(-630, 630); 
            orientation = turn_clockwise_90( orientation);
          
        }
        else{ //turn around
            stepper_steps(630, -630); 
            orientation = turn_anticlockwise_90( orientation);
            stepper_steps(630, -630); 
            orientation = turn_anticlockwise_90( orientation);
        } 
        //*********************
        printf("2nd MATRIX \n");
          printMatrix(matrix);
       
        
       // matrix =  setToVisited(prevpos,  matrix, orientation);
        printMatrix(matrix);
        printf("3rd MATRIX \n");
        if(prev_orientation != orientation){
          dir = direction_turned(prev_orientation, orientation);
          printf(" %c \n", dir);
          //currpos= update_coordinates_rotation( dir,  prev_orientation,  currpos);
          //matrix = setToCurrpos(currpos, matrix, orientation);
        }
        
        //matrix =  setToVisited( update_coordinates( orientation,  currpos),  matrix);
        //currpos = update_coordinates( orientation,  currpos );
        matrix =  setToCurrpos(currpos,  matrix, orientation);
        printf("currpos %d %d, prevpos %d %d", currpos.x, currpos.y, prevpos.x, prevpos.y);
        prev_d_i = curr_topd_i;
        printf("\n");
        printf("4TH MATRIX \n");
        printMatrix(matrix);

        prevpos = currpos;
        return explore(matrix, orientation, prev_d_i, exp_fin, currpos, prevpos);
    
    }
    else{
        return 1;
    }

 }


int main(void){
    //initialise matrix
    pynq_init();
  switchbox_set_pin(IO_AR0, SWB_UART0_RX);
  switchbox_set_pin(IO_AR1, SWB_UART0_TX);
  gpio_set_direction(IO_AR2, GPIO_DIR_INPUT);
  gpio_set_direction(IO_AR3, GPIO_DIR_INPUT);
  printf("AR2: %d\n", gpio_get_level(IO_AR2));
  printf("AR3: %d\n", gpio_get_level(IO_AR3));


  uart_init(UART0);

  uart_reset_fifos(UART0);

  stepper_init();

  stepper_enable();*/


     matrix_t matrix;

    for(int i=0; i<SIZEX; i++){
        for(int j=0; j<SIZEY; j++){
            
            matrix.grid[i][j]= 'N';
        }
    }

  //THIS IS TO ADD BORDERS 
for (int i = 0; i < SIZEX; i++) {
    matrix.grid[0][i] = '#';         // Top row
    matrix.grid[SIZEY - 1][i] = '#'; // Bottom row
}

for (int i = 0; i < SIZEY; i++) {
    matrix.grid[i][0] = '#';         // Left column
    matrix.grid[i][SIZEX - 1] = '#'; // Right column
}

    
    pos currpos;
    currpos.x = 15;
    currpos.y= 6;
    pos prevpos;
    prevpos.x = 15;
    prevpos.y= 6;

    int orientation= 0;
    
    int prev_d_i= get_topd_inf();
    int exp_fin= 0;
     matrix =  setToCurrpos(currpos,  matrix, orientation);
    //matrix.grid[0][0]= 'O';
    printMatrix(matrix);
    explore(matrix, orientation, prev_d_i, exp_fin, currpos, prevpos);
    
    while (!stepper_steps_done())
    ;

  stepper_destroy();

  pynq_destroy();*/
  return EXIT_SUCCESS;
}
//
