#include <Emulateur.hpp>

#define SDL_ERROR_CHECK(x) if ( (r = (x)) ) printf("Error %x -- at line %d -- %s\n", r, __LINE__, SDL_GetError());

void	Emulateur::sdl_init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Impossible to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	#ifdef _MSC_VER
	if (!(_window = SDL_CreateWindow("GBmu v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GB_WINDOW_SIZE_X * 4, GB_WINDOW_SIZE_Y * 4, SDL_WINDOW_SHOWN)))
	#endif
	#ifdef __GNUC__
	if (!(_window = SDL_CreateWindow("GBmu v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GB_WINDOW_SIZE_X * 4, GB_WINDOW_SIZE_Y * 4, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN)))
	#endif
	{
		fprintf(stderr, "Error on window creation: %s\n", SDL_GetError());
		exit(1);
	}
	if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)))
	{
		fprintf(stderr, "Error on renderer creation: %s\n", SDL_GetError());
		exit(1);
	}
	if (!(_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING | SDL_TEXTUREACCESS_TARGET, GB_WINDOW_SIZE_X, GB_WINDOW_SIZE_Y)))
	{
		fprintf(stderr, "Error on surface creation: %s\n", SDL_GetError());
		exit(1);
	}
}

void	Emulateur::fill_input_from_key(SDL_Keycode sym, SDL_EventType t)
{
	static uint8_t freq = 0;

	if (t == SDL_KEYDOWN)
	{
		if (sym == SDLK_t)
			_test++;
		else if (sym == SDLK_h)
		{
			freq = (1 + freq) % 4;
			// freq = (1 + freq) % 5;
			printf("_frequency >> 22: %d -> ", _frequency >> (22 + (cgb.on && (gb_regs.key1 & 0x80))));
			_frequency = (0x400000 << (freq + (cgb.on && (gb_regs.key1 & 0x80))));
			printf("%d\n", (_frequency >> (22 + (cgb.on && (gb_regs.key1 & 0x80)))));
			_start_time = std::chrono::system_clock::now();
		}
		if (sym == SDLK_UP)
			input.p14 &= ~IO_UP;
		else if (sym == SDLK_DOWN)
			input.p14 &= ~IO_DOWN;
		else if (sym == SDLK_LEFT)
			input.p14 &= ~IO_LEFT;
		else if (sym == SDLK_RIGHT)
			input.p14 &= ~IO_RIGHT;
		else if (sym == SDLK_a)
			input.p15 &= ~IO_A;
		else if (sym == SDLK_b || sym == SDLK_x)
			input.p15 &= ~IO_B;
		else if (sym == SDLK_p)
			input.p15 &= ~IO_START;
		else if (sym == SDLK_o)
			input.p15 &= ~IO_SELECT;
		else if (sym == SDLK_y)
			_step_by_step = true;
		else
			return ;
		if ((!(gb_regs.p1.select == P14) && (sym == SDLK_UP || sym == SDLK_DOWN || sym == SDLK_RIGHT || sym == SDLK_LEFT)) || (!(gb_regs.p1.select == P15) && (sym == SDLK_a || sym == SDLK_b || sym == SDLK_p || sym == SDLK_o)))
			gb_regs.iflag.io = true;
		_stop_status = false;
	}
	else
	{
		if (sym == SDLK_UP)
			input.p14 |= IO_UP;
		else if (sym == SDLK_DOWN)
			input.p14 |= IO_DOWN;
		else if (sym == SDLK_LEFT)
			input.p14 |= IO_LEFT;
		else if (sym == SDLK_RIGHT)
			input.p14 |= IO_RIGHT;
		else if (sym == SDLK_a)
			input.p15 |= IO_A;
		else if (sym == SDLK_b || sym == SDLK_x)
			input.p15 |= IO_B;
		else if (sym == SDLK_p)
			input.p15 |= IO_START;
		else if (sym == SDLK_o)
			input.p15 |= IO_SELECT;
	}
}

void	Emulateur::quit()
{
	_MBC.save();
	exit(1); // TODO peut etre d'autres trucs a faire
}

bool	Emulateur::update()
{
	SDL_Event	e;

	SDL_WaitEvent(&e);
	switch (e.type)
	{
		case SDL_KEYDOWN:
			fill_input_from_key(e.key.keysym.sym, SDL_KEYDOWN);
			break;
		case SDL_KEYUP:
			fill_input_from_key(e.key.keysym.sym, SDL_KEYUP);
			break;
		case SDL_QUIT:
			printf("Event SDL_QUIT\n");
			quit();
		default:
			break;
	}
	return (true);
}

void	Emulateur::set_pixel(uint32_t pixel, uint16_t x, uint16_t y)
{
	_pixels_map[y * GB_WINDOW_SIZE_X + x] = pixel;
}

void	Emulateur::render()
{
	static auto										start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point			now;
	static std::chrono::system_clock::time_point	exec;
	int												w, h, r;
	static uint64_t									x = 0;

	x++;
	if (_exec_frame)
	{
		_exec_frame = false;
		_step_by_step = true;
	}
	now = std::chrono::system_clock::now();
	if (_exec_second)
	{
		_exec_second = false;
		exec = now;
	}
	else if (exec != std::chrono::system_clock::time_point() &&
		std::chrono::duration_cast<std::chrono::milliseconds>(now - exec).count() > 1000)
	{
		_step_by_step = true;
		exec = std::chrono::system_clock::time_point();
	}
	if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > 1000)
	{
		printf("FPS: %lld\n", x);
		x = 0;
		start = now;
	}
	SDL_RenderClear(_renderer);
	SDL_ERROR_CHECK(SDL_UpdateTexture(_texture, NULL, _pixels_map, sizeof(uint32_t) * GB_WINDOW_SIZE_X))
	SDL_GetWindowSize(_window, &w, &h);
	SDL_Rect rect_window = {0, 0, w, h};
	SDL_ERROR_CHECK(SDL_RenderCopy(_renderer, _texture, NULL, &rect_window))
	SDL_RenderPresent(_renderer);
}
