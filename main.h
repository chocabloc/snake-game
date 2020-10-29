#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define W_WIDTH 800
#define W_HEIGHT 600

const struct SDL_Rect BUSH={.x=0,.y=128,.w=64,.h=64};
const struct SDL_Rect GRASS={.x=0,.y=128,.w=64,.h=64};
const struct SDL_Rect APPLE={.x=0,.y=192,.w=64,.h=64};

const struct SDL_Rect SNAKE_HR={.x=256,.y=0,.w=64,.h=64};
const struct SDL_Rect SNAKE_HL={.x=192,.y=64,.w=64,.h=64};
const struct SDL_Rect SNAKE_HU={.x=192,.y=0,.w=64,.h=64};
const struct SDL_Rect SNAKE_HD={.x=256,.y=64,.w=64,.h=64};

const struct SDL_Rect SNAKE_VER={.x=128,.y=64,.w=64,.h=64};
const struct SDL_Rect SNAKE_HOR={.x=64,.y=0,.w=64,.h=64};

const struct SDL_Rect SNAKE_BEND_DR={.x=0,.y=0,.w=64,.h=64};
const struct SDL_Rect SNAKE_BEND_DL={.x=128,.y=0,.w=64,.h=64};

const struct SDL_Rect SNAKE_BEND_UR={.x=0,.y=64,.w=64,.h=64};
const struct SDL_Rect SNAKE_BEND_UL={.x=128,.y=128,.w=64,.h=64};

const struct SDL_Rect SNAKE_TR={.x=192,.y=192,.w=64,.h=64};
const struct SDL_Rect SNAKE_TL={.x=256,.y=128,.w=64,.h=64};
const struct SDL_Rect SNAKE_TU={.x=256,.y=192,.w=64,.h=64};
const struct SDL_Rect SNAKE_TD={.x=192,.y=128,.w=64,.h=64};

class point{
public:
	int x;
	int y;
	point(int X,int Y){
		x=X;
		y=Y;
	}
};