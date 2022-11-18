#include <Servo.h>
const int buzzer = 13;
int x = 0;
// =============================================================================================================
// --- Mapeamento de Hardware ---
#define ch1   8 //Canal 1 do rádio instanciado à entrada digital 2
#define ch2   9 //Canal 2 do rádio instanciado à entrada digital 3
#define ch3   10 //Canal 3 do rádio instanciado à entrada digital 4
#define ch4   11 //Canal 4 do rádio instanciado à entrada digital 5
#define ch5   12 //Canal 5 do rádio instanciado à entrada digital 6
#define ch6   13 //Canal 6 do rádio instanciado à entrada digital 7


// =============================================================================================================

//------ pinos dos controles dos motores--------
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

// ----- variaveis de voo -------

int potv4 = 0; //potencia geral dos 4 motores
int potm1 = 0; //potencia do motor 1
int potm2 = 0; //potencia do motor 2
int potm3 = 0; //potencia do motor 3
int potm4 = 0; // potencia do motor 4
//-----------------------------------------


// --- Protótipo das funções auxiliares ---
void read_channels();      //Função para leitura das entradas dos canais
void test_channels();      //Testa os 8 canais do Turnigy9x

// =============================================================================================================
// --- Declaração de variáveis globais ---
short       change_ch = 0x00,   //variável para determinar qual canal será lido
            counterT2 = 0x00;

//variáveis para os canais do rádio
int         canal_01 , 
            canal_02 , 
            canal_03 , 
            canal_04 , 
            canal_05 , 
            canal_06 ;
         


// =============================================================================================================
// --- Interrupção ---
ISR(TIMER2_OVF_vect)
{
    TCNT2 = 0x64;          // Reinicializa o registrador do Timer2
    counterT2++;

    if(counterT2 == 10)
    { 
      counterT2 = 0x00;
     // read_channels();
    }
       
   if(canal_01 > 1500) digitalWrite(13, HIGH);
   else digitalWrite(13, LOW);

   

    
    
    
} //end ISR
    

// =============================================================================================================
// --- Configurações iniciais ---
void setup()
{ 
  pinMode(buzzer,OUTPUT);
  tone(buzzer,500);   
  delay(100);
  noTone(buzzer);
  delay(100);  
   tone(buzzer,500);   
  delay(100);
  noTone(buzzer);
  delay(100);  
  // -- Direção dos I/Os --
  pinMode(ch1, INPUT); //Entrada para o canal 1 do rádio
  pinMode(ch2, INPUT); //Entrada para o canal 2 do rádio
  pinMode(ch3, INPUT); //Entrada para o canal 3 do rádio
  pinMode(ch4, INPUT); //Entrada para o canal 4 do rádio
  pinMode(ch5, INPUT); //Entrada para o canal 5 do rádio
  pinMode(ch6, INPUT); //Entrada para o canal 6 do rádio

   motor1.attach(4);
   motor2.attach(5);
   motor3.attach(6);
   motor4.attach(7);

  pinMode(13, OUTPUT);
      
  Serial.begin(9600);            //Inicia comunicação Serial com 9600 de baud rate


    // -- Registradores de configuração do Timer2 --
     TCCR2A = 0x00;   //Timer operando em modo normal
     TCCR2B = 0x07;   //Prescaler 1:1024
     TCNT2  = 0x64;   //10 ms overflow again
     TIMSK2 = 0x01;   //Habilita interrupção do Timer2
   
   
  
} //end setup


// =============================================================================================================
// --- Loop Infinito ---
void loop()
{

  //---- potencia dos motores ------
    motor1.write(potv4);
    motor2.write(potv4);
    motor3.write(potv4);
    motor4.write(potv4);
  
  //-----------------------------

    
    read_channels();
    test_channels(); //Envia informação para o Serial Monitor

//------comando de partida(centralizando os joystick para baixo/centro)----------------------------------------------
    if(canal_01 < 1000)
   {if(canal_02 < 1000)
    {if(canal_03 < 1000)
      {if(canal_04 > 1900){ 
      Serial.print("----teste de comando de partida-01---------  ");
      delay(1000);
      read_channels();
    test_channels();
         if(canal_01 < 1000){
    if(canal_02 < 1000){
      if(canal_03 < 1000){
        if(canal_04 > 1900){
         x++;
     if(x == 1)
     {
     tone(buzzer,400);   
     delay(800);
     noTone(buzzer);
     
   potv4 = 60; //libera potencia dos motores em 30% 
  
      Serial.print("----teste de comando de partida concluido iniciando partida---  ");
      delay(8 00);
           }else{
            potv4 = 0;// desliga a potencia dos motores
            x = 0; //  zera a variavel
            pinMode(buzzer,OUTPUT);
       tone(buzzer,500);   
       delay(100);
       noTone(buzzer);
       delay(100);  
         tone(buzzer,900);   
       delay(100);
     noTone(buzzer);
     delay(100);  
      tone(buzzer,500);   
       delay(100);
     noTone(buzzer);
    
           }
           
           }}}}}}}}
//-----------------------------------------------------------------------------------------    
    //delay(3000);


    
    
    
} //end loop


// =============================================================================================================
// --- Funções Auxiliares ---
void read_channels()                                            //Faz a leitura dos 6 primeiros canais do rádio
{
 
      canal_01 = pulseIn(ch1, HIGH, 50000);     //Lê pulso em nível alto do canal 1 e armazena na variável canal_01
      canal_02 = pulseIn(ch2, HIGH, 50000);     //Lê pulso em nível alto do canal 2 e armazena na variável canal_02
      canal_03 = pulseIn(ch3, HIGH, 50000);   //Lê pulso em nível alto do canal 3 e armazena na variável canal_03
      canal_04 = pulseIn(ch4, HIGH, 50000);     //Lê pulso em nível alto do canal 4 e armazena na variável canal_04
      canal_05 = pulseIn(ch5, HIGH, 50000);     //Lê pulso em nível alto do canal 5 e armazena na variável canal_05
      canal_06 = pulseIn(ch6, HIGH, 50000);     //Lê pulso em nível alto do canal 6 e armazena na variável canal_06

} //end read channels


void test_channels() //Testa os canais via serial monitor (comentar esta função e só chamar quando necessário)
{
  
      Serial.println("=================");
      Serial.print("Canal 01:  ");
      Serial.println(canal_01);
      Serial.print("Canal 02:  ");
      Serial.println(canal_02);
      Serial.print("Canal 03:  ");
      Serial.println(canal_03);
      Serial.print("Canal 04:  ");
      Serial.println(canal_04);
      Serial.print("Canal 05:  ");
      Serial.println(canal_05);
      Serial.print("Canal 06:  ");
      Serial.println(canal_06);

   
} //end test_channels

 
   
 
