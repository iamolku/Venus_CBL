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
//SET TO ROCK
matrix_t setToRock(pos currpos, matrix_t matrix){
    matrix.grid[currpos.x][currpos.y] = 'R';
    //(" %c", matrix.grid[currpos.x][currpos.y]);
    return matrix;
}
//SET TO MOUNTAIN
matrix_t setToMountain(pos currpos, matrix_t matrix){
        matrix.grid[currpos.x][currpos.y] = 'M';
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

int count_unvisited_beyond_visited(pos currpos, matrix_t matrix, int orientation) {
    int count = 0;
    bool visited_encountered = false;
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

        // Stop if out of bounds
        if (x < 0 || x >= 300 || y < 0 || y >= 300) break;

        // Get the current cell value
        char cell = matrix.grid[x][y];

        // Stop counting if an obstacle is encountered
        if (cell != NULL && cell != '+') {
            break;
        }

        // Count unvisited cells only after the first visited space has been encountered
        if (cell == NULL && visited_encountered) {
            count++;
        } else if (cell == '+') {
            visited_encountered = true; // Mark that visited space is encountered, continue counting
        }
    }
    return count;
}

int count_unvisited_straight(pos currpos, matrix_t matrix, int orientation){
    int count = 0;
    bool visited_encountered = false;
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

        // Stop if out of bounds
        if (x < 0 || x >= 300 || y < 0 || y >= 300) break;

        // Get the current cell value
        char cell = matrix.grid[x][y];

        if (cell == NULL) {
            if (obstacle_encountered) {  // Start counting after an obstacle was encountered
                count++;
            }
        } else if (cell == '+' || cell == 'R' || cell == 'M' || cell == '#') {
            if (!obstacle_encountered && cell != '+') {
                // Mark the first encounter with a significant obstacle
                obstacle_encountered = true;
            } else if (obstacle_encountered) {
                // If already past an obstacle, stop counting at next significant obstacle
                break;
            }
        }
    }
    return count;
}

char optimal_direction (pos currpos, matrix_t matrix, int orientation) {
    int right_orientation = turn_clockwise_90(orientation);
    int left_orientation = turn_anticlockwise_90(orientation);

    int right_unvisited = count_unvisited_beyond_visited(currpos, matrix, right_orientation);
    int left_unvisited = count_unvisited_beyond_visited(currpos, matrix, left_orientation);
    int straight_unvisited = count_unvisited_straight(currpos, matrix, orientation);


    // Determine the best direction based on the count of unvisited spaces

    if (right_unvisited >= left_unvisited && right_unvisited >= straight_unvisited) {
        return 'R';  // Turn right
    } 

    else if (straight_unvisited > right_unvisited && straight_unvisited > left_unvisited){
        return 'S'; //Navigate around the object and move straight
    }
    else {
        return 'L';  // Turn left
    }
}


void move_forwards(){
    //move forwards 3 cm
     stepper_set_speed(25000,25000);//3072 is minimum
    stepper_steps(-162, -162); 
    
}

void move_avoid_cliff(pos currpos, matrix_t matrix, int orientation){
   //turn 90 deg on spot
    stepper_set_speed(25000,25000);//3072 is minimum
     char direction= optimal_direction(currpos,  matrix,  orientation)
    if( direction == L){
         stepper_steps(630, -630); 
    }
    else{
        stepper_steps(-630, 630); 
    }
    move_forwards();
    //turn 90 deg clock wise
}
void move_avoid_rock(pos currpos, matrix_t matrix, int orientation){
    stepper_set_speed(25000,25000);
    char direction= optimal_direction(currpos,  matrix,  orientation)
    if( direction == L){
         stepper_steps(630, -630); 
    }
    else{
        stepper_steps(-630, 630); 
    }
    move_forwards();
    

}
void move_avoid_mountain(pos currpos, matrix_t matrix, int orientation){
    stepper_set_speed(25000,25000);
    //turn on spot 90 deg
    char direction= optimal_direction(currpos,  matrix,  orientation)
    if( direction == L){
         stepper_steps(630, -630); 
    }
    else{
        stepper_steps(-630, 630); 
    }
    move_forwards();
    
  
}


 //recursive function explore
 int explore(int orientation, int prev_d_i, int exp_fin, pos currpos, pos prevpos ){
    if(exp_fin!=1){

        char c= get_c;
        double curr_topd_i = get_topd_inf();

        int delta_topd_i = delta_topd_inf(prev_d_i, curr_topd_i); //calc delta distance infrared
        
        int dy= currpos.y-prevpos.y;
        int dx= currpos.x - prevpos.x;
        
        if(delta_topd_i==0){ //if cliff, crater, nothing or potentially mountain
            if (c== 'L'){ // if cliff or crater
                
                send("cliff", c, 3, update_coordinates( orientation,  dy,  dx,  currpos ));
                 matrix_t =  setToCliff(pos currpos, matrix_t matrix);
               move_avoid_cliff();
                

            } 
            else if(get_d_ultra<6){  //mountain
                send("mountain", c, 30, update_coordinates( orientation,  dy,  dx,  currpos) );
                 matrix_t =  setToMountain(pos currpos, matrix_t matrix);
                move_avoid_mountain();
               
            } 
            else{ //nothing
                 matrix_t =  setToVisited(pos currpos, matrix_t matrix);
                move_forwards();
              
            }
        }
        else if(delta_topd_i == 3){
            
            send("Rock", c, 3, update_coordinates( orientation,  dy,  dx,  currpos)  );
            matrix_t =  setToRock(pos currpos, matrix_t matrix);
            move_around_rock();
           
        }
        else if(delta_topd_i==6){
           send("Rock", c, 6, update_coordinates( orientation,  dy,  dx,  currpos)  )//NEED TO DEDUCT 150 from currpos;
            matrix_t =  setToRock(pos currpos, matrix_t matrix);
           move_around_rock();
           

        }
        prevpos= currpos;
        currpos = update_coordinates( orientation,  dy,  dx,  currpos );
        prev_d_i= curr_topd_i;
        return explore(orientation, prev_d_i, exp_fin, currpos, prevpos);
    
    }
    else{
        return 1;
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
    pos prevpos;
    prevpos.x = 150;
    prevpos.y= 150;

    int orientation= 0;
    
    int prev_d_i= get_topd_inf();
    int exp_fin= 0;
    explore(prev_d_i, exp_fin, currpos);
    return 1;

}
