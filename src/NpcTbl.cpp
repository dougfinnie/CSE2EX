#include <string>

#include <SDL_rwops.h>

#include "NpcTbl.h"

NPC_TABLE *gNpcTable;

bool LoadNpcTable(const char *path)
{
	SDL_RWops *fp = SDL_RWFromFile(path, "rb");

	if (fp == nullptr)
	{
		printf("LoadNpcTable failed\nSDL Error: %s\n", SDL_GetError());
		return false;
	}

	const size_t tblSize = SDL_RWsize(fp);

	const int npcCount = tblSize / 0x18;
	gNpcTable = (NPC_TABLE*)malloc(npcCount * sizeof(NPC_TABLE));

	for (size_t i = 0; i < npcCount; i++) //bits
		gNpcTable[i].bits = SDL_ReadLE16(fp);
	for (size_t i = 0; i < npcCount; i++) //life
		gNpcTable[i].life = SDL_ReadLE16(fp);
	for (size_t i = 0; i < npcCount; i++) //surf
		fp->read(fp, &gNpcTable[i].surf, 1, 1);
	for (size_t i = 0; i < npcCount; i++) //destroy_voice
		fp->read(fp, &gNpcTable[i].destroy_voice, 1, 1);
	for (size_t i = 0; i < npcCount; i++) //hit_voice
		fp->read(fp, &gNpcTable[i].hit_voice, 1, 1);
	for (size_t i = 0; i < npcCount; i++) //size
		fp->read(fp, &gNpcTable[i].size, 1, 1);
	for (size_t i = 0; i < npcCount; i++) //exp
		gNpcTable[i].exp = SDL_ReadLE32(fp);
	for (size_t i = 0; i < npcCount; i++) //damage
		gNpcTable[i].damage = SDL_ReadLE32(fp);
	for (size_t i = 0; i < npcCount; i++) //hit
		fp->read(fp, &gNpcTable[i].hit, 4, 1);
	for (size_t i = 0; i < npcCount; i++) //view
		fp->read(fp, &gNpcTable[i].view, 4, 1);
		
	SDL_RWclose(fp);	
	return true;
}

void ReleaseNpcTable()
{
	if (gNpcTable)
		free(gNpcTable);
}
