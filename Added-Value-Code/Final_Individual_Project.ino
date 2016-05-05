#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include<LiquidCrystal.h>


Adafruit_DRV2605 drv;

//Initializing all variables and constants.
const int ramp_button=8;
const int buzz_button=9;
const int burst_button=10;

int ramp_buttonstate=0;
int buzz_buttonstate=0;
int burst_buttonstate=0;

const int LED_green=13;
const int LED_red=12;
const int buzzer=11;

LiquidCrystal lcd(2,3,4,5,6,7);



//This is the function that creates the ramp effect on the vibration motor.
void ramp()
{
  drv.setWaveform(0,84);
  drv.setWaveform(1,1);
  drv.setWaveform(2,0);
  drv.go();
  delay(2000);
}



//This is the function the creates the steady buzz on the vibration motor.
void buzz()
{
  drv.setWaveform(0,16);
  drv.setWaveform(1,0);
  drv.go();
  delay(2000);
}



//The creates the burst of short buzzes on the vibration motor.
void burst()
{
  drv.setWaveform(0,12);
  drv.setWaveform(1,0);
  drv.go();
  delay(1000);
  drv.setWaveform(0,12);
  drv.setWaveform(1,0);
  drv.go();
  delay(1000);
}



/* 
The starting sequence of the Game. 
This shows the words 'GAME START!' on the LCD screen.
The words blink twice before staying on for 2 seconds.
*/
void starting_sequence()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("GAME START!");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("GAME START!");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("GAME START!");
  delay(2000);
}



/*
This function calls one of the three output functions depending on what the input is.
If the input is 0, it calls on the ramp function.
If the input is 1, it calls on the buzz function.
If the input is 2, it calls on the burst function.
 */
void output(int n)
{
  if (n==0)
  ramp();
  else if (n==1)
  buzz();
  else if (n==2)
  burst();
}



/*
In each level of the game, you need to input the current sequency of outputs.
This sequency could have anywhere between 4 and 10 outputs.
This function tell the user which output in the sequence they have to enter.
 */
void input_number(int b)
{
 
  if(b==0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1st INPUT:");
  }
  else if(b==1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("2nd INPUT:");
  }
  else if(b==2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("3rd INPUT:");
  }
  else if(b==3)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("4th INPUT:");
  }
  else if(b==4)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("5th INPUT:");
  }
  else if(b==5)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("6th INPUT:");
  }
  else if(b==6)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("7th INPUT:");
  }

  lcd.setCursor(0,1);
  lcd.print("KEEP IT PRESSED");
  delay(1000);
}



/*
In the case that the player presses the wrong button, or if the button is not pressed long enough,
the game ends.
This function creates the ending sequence of the game.
First, the red LED and buzzer are turned on for 2 seconds,
then, the words 'GAME OVER" appear on the screen. These words blink twice before staying on until the game is reset.
 */
void game_over()
{
  digitalWrite(LED_green,LOW); 
  digitalWrite(LED_red,HIGH);
  tone(buzzer,262);
  delay(2000);                   
  digitalWrite(LED_red,LOW);
  noTone(buzzer);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("GAME OVER!");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("GAME OVER!");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("GAME OVER!");
  delay(1000);
  exit(0);
}



/*
This is the main function that controls the game.
For each level, there are 5 sets that you have to input correctly.
This function creates and outputs each of the five sets to the vibration motor.
For each set, it calls the input_number function to tell the user which output in the sequence they have to press.
It checks the input, and then calls the game_over function if the output is wrong.
If the sequence is right, it moves on until all 5 sets have been inputted correctly.
 */
void output_sequence(int i)
{
  for(int z=0;z<5;z++)
  {
    digitalWrite(LED_green,LOW);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("SET");
    lcd.setCursor(4,1);
    lcd.print(z+1);
    delay(2000);
    
    int j=3+i;                           //# of outputs for this level
    int seq[j];
    for(int n=0;n<j;n++)
    {
      int r;
      r=random(3);
      seq[n]=r;                           //Output sequence
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("OUTPUT");
      lcd.setCursor(7,1);
      lcd.print(n+1);
      output(r);                         //Output
      delay(1000);
    }

    digitalWrite(LED_green,HIGH);        //Ready for the input
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TIME TO");
    lcd.setCursor(0,1);
    lcd.print("REMEMBER!");
    delay(3000);

    for(int b=0;b<j;b++)
    {
      input_number(b);
      delay(1000);
      ramp_buttonstate=digitalRead(ramp_button);
      buzz_buttonstate=digitalRead(buzz_button);
      burst_buttonstate=digitalRead(burst_button);
      if(seq[b]==0)
      {
        if (ramp_buttonstate!=1)
        {
          game_over();
        }
      }
      if(seq[b]==1)
      {
        if (buzz_buttonstate!=1)
        {
          game_over();
        }
      }
      if(seq[b]==2)
      {
        if (burst_buttonstate!=1)
        {    
          game_over();
        }
      }
    }
  }
}




/*
This function is called if the user wins the game. 
The game ends with the words 'GAME WON!!!' shown on the screen.
The game will have to be restarted if the user wishes to play again.
 */
void game_won()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("YOU WON!!!");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("YOU WON!!!");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("YOU WON!!!");
  exit(0);
}



//Here we set up all the output and input pins, as well as the LCD and haptic motor driver.
void setup() 
{
  Serial.begin(9600);
  
  pinMode(LED_green,OUTPUT);
  pinMode(LED_red,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(ramp_button,INPUT);
  pinMode(buzz_button,INPUT);
  pinMode(burst_button,INPUT);

  lcd.begin(16,2);
  
  drv.begin();
  drv.setMode(DRV2605_MODE_INTTRIG);
  drv.selectLibrary(1);
}




/*
This loop controls the main levels of the game. 
First, it plays the starting sequence.
Then, it runs through the different levels in the game, of which there are 7.
For each level, it displays the level number of the LCD before calling the output_sequence function.
If the level is completed successfully, it moves on to the next level.
If the game is one, it calls on the game_won function.
 */
void loop() 
{
  starting_sequence();
  
  for(int i=1;i<8;i++)                   //Which level
  {
    digitalWrite(LED_green,LOW);
    lcd.clear();                         //Print Level
    lcd.setCursor(0,1);
    lcd.print("LEVEL ");
    lcd.setCursor(6,1);
    lcd.print(i);
    delay(2000); 
    output_sequence(i);
  }

  game_won();

}
