   
typedef struct{
    int x;
    int y;
} pos;

 //functions

 int get_topd_inf(){ //distance sensed by infrared sensor
    int d;
    uint_8 dist = uart_recv(UART1); //to change
    d= (int)dist;
    return d;
 } 

 int delta_topd_inf(int prev_d_inf, int curr_topd_inf){ //returns value in CM
    //if prev_d_inf = +-0.01m curr_topd_inf -> return 0;
    if(prev_d)

 }

 int get_d_ultra(){} //distance sensed by ultrasound sensor

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
        case r1 ... r2:
            c= 'R';
        case g1 ... g2:
            c= 'G';
        case b1 ... b2:
            c= 'B';
        case w1 ... w1:
            c= 'W';
        default:
             c= 'E';
    }

    return c;
    
 } // color sensed by color sensor

pos calculate_pos(){}
void move_normal(){}
void move_around_object(int angle_wrt_origin){
    //should ideally end up with same orientation as before
} 
void move_avoid_rock(){
    
    //turn on the spot clockwise in small pulses until IR sensor 
    while(get_topd_IR() < 25  && get_bottomd_IR()<8){
        
    }

    //turn 
}



 //recursive function explore
 int explore(int prev_d_i, int exp_fin, pos currpos ){
    if(exp_fin!=1){

        char c= get_c;
        double curr_topd_i = get_topd_inf();

        int delta_topd_i = delta_topd_inf(prev_d_i, curr_topd_i); //calc delta distance infrared



        if(delta_topd_i==0){ //if cliff, crater, nothing or potentially mountain
            if (c== 'L'){ // if cliff or crater

                //how to tell apart cliff from crater

                /*to check if its a cliff, turn 90 deg, move forwards */

                //if after 3 sets of movement, computer software detects black tape is straight or orthogonal --> cliff, else -->crater
                //
                send("cliff", c, 3, coordinates(currpos, ) );

            } 
            else if(get_d_ultra<2){  //mountain
                send("mountain", c, 30, coordinates() );
                move_avoid_rock();
            } 
            else{ //nothing
                move_forwards();
            }
        }
        else if(delta_topd_i == 3){
            
            send("Rock", c, 3, coordinates() );
            move_around_object();
        }
        else if(delta_topd_i==6){
           send("Rock", c, 6, coordinates() );
           move_around_object();
        }
        

    }
    else{
        return explore
    }

    




 }


int main(void){

    pos currpos;
    currpos.x =0;
    currpos.y= 0;

    int prev_d_i= get_topd_inf();

    explore(prev_d_i, exp_fin, currpos);






}
