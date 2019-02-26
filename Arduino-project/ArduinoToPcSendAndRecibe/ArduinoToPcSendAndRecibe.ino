/*Pedro Martinez ©2019
 * This project is prepared to receive in a simple way 3 states marked as 
 * LED1, LED 2 and Led3 and is ready to send a byte array of 10.
If you wish to modify the code, you are free to do so.
*/
byte data[] = {0xFF, 50, 100, 150, 200, 250,7,8,9,0xFF};

String inputString = ""; 
boolean stringComplete = false;
String commandString = ""; //accion


// DIGITAL OUTPUTS FROM PC APP
int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {

if(stringComplete)
    {
      stringComplete = false;  
      getCommand();

       if(commandString.equals("STAR"))// BUCLE DENTRO
          {
             digitalWrite(13,HIGH);
          }
       if(commandString.equals("STOP"))// BUCLE APAGAR
          {
                digitalWrite(2,LOW);
                digitalWrite(3,LOW);
                digitalWrite(4,LOW);
                digitalWrite(13,LOW);   
          }   
       else if(commandString.equals("LED1")){estadoLed(LED1);}
       else if(commandString.equals("LED2")){estadoLed(LED2);}
       else if(commandString.equals("LED3")){estadoLed(LED3);}
        
       else if (commandString == "GETI"){
        Serial.flush();
        Serial.write(data, sizeof(data) / sizeof(data[0]));
        
        for(int i=0; i<=sizeof(data)-1; i++){// incremento automatico
          data[i]= data[i] +1;
        }
      }
      inputString = "";  
      }
}


void estadoLed(int pinLed){
  boolean LedState = getLedState();
              if(LedState == true)
              {
                digitalWrite(pinLed,HIGH);
                Serial.println(commandString+" ON");
                
              }else
              {
                digitalWrite(pinLed,LOW);
                Serial.println(commandString+" OFF");
              }
}

void getCommand()//1
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
}
void serialEvent() { //2
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

boolean getLedState()
  {
    boolean state = false;
    if(inputString.substring(5,7).equals("ON"))
    {
      state = true;
    }else
    {
      state = false;
    }
    return state;
  }
