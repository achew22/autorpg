#ifndef EVENT_H
#define EVENT_H

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
