

int wait = 200;
 
// high pins for leds
// 2 - highest; layey 3 - middle; 4 - lowest
int h[] = {2,3,4};

/* 
green - face wall

low pins for leds
[ 13  12  11] red
[  7   6   5] yellow
[ 10   9   8] green

*/

int layer[3][3] = {13, 12, 11, 7, 6, 5, 10, 9, 8}; // 


// setup all at first
void setup() 
{                

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){

      pinMode(layer[i][j], OUTPUT);
      digitalWrite(layer[i][j], HIGH);
    }
  }
  for (int i = 0; i < 3; i++){
    pinMode(h[i], OUTPUT);
    digitalWrite(h[i], LOW);
  }

}

// disable all leds
void clear_all()
{
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      digitalWrite(layer[i][j], HIGH);
    }
  }
  for (int i = 0; i < 3; i++) digitalWrite(h[i], LOW);
}


// things for layers down up animation
void layers_down()
{
  
  for (int x = 0; x < 2; x++){

    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){

        digitalWrite(layer[i][j], LOW);

      }
    }

    for (int i = 0; i < 3; i++) digitalWrite(h[x], LOW);

    digitalWrite(h[x], HIGH);
    delay(wait);

  clear_all();
  }
}

void layers_up()
{
  for (int x = 2; x > 0; x--){

    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){

        digitalWrite(layer[i][j], LOW);

      }
    }

    for (int i = 0; i < 3; i++) digitalWrite(h[x], LOW);

    digitalWrite(h[x], HIGH);
    delay(wait);

  clear_all();
  }
}

void prepare_layers_anim()
{
  digitalWrite(h[2], LOW);
  delay(wait);
  digitalWrite(h[1], LOW);
  delay(wait);
  for (int i = 0; i<3;i++)
  {
    digitalWrite(layer[i][2], LOW);
    delay(wait);
  }
  for (int i = 0; i<3;i++)
  {
    digitalWrite(layer[i][0], LOW);
    delay(wait);
  }
}

void layers_down_up(int reps)
{
  for (int i = 0; i < reps; i++)
  {
    layers_down();
    layers_up();

  }
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){

      digitalWrite(layer[i][j], LOW);
    }
  }
  digitalWrite(h[0], HIGH);
}
// end layers down up


// things for fan animation
void light_centre_z()
{
  clear_all();
  for (int i = 0; i<3;i++) digitalWrite(layer[i][1], LOW);
  for (int i = 0; i<3;i++) digitalWrite(h[i], HIGH);
}

void light_centre_x()
{
  clear_all();
  for (int i = 0; i<3;i++) digitalWrite(layer[1][i], LOW);
  for (int i = 0; i<3;i++) digitalWrite(h[i], HIGH);
}

void light_diagonal_0_2()
{
  clear_all();
  for (int i = 0; i<3;i++) digitalWrite(layer[i][i], LOW);
  for (int i = 0; i<3;i++) digitalWrite(h[i], HIGH);
}

void light_diagonal_2_0()
{
  clear_all();
  for (int i = 0; i<3;i++) digitalWrite(layer[2-i][i], LOW);
  for (int i = 0; i<3;i++) digitalWrite(h[i], HIGH);
}

void prepare_fan_anim()
{
  for (int i = 0; i< 3; i++)
  {
    for (int j = 0; j<3;j++)
    {
      if (i + j !=2)
      {
      digitalWrite(layer[i][j], HIGH);
      delay(wait);
      }      
    }
  }
  digitalWrite(h[1], HIGH);
  delay(wait);
  digitalWrite(h[2], HIGH);
  delay(wait);
}

void fan(int reps)
{
  for (int i = 0; i < reps; i++)
  {  
    light_diagonal_2_0();
    delay(wait);
    light_centre_z();
    delay(wait);
    light_diagonal_0_2();
    delay(wait);
    light_centre_x();
    delay(wait);
  }
}
// fan end

// main loop
void loop(){
      

  prepare_fan_anim();
  fan(3);
  
  prepare_layers_anim();
  layers_down_up(3);

}
