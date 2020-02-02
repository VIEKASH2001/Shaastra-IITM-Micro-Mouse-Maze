
#define vel_motor_esq 10 //pwm pin to determine the speed to right motor  
#define vel_motor_dir 11//pwm pin to determine the speed to left motor
#define e1 8//forward run right
#define e2 9//backward run right
#define d1 12//forward run left motor
#define d2 7//backward run left motor
int trigger_frente = A4; // front ultrasonic sensor
int echo_frente = A5; // front
int trigger_esq = A2;// right
int echo_esq = A3;// right
int trigger_dir = A0;//left
int echo_dir = A1;//left
void setup()
{
pinMode(trigger_frente, OUTPUT);
pinMode(echo_frente, INPUT);
pinMode(trigger_esq, OUTPUT);
pinMode(echo_esq, INPUT);
pinMode(trigger_dir, OUTPUT);
pinMode(echo_dir, INPUT);
pinMode(vel_motor_esq, OUTPUT);
pinMode(vel_motor_dir, OUTPUT);
pinMode(e1, OUTPUT);
pinMode(e2, OUTPUT);
pinMode(d1, OUTPUT);
pinMode(d2, OUTPUT);
delay(5000);//make  it less later
}
void loop()
{
long duracao_frente, duracao_esq,
duracao_dir, direita, esquerda, frente;
digitalWrite(trigger_frente, LOW);
delayMicroseconds(2);
digitalWrite(trigger_frente, HIGH);
delayMicroseconds(5);
digitalWrite(trigger_frente, LOW);
duracao_frente = pulseIn(echo_frente, HIGH);
//stores the time duration between high and high ie, one cycle duration
frente = duracao_frente/29/2; //how formula?
digitalWrite(trigger_esq, LOW);
delayMicroseconds(2);
digitalWrite(trigger_esq, HIGH);
delayMicroseconds(5);
digitalWrite(trigger_esq, LOW);
duracao_esq = pulseIn(echo_esq, HIGH);
esquerda = duracao_esq/29/2;
digitalWrite(trigger_dir, LOW);
delayMicroseconds(2);
digitalWrite(trigger_dir, HIGH);
delayMicroseconds(5);
digitalWrite(trigger_dir, LOW);
duracao_dir = pulseIn(echo_dir, HIGH);
direita = duracao_dir/29/2;
analogWrite(vel_motor_esq, 0);
analogWrite(vel_motor_dir, 0);
analogWrite(e1, 0); //
analogWrite(e2, 0); //better use digital write
analogWrite(d1, 0); //
analogWrite(d2, 0);
if(frente >8)
{ if(direita >7 && direita< 13)
{
analogWrite(vel_motor_esq, 120);
analogWrite(vel_motor_dir, 150);
analogWrite(e1, 255);
analogWrite(e2, 0);
analogWrite(d1, 0);
analogWrite(d2, 255);
}
if(direita >=13)
{
analogWrite(vel_motor_esq, 255);
analogWrite(vel_motor_dir, 60);
analogWrite(e1, 255);
analogWrite(e2, 0);
analogWrite(d1, 0);
analogWrite(d2, 255);
}
if(direita <=7)
{
analogWrite(vel_motor_esq, 60);
analogWrite(vel_motor_dir, 255);
analogWrite(e1, 255);
analogWrite(e2, 0);
analogWrite(d1, 0);
analogWrite(d2, 255);
} }
if(esquerda <=20 && direita>20 && frente <=8)
dir();
if(esquerda >20 && direita>20 && frente <=8)
dir();
if(direita <=20 && esquerda>20 && frente <=8)
esq();
if(direita<=20 && esquerda<=20 && frente<=8)
voltar();
}
void esq()
{
analogWrite(vel_motor_esq, 120);
analogWrite(vel_motor_dir, 120);
analogWrite(e1, 0);
analogWrite(e2, 255);
analogWrite(d1, 0);
analogWrite(d2, 255);
delay(700);
}
void dir()
{analogWrite(vel_motor_esq, 120);
analogWrite(vel_motor_dir, 120);
analogWrite(e1, 255);
analogWrite(e2, 0);
analogWrite(d1, 255);
analogWrite(d2, 0);
delay(800);
}
void voltar()
{
analogWrite(vel_motor_esq, 120);
analogWrite(vel_motor_dir, 120);
analogWrite(e1, 255);
analogWrite(e2, 0);
analogWrite(d1, 255);
analogWrite(d2, 0);
delay(1200);
}
