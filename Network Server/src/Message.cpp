#include "Message.h"

namespace Network
{

	void Message::Clear()
	{
		buffer.clear();
		readHead = 0;
	}
}