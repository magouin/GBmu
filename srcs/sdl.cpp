#include <Emulateur.hpp>

uint8_t	Emulateur::color_htor(uint32_t color)
{
	return (color >> 24);
}

uint8_t	Emulateur::color_htog(uint32_t color)
{
	return ((color >> 16) & 0xff);
}

uint8_t	Emulateur::color_htob(uint32_t color)
{
	return ((color >> 8) & 0xff);
}

uint8_t	Emulateur::color_htoa(uint32_t color)
{
	return (color & 0xff);
}

uint32_t Emulateur::color_5_to_8(uint16_t gb_color)
{
	uint32_t color_r, color_g, color_b;

	color_r = ((gb_color & 0x001f) * 255) / 31;
	color_g = ((gb_color & 0x03e0) * 255) / 31;
	color_b = ((gb_color & 0x7c00) * 255) / 31;

	return ((color_r < 24) | (color_g < 16) | (color_b < 8) | 0xff);
}

void	Emulateur::sdl_init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Impossible to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	if (!(_window = SDL_CreateWindow("GBmu v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GB_WINDOW_SIZE_X, GB_WINDOW_SIZE_Y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN)))
	{
		fprintf(stderr, "Error on window creation: %s\n", SDL_GetError());
		exit(1);
	}
	if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
	{
		fprintf(stderr, "Error on renderer creation: %s\n", SDL_GetError());
		exit(1);
	}
	if (!(_surface = SDL_CreateRGBSurfaceWithFormat(0, 160, 144, 32, SDL_PIXELFORMAT_RGBA32)))
	{
		fprintf(stderr, "Error on surface creation: %s\n", SDL_GetError());
		exit(1);
	}
}

bool	Emulateur::update()
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
			SDL_Log("Poulet\n");
		else if (e.type == SDL_QUIT)
		{
			printf("Event SDL_QUIT\n");
			return (false);
		}
    }
	return (true);
}

void	Emulateur::set_pixel(uint32_t pixel, uint16_t x, uint16_t y)
{
	_pixels_map[y * GB_WINDOW_SIZE_X + x] = pixel;
}

void	Emulateur::render()
{
    SDL_RenderClear(_renderer);

	SDL_LockSurface(_surface);
	memcpy(_surface->pixels, _pixels_map, sizeof(_pixels_map));
	SDL_UnlockSurface(_surface);

	SDL_Texture *tmp_texture = SDL_CreateTextureFromSurface(_renderer, _surface);
	int w, h;
	SDL_GetWindowSize(_window, &w, &h);
	SDL_Rect rect_window = {0, 0, w, h};
	SDL_RenderCopy(_renderer, tmp_texture, NULL, &rect_window);

	SDL_RenderPresent(_renderer);

	SDL_DestroyTexture(tmp_texture);
}