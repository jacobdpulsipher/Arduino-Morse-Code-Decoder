/*
 * MORSE DECODER:
 * 
 * BY: Jacob Pulsipher
 * Date: 4/13/2021
 * 
 * DESCRIPTION:
 * 
 * This simple arduino project will convert morse code via light into words that are printed in the Serial Moniter. The signaler just has to 
 * follow the tempo of the LED and signal for the appropriate amount of time for a dot, dash, and separations. This project does not yet support
 * spaces. I have tried signaling to it with a morse code translator app, but due to the complications of timing and syncronization, I have yet
 * to get that much working.
 * 
 */





int reader = A0; //Pin used to read data coming from the photoresistor.
int configure = 2; //Used to throw an interrupt that adjusts the photoresistor to ambient light
int LED = 8; //Flashes a light to show the morse code tempo.

long SIGNAL_SPEED = 500;
int data = 0;  //Current analogRead from the photoresistor is stored in this variable
int index = 0; //Used to keep track of the index of symbol[]
char symbol[4]; //The various dashes and dots are stored in this char list to be sent off to translate()
unsigned long clk = 0;
int cOn = 0; //Count of how many times the microcontroller reads the light being on
int cOff = 0; //Count of how many times the microcontroller reads the light being off
bool flash = false; //Used to determine the state of the LED: ON/OFF
int threshold = 0;

void setup() 
{
  pinMode(reader, INPUT);
  pinMode(configure, INPUT);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(configure), adjust, FALLING);
  Serial.begin(9600);
}

void loop() {
  
  while (true)
  {
    digitalWrite(LED, flash= flash^1);
    delay(3);
    digitalWrite(LED, flash= flash^1);
    data = analogRead(reader);
    clk = millis();
    if (data > threshold) //Light is on
    {
      cOn += 1;
    }
    else if (data < threshold) //Light is Off
    {
      if (cOn == 1)
      {
        //Add a dot
        symbol[index] = '.';
        index++;
        cOn = 0;
      }
      else if (cOn >= 3)
      {
        //Add a dash
        symbol[index] = '-';
        index++;
        cOn = 0;
      }
      else if (cOn == 0)
      {
        cOff++;
      }
      else{}
    if (cOff == 3) // End of letter
    {
      //Uses the symbols to print out a letter
      char code[4] = {symbol[0], symbol[1], symbol[2], symbol[3]};
      translate(code);
      //Serial.print(code);
      for (int i = 0; i < 4; i++)
      {
        symbol[i] = 95;
      }
      //Serial.println();
      cOff = 0;
      index = 0;
      break;
    }
    
      
    }
    while((millis() - clk) < SIGNAL_SPEED){} //While loop will repeat after SIGNAL_SPEED ms have passed.
  }
}

/******************************
 * This is used to adjust the photoresistor for ambient light.
 *****************************/
void adjust()
{
  Serial.println("CONFIGURED");
  threshold = (50 + analogRead(A0)); //"ON" is defined as 50 over the ambient analogRead measure.
  
}


/*********************************************************
 * translate() takes in a list of chars, and then uses a series of if statements, to determine what letter has been signaled.
 ********************************************************/
char translate(char info[4])
{
  //Serial.println(info);
  if (info[0] == '.')
  {
    if (info[1] == '.')
    {
          if (info[2] == '.')
          {
            if (info[3] == '.')
            {
              Serial.print("H");
            }
            else if (info[3] == '-')
            {
              Serial.print("V");
            }
            else if (info[3] == '_')
            {
              Serial.print("S");
            }
          }
          else if (info[2] == '-')
          {
            if (info[3] == '.')
            {
              Serial.print("F");         
            }
            else if (info[3] == '-')
            {
              Serial.print("INVALID");
            }
            else if (info[3] == '_')
            {
              Serial.print("U");
            }
          }
          
          else if (info[2] == '_')
          {
            Serial.print("I");
          }             
    }
    else if (info[1] == '-')
    {
          if (info[2] == '.')
          {
            if (info[3] == '.')
            {
              Serial.print("L");
            }
            else if (info[3] == '-')
            {
              Serial.print("INVALID");
            }
            else if (info[3] == '_')
            {
              Serial.print("R");
            }
          }
          else if (info[2] == '-')
          {
            if (info[3] == '.')
            {
              Serial.print("P");         
            }
            else if (info[3] == '-')
            {
              Serial.print("J");
            }
            else if (info[3] == '_')
            {
              Serial.print("W");
            }
          }
          
          else if (info[2] == '_')
          {
            Serial.print("A");
          }

    }
    else if (info[1] == '_')
    {
      Serial.print("E");
    }
  }

else if (info[0] == '-')
  {
    if (info[1] == '.')
    {
          if (info[2] == '.')
          {
            if (info[3] == '.')
            {
              Serial.print("B");
            }
            else if (info[3] == '-')
            {
              Serial.print("X");
            }
            else if (info[3] == '_')
            {
              Serial.print("D");
            }
          }
          else if (info[2] == '-')
          {
            if (info[3] == '.')
            {
              Serial.print("C");         
            }
            else if (info[3] == '-')
            {
              Serial.print("Y");
            }
            else if (info[3] == '_')
            {
              Serial.print("K");
            }
          }
          
          else if (info[2] == '_')
          {
            Serial.print("N");
          }             
    }
    else if (info[1] == '-')
    {
          if (info[2] == '.')
          {
            if (info[3] == '.')
            {
              Serial.print("Z");
            }
            else if (info[3] == '-')
            {
              Serial.print("Q");
            }
            else if (info[3] == '_')
            {
              Serial.print("G");
            }
          }
          else if (info[2] == '-')
          {
            if (info[3] == '.')
            {
              Serial.print("INVALID");         
            }
            else if (info[3] == '-')
            {
              Serial.print("INVALID");
            }
            else if (info[3] == '_')
            {
              Serial.print("O");
            }
          }
          
          else if (info[2] == '_')
          {
            Serial.print("M");
          }

    }
    else if (info[1] == '_')
    {
      Serial.print("T");
    }
  }
}
