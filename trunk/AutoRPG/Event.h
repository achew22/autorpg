#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <list>

struct Event
{
public:
	int type;
	std::string who_id;
	std::string info;	//This info is a serialized version of the information to be passed with the function that ought to be called by the event
	static std::list<Event*> eventList;

	Event();
	Event(int eventType, std::string eventWho_id, std::string eventInfo);
	std::string Serialize();
	static Event* Deserialize(std::string eventSerial);
	static void AddEvent(std::string eventSerial);
	static void AddEvent(Event* event);
	static void PollEvent();
};

#endif
