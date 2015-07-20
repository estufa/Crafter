
#include <Crafter.h>

// M1-forward, M1-backwards, M2-forward, M2-backwards
Motor motor (6, 7, 8, 9);
// Digital input (Touch sensor)
DigitalInput button(11);
// trig, echo
US us(11, 12);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// Move forward at 60% full speed
	motor.run(60);

	// While it's not hitting anything,
	while(!button.getState())
		// Print the ultrassonic sensor reading
		Serial.println(us.getDistance(), DEC);

	// If got out of the loop, stop for a while
	motor.stop();
	delay(5000);
}
