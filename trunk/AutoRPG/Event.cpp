#include "Event.h"
#include "Character.h"
#include "Conversions.h"
#include "constants.h"

#include <string>
#include <list>
#include <sstream>
#include <stdio.h>

std::list<Event*> Event::eventList;

Event::Event()
{
	type = 0;
	who_id = "";
	info = "";
}

Event::Event(int eventType, std::string eventWho_id, std::string eventInfo)
{
	type = eventType;
	who_id = eventWho_id;
	info = eventInfo;
}

std::string Event::Serialize()
{
	std::string serial = "";
	serial += Conversions::IntToString(type) + " ";
	serial += who_id + "\n";
	serial += info + " ";
	return serial;
}

//The event looks like this:
//"priority eventType who_id"
//"Info1 info2 info3 ...."
Event* Event::Deserialize(std::string eventSerial)
{
	Event* event = new Event();
	std::string temp;
	std::stringstream inStream;
	inStream.str(eventSerial);
	inStream >> temp;
	event->type = Conversions::StringToInt(temp);
	inStream >> event->who_id;
	getline(inStream, event->info);
	return event;
}

void Event::AddEvent(std::string eventSerial)
{
	eventList.push_back(Deserialize(eventSerial));
}

void Event::AddEvent(Event* event)
{
	eventList.push_back(event);
}

void Event::PollEvent()
{
	Event* event = *eventList.begin();
	eventList.erase(eventList.begin());
	switch (event->type)
	{
	case ATTACK:
//		characterMap[event->who_id]->Attack(info);	//These are all special functions that take in serialized data, then deserialize it and
        printf("Character with id %s Attacked!\n", event->who_id.c_str());
		break;
	case DEFEND:
//		characterMap[event->who_id]->Defend(info);
        printf("Character with id %s Defended!\n", event->who_id.c_str());
		break;
	case TAKEDAMAGE:
//		characterMap[event->who_id]->TakeDamage(info);
        printf("Character with id %s Took Damage!\n", event->who_id.c_str());
		break;
	case DEATH:
//		characterMap[event->who_id]->Death(info);
        printf("Character with id %s Died!\n", event->who_id.c_str());
		break;
	case SPAWN:
//		characterMap.insert(characterMap.begin(), std::pair<std::string, Character*>(event->who_id, info));
        printf("Character with id %s Spawned!\n", event->who_id.c_str());
		break;
	case MOVEMENT:
//		characterMap[event->who_id]->Movement(info);
        printf("Character with id %s Moved!\n", event->who_id.c_str());
		break;
	case CHAT:
//		characterMap[event->who_id]->Chat(info);
        printf("Character with id %s Chatted!\n", event->who_id.c_str());
		break;
	default:
		break;
	}

	delete event;	//This should be the only remaining pointer to this event, and it is deleted here to avoid memory leaks
}
