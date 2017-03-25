#include <LinkedList.h>
#include "StateController.h"
#include "Microswitch.h"

StateController stateController;

#define MAX_TIME -1
#define SECOND_IN_MICRO 10000
#define THRESHOLD 30000

#define TRIGGER_THREASHOLD 13

int doorSwitchPin = 5;
int bellRelayPin = 9;

unsigned long lastUpdate;

MicroSwitch* doorSwitch = new MicroSwitch( doorSwitchPin );

int triggerCount = 0;

void setup()
{
	stateController.Register( doorSwitch );

	pinMode( bellRelayPin, OUTPUT );
}

void triggerBell(unsigned long length)
{
	digitalWrite( bellRelayPin, 1 );

	delay( length );

	digitalWrite( bellRelayPin, 0 );
}

void triggerFancyBell()
{
	triggerBell( 250 ); // Shave
	delay( 50 );
	triggerBell( 125 ); // and
	delay( 50 ); 
	triggerBell( 125 ); // a
	delay( 50 );
	triggerBell( 125 ); // hair-
	delay( 50 );
	triggerBell( 125 ); // -cut
}

void loop()
{
	unsigned long now = micros();
	long updateTime = 0;

	if( now < lastUpdate ) {
		updateTime = now + ( MAX_TIME - lastUpdate );
	}
	else {
		updateTime = now - lastUpdate;
	}

	lastUpdate = now;

	stateController.Update( updateTime );

	if( doorSwitch->JustPressed() )
	{
		if( triggerCount++ > TRIGGER_THREASHOLD )
		{
			triggerFancyBell();
			triggerCount = 0;
		}
		else
		{
			triggerBell(1000);
		}
	}
}
