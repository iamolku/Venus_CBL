#define CLIFF '#'
#define UNVISITED NULL 
#define VISITED '+'
#define ROCK 'R'
#define MOUNTAIN 'M'
#define VISITED '+'


typedef struct
{
    char grid[300][300];
    
} matrix_t;

typedef struct{
    int x;
    int y;
} pos;

 //functions

//matrix related functions
matrix_t setToCliff(pos currpos, matrix_t matrix){

    matrix.grid[currpos.x][currpos.y] = '#';
    //(" %c", matrix.grid[currpos.x][currpos.y]);
    return matrix;
}

matrix_t setToVisited(pos currpos, matrix_t matrix){
     matrix.grid[currpos.x][currpos.y] = '+';
    //(" %c", matrix.grid[currpos.x][currpos.y]);
    return matrix;
}


//detecting around the currpos
char left(pos currpos,  matrix_t matrix ){
    if(matrix.grid[currpos.x -1][currpos.y] != NULL){
        return matrix.grid[currpos.x -1][currpos.y];
    }
    else{
        return 'N';
    }
           
}
char right(pos currpos,  matrix_t matrix ){
    if(matrix.grid[currpos.x +1][currpos.y]!= NULL){
        return matrix.grid[currpos.x +1][currpos.y];
    } else{
        return 'N';
    }
}

char up(pos currpos,  matrix_t matrix){
    if(matrix.grid[currpos.x][currpos.y -1]!=NULL){
         return matrix.grid[currpos.x][currpos.y -1];
    }
    else{
        return 'N';
    }
   
}
char behind(pos currpos,  matrix_t matrix){
    if(matrix.grid[currpos.x][currpos.y +1] !=NULL){
        return matrix.grid[currpos.x][currpos.y +1];
    }
    else{
        return 'N';
    }
    
}


//sensor related functions
 int get_topd_inf(){ //distance sensed by infrared sensor in mm
    int d;
    uint_8 dist = uart_recv(UART1); //to change
    d= (int)dist * 10;
    return d;
    
 } 

 int delta_topd_inf(int prev_d_inf, int curr_topd_inf){ //returns value in CM
    //if prev_d_inf = +-0.01m curr_topd_inf -> return 0;
    if(prev_d_inf - curr_topd_inf < 1 || prev_d_inf - curr_topd_inf > -1   ){
       return 0;
    }
    else if((prev_d_inf - curr_topd_inf) < 4 ){
       return 3;
    }
    else if((prev_d_inf - curr_topd_inf) < 6){
       return 6;
    }
       
 }

 int get_d_ultra(){
    int d;
    uint_8 dist = uart_recv(UART1); //to change
    d= (int)dist * 10;
    return d;
    
 } //distance sensed by ultrasound sensor

char get_c(){ //possible colors = R, G, B, BLACK (L), WHITE (W), error (E)

    char c;
    uint_8 color = uart_recv(UART1); //to change
    
    int l;
    int r1;
    int r2;
    int g1;
    int g2;
    int b1;
    int b2;
    int w1; 
    int w2;
   
    switch(color){
        case 0 ... l:
            c= 'L';
        break;
        case r1 ... r2:
            c= 'R';
        break;
        case g1 ... g2:
            c= 'G';
        break;
        case b1 ... b2:
            c= 'B';
        break;
        case w1 ... w1:
            c= 'W';
        break;
        default:
             c= 'E';
        break;
    }

    return c;
    
 } // color sensed by color sensor

boolean pos_to_the_left_explored(pos currpos){
    

    
}
boolean pos_to_the_right_explored(pos currpos){}
//void space_unexplored(pos position){} // returns whether space to the tright or the left of the robot is un
void move_forwards(){
    //move forwards 3 cm
    
}
/*void move_around_object(int angle_wrt_origin){
    //should ideally end up with same orientation as before
} */

int turn_clkwise_90(int orientation){
    //insert code to move

    //update and return orientation
    switch (orientation){
        case 0: 
                orientation = 90;
        break;
        case 90:
             orientation = 180;
        break;
        case 180:
            orientation = 270;
        break;
        case 270:
            orientation = 0;
        break;
        default:
            orientation = orientation;
        break;
    }
    return orientation;  
}
int turn_anticlkwise_90(){
    //insert code to move

    //update and return orientation
    switch (orientation){
        case 0: 
                orientation = 270;
        break;
        case 90:
             orientation = 0;
        break;
        case 180:
            orientation = 90;
        break;
        case 270:
            orientation = 180;
        break;
        default:
            orientation = orientation;
        break;
    }
    return orientation;  
}


void move_avoid_cliff(){
   //turn 90 deg NOT on spot
    
    //turn 90 deg clock wise
}
void move_avoid_rock(){
    //turn 90 deg NOT on spot
   
   

    //turn 90 deg clock wise
}
void move_avoid_mountain(){
    //turn on spot 90 deg
    
  
}


pos update_coordinates(int orientation, int dy, int dx, pos currpos){
    switch(orientation){
        case 0: 
            currpos.y = currpos.y + dy;
        break;
        case 90: 
            currpos.x= currpos.x + dx;
        break;
        case 180: 
            currpos.y = currpos.y - dy;
        break;
        case 270:
            currpos.x= currpos.x - dx;
        break;
        default:
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
                y--;
                break;
            case 90:  // East
                x++;
                break;
            case 180:  // South
                y++;
                break;
            case 270:  // West
                x--;
                break;
        }
        if (x < 0 || x >= 300 || y < 0 || y >= 300 || matrix.grid[x][y] != NULL) {
            //300 set here as an example limit, to be changed once actual matrix size has been determined
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
    int left_unvisited = count_unvisited_in_direction(currpos, matrix, left_orientation);

    if (right_unvisited > left_unvisited) {
        return 'R';  // Turn right
    } else {
        return 'L';  // Turn left
    }
}
// can also set this to return integers if needed





 //recursive function explore
 int explore(int prev_d_i, int exp_fin, pos currpos ){
    if(exp_fin!=1){

        char c= get_c;
        double curr_topd_i = get_topd_inf();

        int delta_topd_i = delta_topd_inf(prev_d_i, curr_topd_i); //calc delta distance infrared
        
        if(delta_topd_i==0){ //if cliff, crater, nothing or potentially mountain
            if (c== 'L'){ // if cliff or crater
                
                send("cliff", c, 3, update_coordinates( orientation,  dy,  dx,  currpos ));
                 
               move_avoid_cliff();
               currpos = update_coordinates( orientation,  dy,  dx,  currpos );

            } 
            else if(get_d_ultra<6){  //mountain
                send("mountain", c, 30, update_coordinates( orientation,  dy,  dx,  currpos) );
                move_avoid_mountain();
               currpos = update_coordinates( orientation,  dy,  dx,  currpos );

            } 
            else{ //nothing
                move_forwards();
               currpos = update_coordinates( orientation,  dy,  dx,  currpos );

            }
        }
        else if(delta_topd_i == 3){
            
            send("Rock", c, 3, update_coordinates( orientation,  dy,  dx,  currpos)  );
            move_around_rock();
           currpos = update_coordinates( orientation,  dy,  dx,  currpos );

        }
        else if(delta_topd_i==6){
           send("Rock", c, 6, update_coordinates( orientation,  dy,  dx,  currpos)  )//NEED TO DEDUCT 150 from currpos;
           move_around_rock();
           currpos = update_coordinates( orientation,  dy,  dx,  currpos );

        }
    
    }
    else{
        return explore()
    }

 }


int main(void){
    //initialise matrix
     matrix_t matrix;

    for(int i=0; i<60; i++){
        for(int j=0; j<60; j++){
            
            matrix.grid[i][j]= NULL;
        }
        
    }
    pos currpos;
    currpos.x = 150;
    currpos.y= 150;
    
    int prev_d_i= get_topd_inf();

    explore(prev_d_i, exp_fin, currpos);


}
