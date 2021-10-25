#include <math.h>

#define EN 2
#define STP 17
#define DIR 4

#define E 2.71828182845904523536 //numero de Euler

//Período máximo do passo do motor
double p_maximo = 3000;
//Período mínimo do passo do motor
double p_minimo = 1000;
//define a direção do motor
int direcao = 1;
//determina se a curva será de aceleração (1) ou desaceleração (-1)
double vetor_aceleracao = 1;
//amplitude usada na equação de aceleração
double amplitude = p_maximo - p_minimo;
//determina a inclinação da curva de aceleração, o quão rápido o motor irá acelerar
double declividade =  0.0025;   // na Equação é valor de K
//Metade do número de passos (iterações) que o motor precisará para acelerar
double x_medio = 0;
double periodo = 0;
double aux = 0;

//Função necessária para calcular o período do passo do motor a cada iteração do loop (for)
double calculo_do_instante(int i){
  
  double instante = ( amplitude / ( 1 + pow( E , (vetor_aceleracao * (declividade * (i - x_medio) ) ) ) ) ) + p_minimo;
  return instante;
  
}

void setup(){
  
  pinMode(EN, OUTPUT);
  pinMode(STP, OUTPUT);
  pinMode(DIR, OUTPUT);
  //Ativa o driver DRV8825
  digitalWrite(EN, 0);
  //Define a direção
  digitalWrite(DIR, direcao);

  //Equação usada para determinar a metade do número total de passos (iterações) necessários para o movimento de aceleração
  x_medio = ((-1)*log( amplitude / ((p_maximo*0.99999) - p_minimo) -1)) / declividade;
  //É necessário recalcular a cada mudança de parâmetros de aceleração, como velocidade máxima, minima e/ou declividade
  
  delay(1000);
  
}

void loop(){

   vetor_aceleracao = 1;

  //Loop da aceleração, onde será gerado os pulsos para o driver DRV8825
  //Acelera o motor com período de 600 microssegundos para 100 microssegundos usando a curva sigmoidal
  for(int i=0;i<(x_medio*2);i++)
  {
    periodo = (calculo_do_instante(i));
    digitalWrite(STP, 1);
    delayMicroseconds(4);
    digitalWrite(STP, 0);
    delayMicroseconds(periodo);
    
  }
    //Move o motor em 200 passos com período de 100 microssegundos
  for(int i=0;i<3000;i++){
    //aux = calculo_do_instante(i);
    digitalWrite(STP, 1);
    delayMicroseconds(4);
    digitalWrite(STP, 0);
    delayMicroseconds(periodo+400);
  }

  vetor_aceleracao = -1;

  //Desacelera o motor com período de 100 microssegundos para 600 microssegundos usando a curva sigmoidal
  for(int i=0;i<(x_medio*2);i++)
  {
    periodo = (calculo_do_instante(i));
    digitalWrite(STP, 1);
    delayMicroseconds(4);
    digitalWrite(STP, 0);
    delayMicroseconds(periodo);
    
  }
  
  delay(1000);
  
}
