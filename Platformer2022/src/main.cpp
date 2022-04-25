#define PLAYGROUND 0

#if PLAYGROUND == 1
	#include "Playground.h"
#else
	#include "Game.h"
#endif // PLAYGROUND

int main()
{
	int screen_w = 424;
	int screen_h = 240;
	int pixel_w = 3;
	int pixel_h = 3;

	bool fullscreen = false;
	bool vsync = true;

#if PLAYGROUND == 1
	Playground pg;
	if (pg.Construct(screen_w, screen_h, pixel_w, pixel_h, fullscreen, vsync))
		pg.Start();
#else
	if (game->Construct(screen_w, screen_h, pixel_w, pixel_h, fullscreen, vsync))
		game->Start();
	delete game;
#endif // PLAYGROUND			
	return 0;
}