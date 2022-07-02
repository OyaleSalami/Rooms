#pragma once

#ifdef LINUX
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif // LINUX

#include <winsock.h>
#include "Debug.h"

///<summary>Class abstraction for a TCP Socket</summary>
class TCP
{
};