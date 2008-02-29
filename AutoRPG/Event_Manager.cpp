/*
Copyright 2007, 2008 Andrew Allen and Brian Shourd

This file is part of AutoRPG.

AutoRPG is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AutoRPG is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with AutoRPG (Called LICENSE.txt).  If not, see
<http://www.gnu.org/licenses/>.
*/

#include "Event_Manager.h"
#include "Event.h"

#include <string>
#include <list>
#include <map>
#include <stdio.h>

Event_Manager::Event_Manager(std::map<int, Character*>* pCharacterMap)
{
    characterMap = pCharacterMap;
}

void Event_Manager::AddEvent(std::string eventSerial)
{
	eventList.push_back(Event::Deserialize(eventSerial));
}

void Event_Manager::AddEvent(Event* event)
{
	eventList.push_back(event);
}

void Event_Manager::PollEvent()
{
	Event* event = *eventList.begin();
	eventList.erase(eventList.begin());
	switch (event->type)
	{
	case ATTACK:
//		characterMap->find(who_id)->second->Attack(info);	//These are all special functions that take in serialized data, then deserialize it and
        printf("Character with id %i Attacked!\n", event->who_id);
		break;
	case DEFEND:
//		characterMap->find(who_id)->second->Defend(info);
        printf("Character with id %i Defended!\n", event->who_id);
		break;
	case TAKEDAMAGE:
//		characterMap->find(who_id)->second->TakeDamage(info);
        printf("Character with id %i Took Damage!\n", event->who_id);
		break;
	case DEATH:
//		characterMap->find(who_id)->second->Death(info);
        printf("Character with id %i Died!\n", event->who_id);
		break;
	case SPAWN:
//		characterMap.insert(characterMap.begin(), std::pair<std::string, Character*>(event->who_id, info));
        printf("Character with id %i Spawned!\n", event->who_id);
		break;
	case MOVEMENT:
//		characterMap->find(who_id)->second->Movement(info);
        printf("Character with id %i Moved!\n", event->who_id);
		break;
	case CHAT:
//		characterMap->find(who_id)->second->Chat(info);
        printf("Character with id %i Chatted!\n", event->who_id);
		break;
	default:
		break;
	}

	delete event;	//This should be the only remaining pointer to this event, and it is deleted here to avoid memory leaks
}
