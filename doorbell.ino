#include <LinkedList.h>
#include "StateController.h"
#include "Microswitch.h"

StateController stateController;

#define MAX_TIME -1
#define SECOND_IN_MICRO 10000
#define THRESHOLD 30000

int doorSwitchPin = 5;
int bellRelayPin = 9;

unsigned long lastUpdate;

MicroSwitch* doorSwitch = new MicroSwitch( doorSwitchPin );

void setup()
{
	stateController.Register( doorSwitch );

	pinMode( bellRelayPin, OUTPUT );
}

void triggerBell()
{
	digitalWrite( bellRelayPin, 1 );

	delay( 500 );

	digitalWrite( bellRelayPin, 0 );
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
		triggerBell();
	}
	/* add main program code here */

}
