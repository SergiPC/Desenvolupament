#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1File.h"

#include "SDL/include/SDL.h"
#include "PhysFS/include/physfs.h"
#pragma comment( lib, "PhysFs/libx86/physfs.lib" )

j1File::j1File() : j1Module()
{}

// Destructor
j1File::~j1File()
{}

// Called before render is available
bool j1File::Awake()
{
	LOG("Loading File");
	bool ret = true;
	PHYSFS_init(NULL);

	if (PHYSFS_init(NULL) == 0)
	{
		LOG("PHYSFS could not initialize! PHYSFS error: %s\n", PHYSFS_getLastError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool j1File::CleanUp()
{
	LOG("Freeing File");
	bool ret = true;
	PHYSFS_deinit();

	if (PHYSFS_deinit() == 0)
	{

		LOG("PHYSFS could not freeing! PHYSFS error: %s\n", PHYSFS_getLastError());
		ret = false;
	}

	return ret;
}

// Load file
SDL_RWops* j1File::LoadFile(const char* name_file)
{	
	SDL_RWops* tmp_io;

	// 1.- Open the file with PhysFS:
	PHYSFS_File* ptr_file = PHYSFS_openRead(name_file);

	if (ptr_file == NULL)
	{
		LOG("PHYSFS_openRead could not open file! PHYSFS error: %s\n", PHYSFS_getLastError());
		return NULL;
	}

	// 2.- Calculate the size:
	// PHYSFS_sint64: a signed, 64-bit integer type.
	PHYSFS_sint64 file_size = PHYSFS_fileLength(ptr_file);

	// 3.- Reservation of required memory and read the whole file.
	PHYSFS_sint64 file_required_mem = PHYSFS_read(ptr_file, tmp_io, file_size, 1);

	if (file_required_mem < 0)
	{
		LOG("PHYSFS_File could not be read! PHYSFS error: %s\n", PHYSFS_getLastError());
		return NULL;
	}

	// 4.- Close the file.
	PHYSFS_File* new_ptr_file = ptr_file;
	PHYSFS_close(ptr_file);

	if (PHYSFS_close(ptr_file) == 0)
	{
		LOG("PHYSFS_File could not be closed! PHYSFS error: %s\n", PHYSFS_getLastError());
		return NULL;
	}

	// 5.- Create a RWops from memory.
	SDL_RWops* new_io = SDL_RWFromConstMem(new_ptr_file, file_size);
	
	return;
}
