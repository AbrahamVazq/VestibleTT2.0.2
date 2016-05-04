////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <SdFat.h>
#include <Time.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Creamos objetos de la clase SdFat */
SdFat sd;
SdFile archivo;
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  Variables
int pulsePin = A0;                // Pulse Sensor purple wire connected to analog pin 0
int tempPin = A2;                 // Definimos la entrada anlogica en pin A0 
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
float tempC;                      // variable para el dato del Sensor
const int chipSelect = 4;         // Pin para el ChipSelect
const int botonPin = 8;           // Boton de Pausa para separar datos
int botonEstado = 0;              //Este es el estado inicial del boton de pausa
int turno;
                
// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, 
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// M A I N ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

//  Where the Magic Happens
void loop()
{
  
    serialOutput() ;   
    delay(200);
    switch(turno)
    {
      case 1:
            temperatura();
      case 2:
            pulso();
    }
    delay(20);
  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }

/////////////////////////////////////////////////////////////////////////////////////////////////////
void pulso()
{
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
        QS = false;                      // reset the Quantified Self flag for next time    
  }
     
  ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
  delay(20);                             //  take a break
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void temperatura()
{
   /*Creamos una objeto t de la clase tiempo */
    time_t t = now();
  /* Leemos el valor desde el sensor */
    tempC = analogRead(tempPin);

  /* Convierte el valor a temperatura*/
    tempC = (5.0 * tempC * 100.0)/1024.0;
  /* Datos que se mostraran en consola serial*/
    Serial.print(tempC);
    Serial.print(" Grados Celsius a las ");
    Serial.print(day(t));
    Serial.print(+ "-");
    Serial.print(month(t));
    Serial.print(+ "-");
    Serial.print(year(t));
    Serial.print(+ " ");
    Serial.print(hour(t));
    Serial.print(+ ":");
    Serial.print(minute(t));
    Serial.print(+ ":");
    Serial.print(second(t));
    Serial.print("\n");
    digitalWrite(3, HIGH);
    
   /* Re-abrimos el archivo para lectura */
  if (!archivo.open("Temperatura.txt", O_RDWR | O_CREAT | O_AT_END)) 
  {
    sd.errorHalt("opening test.txt for write failed");
  }
  
  /*Si el archivo se abrio correctamente, escribimos en el */
  Serial.print("La lectura sensa: ");
  archivo.print("\"");
  archivo.print(hour(t));
  archivo.print(+ ":");
  archivo.print(minute(t));
  archivo.print(+ ":");
  archivo.print(second(t));
  archivo.print("\"");
  archivo.print(+ " ");
  archivo.print(tempC);
  archivo.println(+ ",");

  archivo.close();
   delay(1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void interrumpe()
{
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(7,LOW);
    Serial.println(+ "]");
    Serial.println(+ "[");
    archivo.println(+ "]");
    archivo.println(+ "[");
    delay(5000);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////


