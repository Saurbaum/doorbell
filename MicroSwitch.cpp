#include "MicroSwitch.h"

#define DEBOUNCE_TIME 50000

MicroSwitch::MicroSwitch( int pinId ) : DigitalInput( pinId ), m_debouncePending( false ), m_lastUpdate( 0 ), m_currentState( HIGH ), m_pendingState( HIGH )
{
}

void MicroSwitch::Update( long updateInterval )
{
	if( m_debouncePending )
	{
		m_lastUpdate += updateInterval;
	}
	else
	{
		m_lastUpdate = 0;
	}

	if( m_debouncePending ) {
		if( m_lastUpdate >= DEBOUNCE_TIME ) {
			m_debouncePending = false;
			if( m_pendingState == DigitalInput::GetState() )
			{
				m_currentState = m_pendingState;
				if( m_currentState == HIGH )
				{
					m_pressed = true;
				}
				else
				{
					m_pressed = false;
				}
			}
			else
			{
				m_pendingState = m_currentState;
				m_pressed = false;
			}

		}
	}

	int state = DigitalInput::GetState();

	if( state != m_pendingState ) {
		if( !m_debouncePending ) {
			m_debouncePending = true;
			m_pendingState = state;
		}
	}
};

void MicroSwitch::Reset()
{
	m_currentState = m_pendingState = DigitalInput::GetState();
};

int MicroSwitch::GetState()
{
	return m_currentState;
}

bool MicroSwitch::JustPressed()
{
	bool pressed = m_pressed;
	m_pressed = false;
	return pressed;
}

