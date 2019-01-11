#include <stddef.h>
#include "Types.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <SDL_rwops.h>

#include "Config.h"
#include "WindowsWrapper.h"

bool LoadConfigData(CONFIG *conf)
{
	//Clear old config data
	memset(conf, 0, sizeof(CONFIG));
	
	//Get path
	char path[PATH_LENGTH];
	sprintf(path, "%s/%s", gModulePath, "Config.dat");
	
	//Open file
	SDL_RWops *fp = SDL_RWFromFile(path, "rb");
	if (!fp)
		return false;
	
	//Read data (we're using SDL_RWops so we can load it with the specific endianness expected)
	//Read the version id and font name
	fp->read(fp, conf->proof, sizeof(conf->proof), 1);
	fp->read(fp, conf->font_name, sizeof(conf->font_name), 1);
	
	//Read control settings
	conf->move_button_mode = SDL_ReadLE32(fp);
	conf->attack_button_mode = SDL_ReadLE32(fp);
	conf->ok_button_mode = SDL_ReadLE32(fp);
	
	//Read display mode (320x240, 640x480, 24-bit fullscreen, 32-bit fullscreen) TODO: add more things?
	conf->display_mode = SDL_ReadLE32(fp);
	
	//Read joystick configuration (if enabled, and mappings)
	conf->bJoystick = SDL_ReadLE32(fp);
	for (int button = 0; button < 8; button++)
		conf->joystick_button[button] = SDL_ReadLE32(fp);
	
	//Close file
	fp->close(fp);
	
	//Check if version is correct, return that it succeeded
	if (!strcmp(conf->proof, "DOUKUTSU20041206"))
		return true;
	
	//If not, return that it failed
	return false;
}

void DefaultConfigData(CONFIG *conf)
{
	//Claer old config data
	memset(conf, 0, sizeof(CONFIG));
	
	//Reset joystick settings (as these can't simply be set to 0)
	conf->bJoystick = 1;
	conf->joystick_button[0] = 2;
	conf->joystick_button[1] = 1;
	conf->joystick_button[2] = 5;
	conf->joystick_button[3] = 6;
	conf->joystick_button[4] = 3;
	conf->joystick_button[5] = 4;
	conf->joystick_button[6] = 6;
	conf->joystick_button[7] = 3;
}
