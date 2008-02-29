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

#include "Event.h"
#include "Character.h"
#include "Conversions.h"
#include "constants.h"

#include <string>
#include <list>
#include <sstream>
#include <stdio.h>

Event::Event()
{
	type = 0;
	who_id = 0;
	info = "";
}

Event::Event(int eventType, int eventWho_id, std::string eventInfo)
{
	type = eventType;
	who_id = eventWho_id;
	info = eventInfo;
}

std::string Event::Serialize(Event* event)
{
	std::string serial = "";
	serial += Conversions::IntToString(event->type) + " ";
	serial += Conversions::IntToString(event->who_id) + "\n";
	serial += event->info + " ";
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
	inStream >> temp;
	event->who_id = Conversions::StringToInt(temp);
	getline(inStream, event->info);
	return event;
}
