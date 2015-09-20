#ifndef __j1FILE_H__
#define __j1FILE_H__

#include "j1Module.h"

class j1File : public j1Module
{
public:

	j1File();

	// Destructor
	virtual ~j1File();

	// Called before render is available
	bool Awake();

	// Called before quitting
	bool CleanUp();

	// Load file
	SDL_RWops* LoadFile(const char* name_file);

};

#endif // __j1FILE_H__