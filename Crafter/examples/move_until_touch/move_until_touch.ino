
#include <Crafter.h>


// M1-forward, M1-backwards, M2-forward, M2-backwards
Motor motor (6, 7, 8, 9);
// Digital input (Touch sensor)
DigitalInput button(11);
// Digital output (LED)
DigitalOutput led(13);


void setup()
{
	
}

void loop()
{
	// Move forward
	motor.run(100);

	// While it's not seing anything,
	while(!button.getState())
		// Just wait between sensor readings to avoid echo
		delay(10);

	// If got out of the loop, stop for a while
	motor.stop();
	blink_led(5);
	delay(20000);
}


void blink_led(unsigned int times)
{
	for(unsigned int i = 0; i < times; i++)
	{
		led.setState(true);
		delay(100);
		led.setState(false);
		delay(100);
	}
}
