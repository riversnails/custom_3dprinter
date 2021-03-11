unsigned long c_millis = 0;
unsigned long p_millis = 0;
int duty = 22;

void setup()
{
  DDRB |= 0x10;
  
  TCCR2A = 0x02;
  TCCR2B = 0x02;
  OCR2A = 64;
  //TCNT2 = 256 - 64;
  TIMSK2 = 0x02;
}

void loop() // 빈 코드
{
  c_millis = millis();
  if(c_millis - p_millis > 10)
  {
    p_millis = c_millis;

    duty++;
    if(duty == 72) duty = 22;
  }
}

int count = 0;

// ISR(TIMER2_OVF_vect)
// {
// 	TCNT2 = 256 - 64; 

// 	count++;
// 	if(count == 625)
// 	{
// 		count = 0;
// 		PORTB = 0x10;
// 	}
// 	else if(count == duty) // 22는 왼쪽, 72는 오른쪽, 47는 가운데
// 	{
// 		PORTB = 0;
// 	}

// }

ISR(TIMER2_COMPA_vect)
{ 

   count++;
   if(count == 625)
   {
     count = 0;
     PORTB = 0x10;
   }
   else if(count == duty) // 22는 왼쪽, 72는 오른쪽, 47는 가운데
   {
     PORTB = 0;
   }

}