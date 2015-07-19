
#include <Crafter.h>

// M1-forward, M1-backwards, M2-forward, M2-backwards
Motor motor (6, 7, 8, 9);
// trig, echo
US us(11, 12);

void setup()
{
	
}

void loop()
{
	// Move forward
	motor.run(100);

	// While it's not seing anything,
	while(us.getDistance() > 15)
		// Just wait between sensor readings to avoid echo
		delay(10);

	// If got out of the loop, stop for a while
	motor.stop();
	delay(20000);
}
