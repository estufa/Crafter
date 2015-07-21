
#include <Crafter.h>

AnalogicInput irLine(A0);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// Print the line infrared reading
	Serial.print("Line sensor: ");
	Serial.println(irLine.getValue(), DEC);
	delay(100);
}
