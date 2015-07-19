
#include "Crafter.h"


// DC motor class
Motor::Motor()
{
	this->_m1_f = DEF_M1_F;
	this->_m1_b = DEF_M1_B;
	this->_m2_f = DEF_M2_F;
	this->_m2_b = DEF_M2_B;
}

Motor::Motor(char m1f, char m1b, char m2f, char m2b)
{
	this->_m1_f = m1f;
	this->_m1_b = m1b;
	this->_m2_f = m2f;
	this->_m2_b = m2b;
}

void Motor::moveMotor(MOTOR motor, int speed)
{
	switch(motor)
	{
	case M1:
		if (speed >= 0)
		{
			analogWrite(_m1_f, speed);
			analogWrite(_m1_b, 0);
		}
		else
		{
			analogWrite(_m1_f, 0);
			analogWrite(_m1_b, -speed);
		}
		break;
	case M2:
		if (speed >= 0)
		{
			analogWrite(_m2_f, speed);
			analogWrite(_m2_b, 0);
		}
		else
		{
			analogWrite(_m2_f, 0);
			analogWrite(_m2_b, -speed);
		}
		break;
	}
}

void Motor::run(int speed)
{
	if(speed > 100)
		speed = 100;
	if(speed < -100)
		speed = -100;

	this->moveMotor(M1, speed*2.55);
	this->moveMotor(M2, speed*2.55);
}

void Motor::turn(int speed)
{
	if(speed > 100)
		speed = 100;
	if(speed < -100)
		speed = -100;

	this->moveMotor(M1, speed*2.55);
	this->moveMotor(M2, -(speed*2.55));
}

void Motor::stop(MOTOR motor)
{
	this->moveMotor(motor, 0);
}

void Motor::stop()
{
	this->stop(M1);
	this->stop(M2);
}


// Servo class
//ServoMotor::ServoMotor()
//{
//	this->servo = new Servo();
//	this->_servo->attach(DEF_SERV);
//}
//
//ServoMotor::ServoMotor(char port)
//{
//	this->servo = new Servo();
//	this->_servo->attach(port);
//}
//
//void ServoMotor::setPosition(char position)
//{
//	this->_servo->write(position);
//}


// Ultrassonic sensor class
US::US(char trig, char echo)
{
	pinMode(echo, INPUT);
	pinMode(trig, OUTPUT);
	_echo = echo;
	_trig = trig;
}

int US::getDistance()
{
	_initialTime = 0;
	_finalTime = 0;
	_state = 0;

	digitalWrite(_trig, LOW);
	delayMicroseconds(2);
	digitalWrite(_trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trig, LOW);

	_us_InitialTime = millis();
	while(_state != 2 && (US_TIME_LIMIT > (millis() - _us_InitialTime)))
	{
		if(_state == 0 && digitalRead(_echo) == HIGH)
		{
			_initialTime = micros();
			_state = 1;
		}
		if(_state == 1 && digitalRead(_echo) == LOW)
		{
			_finalTime = micros();
			_state = 2;
		}
	}

	if(_finalTime < _initialTime)
		return 255;
	else if((_initialTime > 0) && (_finalTime > 0))
		return (_finalTime - _initialTime) / 35;
	else
		return  255;
}


// Analog infrared sensor class
Sharp::Sharp(char analogInput)
{
	_port = analogInput;
	_in[0] = 0.4;
	_in[1] = 0.45;
	_in[2] = 0.51;
	_in[3] = 0.61;
	_in[4] = 0.74;
	_in[5] = 0.93;
	_in[6] = 1.08;
	_in[7] = 1.31;
	_in[8] = 1.64;
	_in[9] = 2.31;
	_in[10] = 2.74;
	_in[11] = 2.97;
	_in[12] = 3.15;

	_out[0] = 80.0;
	_out[1] = 70.0;
	_out[2] = 60.0;
	_out[3] = 50.0;
	_out[4] = 40.0;
	_out[5] = 30.0;
	_out[6] = 25.0;
	_out[7] = 20.0;
	_out[8] = 15.0;
	_out[9] = 10.0;
	_out[10] = 8;
	_out[11] = 6.5;
	_out[12] = 6.1;
}

int Sharp::getDistance()
{
	double val = analogRead(_port)*0.0048828125;
	// take care the value is within range
	// constrain(val, in[0], in[13-1]);
	if (val <= _in[0])
		return _out[0] * 10;
	if (val >= _in[13-1])
		return _out[13-1] * 10;

	// search right interval
	int pos = 1;  // _in[0] allready tested
	while(val > _in[pos])
		pos++;

	// this will handle all exact "points" in the _in array
	if (val == _in[pos])
		return _out[pos];
	// interpolate in the right segment for the rest
	return 10 * ((val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1]);
}


// Digital output class
DigitalOutput::DigitalOutput(char port, boolean onState)
{
	pinMode(port, OUTPUT);
	this->_port = port;
	this->_onState = onState;
}

void DigitalOutput::setState(boolean state)
{
	if(this->_onState)
		digitalWrite(this->_port, state);
	else
		digitalWrite(this->_port, !state);
}


// Digital input class
DigitalInput::DigitalInput(char port, boolean pressedState)
{
	pinMode(port, INPUT);
	this->_port = port;
	this->_pressedState = pressedState;
}

boolean DigitalInput::getState()
{
	if(this->_pressedState)
		return digitalRead(this->_port);
	else
		return !digitalRead(this->_port);
}


// Analogic input class
AnalogicInput::AnalogicInput(char port, boolean getPercentual)
{
	this->_port = port;
	this->_getPercentual = getPercentual;
}

int AnalogicInput::getValue()
{
	int value = analogRead(this->_port);
	if(this->_getPercentual)
		return value/10.24;
	else
		return value;
}

