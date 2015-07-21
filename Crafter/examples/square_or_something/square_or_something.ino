
#include <Crafter.h>

// M1-forward, M1-backwards, M2-forward, M2-backwards
Motor motor (6, 7, 11, 12);

void setup()
{
	
}

void loop()
{
	for (int i = 0; i < 4; i++)
	{
		// Move forward
		motor.run(100);
		delay(100);

		// Stop
		motor.stop();
		delay(100);

		// Turn right
		motor.moveMotor(M1, 100);
		motor.stop(M2);
		delay(1000);
	}

	// Stop
	motor.stop();
	delay(5000);
}
