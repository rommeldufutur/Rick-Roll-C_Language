#include "headers.h"

int main(int argc, char *argv[])
{
	RickRoll();
	return 0;
}

int RickRoll(void)
{
	/* Initialisation de SDL2 */
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

/* *************************************************************** */


	/* Initialisations de fenetre + image RickRoll */
	SDL_Window *window = NULL;
	window = SDL_CreateWindow("Never Gonna Give You Up !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 850, 678, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface *img = NULL;
	img = SDL_LoadBMP("rickroll.bmp");

	SDL_Texture *textureIMG = NULL;
	textureIMG = SDL_CreateTextureFromSurface(renderer,img);

	SDL_FreeSurface(img);


	if (img == NULL)
	{
		fprintf(stderr, "Erreur SDL_LoadBMP: '%s'\n",SDL_GetError());
		goto exit;
	}
	

	if (textureIMG == NULL)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface: '%s'\n", SDL_GetError());
		goto exit;
	}


/* *************************************************************** */


	/* Charger la musique du RickRoll (refraint) */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		fprintf(stderr, "Erreur Mix_OpenAudio: '%s'\n", SDL_GetError());
		goto exit;
	}
	Mix_Music *bgm = Mix_LoadMUS("rickroll.mp3");

	Mix_PlayMusic(bgm, -1);



/* *************************************************************** */


	/* boucle programme */
	unsigned int running = 1;
	while (running == true)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			running = false;
			goto exit;
		}
		/* afficher pour sûr, l'image RickRoll */
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, textureIMG, NULL, NULL);
		SDL_RenderPresent(renderer);
	}


/* *************************************************************** */


	exit:
	/* On détruit le renderer, la fenêtre, quitte SDL2, et libère de la RAM */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_FreeMusic(bgm);
	Mix_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}