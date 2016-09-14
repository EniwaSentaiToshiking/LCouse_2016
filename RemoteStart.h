	#ifndef REMOTESTART_H
	#define REMOTESTART_H

	#include "ev3api.h"
	#include <stdio.h>

	class RemoteStart {

	private:

	 uint8_t CMD_START;
	FILE* bt;

	public:
		RemoteStart();
		bool remote_start();
virtual ~RemoteStart();
	};

	#endif