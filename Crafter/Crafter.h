
/*
	Crafter Library 1.0 - Library for using all the Crafter Project's input and output, including DC motors.
	Implementation started at July 18th 2015
	Library implemented by:
	-Gabriel Bandeira
	e-mail: gmb@cin.ufpe.br
	github: github.com/gmbandeira

	Using Sharp Sensor Filter implemented by:
	Ivan Seidel
	github: github.com/ivanseidel

	Get to know the project and the ones responsible for it at:
	www.projetocrafter.com.br
	###@robolivre.org

	+ DC Motors Interface
	+ Digital Ultrassonic Interface (HC-SR04)
	+ Analog Infrared Interface (Sharp infrared sensor)
	+ Digital Output Interface (Simple digital output)
	+ Digital Touch Sensor Interface (Simple digital input)
	+ Analog input interface (LDR or other analog input)

	---------------------------------------------------------------------------------------------------------------------------------------

	Future versions: Crafter-1.1

	+ Sharp infrared sensor example
	+ Improve US distance measure
	+ Servo Interface
*/


#ifndef CRAFTER_1_0_H
#define CRAFTER_1_0_H


// Headers
#include <Arduino.h>		// Arduino functions like pinMode
#include <Servo.h>			// Arduino servo interface


// Definitions
// Motor default ports
#define DEF_M1_F 1
#define DEF_M1_B 2
#define DEF_M2_F 3
#define DEF_M2_B 4
// Servo default port
#define DEF_SERV 10
// Time limit for waiting ultrassonic reflection
#define US_TIME_LIMIT 20


// Enumerations
enum MOTOR {
	M1,
	M2
};


// DC motor interface
class Motor {
public:
	// Class constructor with default parameters
	Motor();
	// Class constructor using custom motor ports
	Motor(char m1f, char m1b, char m2f, char m2b);
	// Move one motor in the chosen speed. [motor = M1 | M2] [-100 < speed < 100]
	void moveMotor(MOTOR motor, int speed);
	// Move the entire robot forward or backwards. [-100 < Speed < 100]
	void run(int speed);
	// Turn the robot in the middle axis [-100 < Speed < 100]
	void turn(int speed);
	// Stop all the motors
	void stop();
	// Stop a chosen motor (M1 or M2) . [-100 < Speed < 100]
	void stop(MOTOR motor);

private:
	// Motor ports
	char _m1_f;
	char _m1_b;
	char _m2_f;
	char _m2_b;
};


// Servo interface
//class ServoMotor {
//public:
//	// Class constructor with default servo port
//	ServoMotor();
//	// Class constructor using custom servo port
//	ServoMotor(char port);
//	// Set the servo position.
//	// position: the servo position, usually: 0 < position < 180
//	void setPosition(char position);
//
//private:
//	// Servo library's servo
//	Servo* _servo;
//};


// Digital ultrassonic sensor
class US {
public:
	// Class contructor
	// trig = the pulse emissor of the sensor
	// echo = the pulse receiver of the sensor
	US(char trig, char echo);
	// Return the distance read by the ultrassonic (range 0 - 255)
	// If any error accurs, return 255
	int getDistance();

private:
	// US pins for sending and receiving ultrassonic pulses
	char _echo;
	char _trig;
	// Initial and final time for calculating the distance
	long _initialTime;
	long _finalTime;
	// Initial time to calculate the waiting limit
	long _us_InitialTime;
	// Sending, receiving or waiting states
	// TODO
	// Check if char works just fine as int worked
	char _state;
};


// Analog infrared sensor
class Sharp {
public:
	// Class constructor
	// analogInput = the analog input to read the sensor value
	Sharp(char analogInput);
	// Return the distance (value between 0 - 80)
	int getDistance();

private:
	char _port;
	double _in[12];
	double _out[12];
};


// General Purpose Digital Output
class DigitalOutput {
public:
	// Class constructor
	// port = the digital pin to use
	// onState = the boolean value to be to turn on, default is true. If false, the off value is defined as true
	DigitalOutput(char port, boolean onState = true);
	// Set a digital state (true or false)
	void setState(boolean state);

private:
	// Internal digital output
	char _port;
	// Internal on value
	boolean _onState;
};          


// General Purpose Digital Input
class DigitalInput {
public:
	// Class constructor
	// port = the digital pin to read
	// pressedState = the boolean value when is turned on, default is TRUE. If FALSE, the OFF value is defined as TRUE and the ON value as FALSE.
	DigitalInput(char port, boolean pressedState = true);
	// Get a digital state (true or false) acording to the pressedState defined above
	boolean getState();

private:
	// Internal digital input
	char _port;
	// Internal on value
	boolean _pressedState;
};


// General purpose analogic input
class AnalogicInput {
public:
	// Class constructor
	// port = the analogic pin to read
	// getPercentual = flag that indicates wheter the getValue function will return a percentual value (0-100) or the real reading value (0-1023)
	AnalogicInput(char port, boolean getPercentual = true);
	// Get the analogic reading value
	int getValue();
	
private:
	// Internal digital input
	char _port;
	// If set, returns the percentual value, else, returns the value between 0 and 1023
	boolean _getPercentual;
};

#endif

