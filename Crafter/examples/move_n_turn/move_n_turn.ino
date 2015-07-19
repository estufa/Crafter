
#include <Crafter.h>

Motor motor;

void setup()
{
	
}

void loop()
{
	// Move forward
	motor.run(100);
	delay(1000);

	// Stop
	motor.stop();

	// Turn right
	motor.turn(100);
	delay(1000);

	// Stop
	motor.stop();
	delay(5000);
}
