//lil playground for me before I put these into the actual code

char detected_left_sensor(pos currpos, matrix_t matrix, int orientation){
  char c;
  //moves slightly backward
  stepper_steps(80,80);

  //turns 10deg or so to the left
  stepper_steps(0,-66);

  //gets the color
  c = get_c();

  //turns back
  stepper_steps(0,66);
  
  //moves back forward
  stepper_steps(-80, -80);
  return c;
}

char detected_right_sensor(pos currpos, matrix_t matrix, int orientation){
  char c;
  stepper_steps(80,80);

  stepper_steps(-66, 0);

  c = get_c();

  stepper_steps(66,0);
  
  stepper_steps(-80, -80);
  return c;

}
