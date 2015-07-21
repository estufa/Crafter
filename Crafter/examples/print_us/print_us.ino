
#include <Crafter.h>

// trig, echo
US us(4, 5);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// Print the ultrassonic sensor reading
	Serial.print("US sensor: ");
	Serial.println(us.getDistance(), DEC);
	delay(100);
}
