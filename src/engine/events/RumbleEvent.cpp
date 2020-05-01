#include "RumbleEvent.h"
#include "Event.h"

using namespace std;

RumbleEvent::RumbleEvent(string type, EventDispatcher* source, float intensity, int duration) : Event(type, source) {
	this->intensity = intensity;
    this->duration = duration;
}