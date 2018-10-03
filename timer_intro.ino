/* Arduino 101: timer and interrupts
   1: Timer1 compare match interrupt example 
   more infos: http://www.letmakerobots.com/node/28278
   created by RobotFreak 
*/
#define ledPin 13

// min timer:  1 ms.
// max timer:  4 seconds.
void init_timer( int exp_ms )
{
  float hz;
  int   prescaler=1024;
  float cmp_flt;
  unsigned int   cmp_int;
  
  if ((exp_ms < 1) || (exp_ms > 4000))
  {
    // Error!
    return;
  }

  hz = 1000.0/(float)exp_ms;
  
  cmp_flt = 16000000/prescaler;
  cmp_flt = cmp_flt / hz;

  cmp_int = (int) cmp_flt;

  
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = cmp_int;            // compare match register 16MHz/1024/hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (B00000101);    // 1024 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts  
}

void setup()
{
  Serial.begin(9600);
  
  init_timer(250);
  
  pinMode(ledPin, OUTPUT);

}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
}

void loop()
{
  // your program here…
}
