setup()
{
	DDRB |= 0x20;

	TCCR2A = 0x00;
	TCCR2B = 0x07;
	TIMSK2 = 0x01; 
}

loop() // 타이머를 이용하여 깜빡이는 코드
{
	// PORTB |= 0x20;
	// delay(1000);
	// PORTB = PORTB & (~0x20);//포트b 읽기, not취함, 앤드취함, 대입함 = 4번 계산함
	// PORTB &= ~0x20;//더 간략해짐
	// delay(1000);

	// 이제 타이머 사용
	// 원하는 시간에 인터럽트 


	// 0x23 : 0010|0011
	// 0x20 : 0010|0000
	// ----------------
	// &    : 0010|0000	=> 대입  

	// ! : 논리연산자 (!0x23 => 0)
	// ~ : 비트 연산자(~0x23 =>1101|1100:0xDC)

	// 0x23 : 0010|0011
	// ~0x20 : 0010|0000 = 1101|1111
	// ----------------
	// &    : 0000|0011
	// 결론 : 내가 특정값을 비트연산후 앤드를 취하면 그 값만 빼냄
}

int count = 0;
int toggle = 0;

SIGNAL(TIMER2_OVF_vect)
{
	count++;
	if(count == 61)
	{
		count = 0;
		if(toggle == 0)
		{
			toggle = 1;
			PORTB |= 0x20;
		}
		else
		{
			toggle = 0;
			PORTB &= ~0x20;
		}
	}
}