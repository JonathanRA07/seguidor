﻿#include <16f887.h>
//#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO
#fuses BROWNOUT, HS, NOWDT, NOLVP
#use DELAY(clock = 4000000)
#byte trisb=0x86
#byte portb=0x06

int Timer2,Poscaler;

int16 extremo_izq;
int16 extremo_der;

int16 extremo_med_izq;
int16 extremo_med_der;

int16 extremo_extremo_izq;
int16 extremo_extremo_der;


void main(void){
Timer2=249;
Poscaler=1;
setup_timer_2(t2_div_by_4,Timer2,Poscaler);

//CONFIGURAR PUERTOS
setup_adc_ports(sAN1|sAN2 |sAN3 |sAN4 |sAN5 |sAN6 |sAN7 |  VSS_VDD);
setup_adc(adc_clock_internal);//CONF PUERTOS ANALOGICOS
setup_ccp1(ccp_pwm);
setup_ccp2(ccp_pwm);
int velocidad=100;



//PARA INICIALIZAR CALIBRACION
do{

}while(INPUT(PIN_B0)==1);


output_high(PIN_B2);
delay_ms(400);
output_low(PIN_B2);
delay_ms(400);

output_high(PIN_B2);
delay_ms(400);
output_low(PIN_B2);
delay_ms(400);

output_high(PIN_B2);
delay_ms(400);
output_low(PIN_B2);
delay_ms(400);

//3 extremo derecho
//5 extremo izquierdo
while(1){
        set_adc_channel(7); 
        extremo_extremo_izq=read_adc(); 
        
        set_adc_channel(6); 
        extremo_med_izq=read_adc(); 

        set_adc_channel(5); 
        extremo_izq=read_adc(); 
        
        set_adc_channel(3);
        extremo_der=read_adc(); 
        
        set_adc_channel(2); 
        extremo_med_der=read_adc(); 
        
        set_adc_channel(1); 
        extremo_extremo_der=read_adc(); 
        
  //si se va para la izquierda, regresar hacia derecha
  if(extremo_izq>240)
  {
     //IZQUIERDO hacia atras
        output_low(PIN_B3);
        output_high(PIN_B4); 
        set_pwm2_duty(velocidad+30); 
    //derecha para adelante
        output_high(PIN_A0);
        output_low(PIN_B5);
        set_pwm1_duty(velocidad);
  }
  //si se va a la derecha, regresar a la izquierda
  else if(extremo_der>240)
  {
     //IZQUIERDO hacia enfrente
         output_high(PIN_B3);
         output_low(PIN_B4); 
    //este es pwm de la izquierda
        set_pwm2_duty(velocidad);
        
    //derecha para atras
        output_low(PIN_A0);
        output_high(PIN_B5);
              //este es pwm de la derecha
        set_pwm1_duty(velocidad+30);
  }
  
   //si se va a la derecha, regresar a la izquierda
   else if(extremo_med_der>240)
  {
    //asda
     //IZQUIERDO hacia enfrente
         output_high(PIN_B3);
         output_low(PIN_B4); 
    //este es pwm de la izquierda
        set_pwm2_duty(velocidad);
        
    //derecha para atras
        output_low(PIN_A0);
        output_high(PIN_B5);
              //este es pwm de la derecha
        set_pwm1_duty(velocidad+60);
  }
   //si se va para la izquierda, regresar hacia derecha
  else if(extremo_med_izq>240)
  {
     //IZQUIERDO hacia atras
         output_low(PIN_B3);
         output_high(PIN_B4); 
    //este es pwm de la izquierda
        set_pwm2_duty(velocidad);
        
    //derecha para adelante
        output_high(PIN_A0);
        output_low(PIN_B5);
              //este es pwm de la derecha
        set_pwm1_duty(velocidad+60);
  }
   //si se va a la derecha, regresar a la izquierda
   else if(extremo_extremo_der>240)
  {
    //asda
     //IZQUIERDO hacia enfrente
         output_high(PIN_B3);
         output_low(PIN_B4); 
    //este es pwm de la izquierda
        set_pwm2_duty(velocidad-20);
        
    //derecha para atras
        output_low(PIN_A0);
        output_high(PIN_B5);
              //este es pwm de la derecha
        set_pwm1_duty(velocidad+120);
  }
   //si se va para la izquierda, regresar hacia derecha
   else if(extremo_extremo_izq>240)
  {
     //IZQUIERDO hacia atras
         output_low(PIN_B3);
         output_high(PIN_B4); 
    //este es pwm de la izquierda
        set_pwm2_duty(velocidad-20);
        
    //derecha para adelante
        output_high(PIN_A0);
        output_low(PIN_B5);
              //este es pwm de la derecha
        set_pwm1_duty(velocidad+120);
  }
  else{
      //derecha para adelante
        output_high(PIN_A0);
        output_low(PIN_B5);
              //este es pwm de la derecha
        set_pwm1_duty(velocidad); 
     //IZQUIERDO hacia enfrente
         output_high(PIN_B3);
         output_low(PIN_B4); 
    //este es pwm de la izquierda
        set_pwm2_duty(velocidad);
  }
}

}
