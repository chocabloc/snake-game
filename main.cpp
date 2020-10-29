#include <iostream>
#include "main.h"
#include <cmath>
#include <string>
#include <cstring>

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif

#include <vector>

using namespace std;

SDL_Window* window=NULL;

SDL_Surface* surface=NULL;

SDL_Surface* imgSnake=NULL;

SDL_Surface* texSurface=NULL;

SDL_Surface* pauseSurface=NULL;

TTF_Font* font;
TTF_Font* font1;

vector<point> seg;
vector<point> segc;
int key=3;
int frame=0;
int score=0;
SDL_Event e;
bool foodraw=true,ateitself=false,paused=false,pupdated=false;
SDL_Rect fr={.x=0,.y=0,.w=16,.h=16};
SDL_Rect draw={.x=300,.y=250,.w=0,.h=0};
void move(){
	point seg_prev=seg[0];
	point seg_prev_old=seg[0];
	switch(key){
		case 0:
		seg[0].y-=16;
		break;

		case 1:
		seg[0].y+=16;
		break;

		case 2:
		seg[0].x-=16;
		break;

		case 3:
		seg[0].x+=16;
		break;
	}
	for(int i=0;i<seg.size();i++){
		if(i>0){
			seg_prev_old=seg[i];
			seg[i]=seg_prev;
			seg_prev=seg_prev_old;
		}
	}
}
void incSegment(){
	point last=seg[seg.size()-1];
	move();
	seg.push_back(last);
}
void update(){
	if(foodraw){
		fr.x=(rand()%25)*16;
		fr.y=(rand()%37)*16;
		incSegment();
		foodraw=false;
	}
	else{
		SDL_BlitScaled(imgSnake,&APPLE,surface,&fr);
	}
	SDL_Rect r;
	for(int i=0;i<seg.size();i++){

		r.x=seg[i].x;
		r.y=seg[i].y;
		r.w=16;
		r.h=16;
		if(i==0){
			if(seg[0].x==fr.x && seg[0].y==fr.y){
				foodraw=true;
				score++;
				texSurface=TTF_RenderText_Blended(font,(string("Score: ")+to_string(score)).c_str(),{0,0,0});
			}

			if(seg[1].x<seg[0].x && seg[1].y==seg[0].y)
				SDL_BlitScaled(imgSnake,&SNAKE_HR,surface,&r);

			else if(seg[1].x>seg[0].x && seg[1].y==seg[0].y)
				SDL_BlitScaled(imgSnake,&SNAKE_HL,surface,&r);

			else if(seg[1].x==seg[0].x && seg[1].y<seg[0].y)
				SDL_BlitScaled(imgSnake,&SNAKE_HD,surface,&r);

			else if(seg[1].x==seg[0].x && seg[1].y>seg[0].y)
				SDL_BlitScaled(imgSnake,&SNAKE_HU,surface,&r);
		}
		else{
			if(seg[0].x==seg[i].x && seg[0].y==seg[i].y){
				segc=seg;
				segc.resize(i,point(0,0));
				ateitself=true;
				score=i-2;
				texSurface=TTF_RenderText_Blended(font,(string("Score: ")+to_string(score)).c_str(),{0,0,0});
				break;
			}
			if(i==seg.size()-1){
				if(seg[i-1].x<seg[i].x && seg[i-1].y==seg[i].y)
					SDL_BlitScaled(imgSnake,&SNAKE_TR,surface,&r);

				else if(seg[i-1].x>seg[i].x && seg[i-1].y==seg[i].y)
					SDL_BlitScaled(imgSnake,&SNAKE_TL,surface,&r);

				else if(seg[i].x==seg[i-1].x && seg[i-1].y<seg[i].y)
					SDL_BlitScaled(imgSnake,&SNAKE_TD,surface,&r);
				
				else if(seg[i].x==seg[i-1].x && seg[i-1].y>seg[i].y)
					SDL_BlitScaled(imgSnake,&SNAKE_TU,surface,&r);
			}
			else{
				if((seg[i].x>seg[i+1].x && seg[i].y<seg[i-1].y) || (seg[i].x>seg[i-1].x && seg[i].y<seg[i+1].y))
					SDL_BlitScaled(imgSnake,&SNAKE_BEND_DL,surface,&r);

				else if((seg[i].x<seg[i+1].x && seg[i].y<seg[i-1].y) || (seg[i].x<seg[i-1].x && seg[i].y<seg[i+1].y))
					SDL_BlitScaled(imgSnake,&SNAKE_BEND_DR,surface,&r);

				else if((seg[i].x>seg[i-1].x && seg[i].y>seg[i+1].y) || (seg[i].x>seg[i+1].x && seg[i].y>seg[i-1].y))
					SDL_BlitScaled(imgSnake,&SNAKE_BEND_UL,surface,&r);

				else if((seg[i].x<seg[i-1].x && seg[i].y>seg[i+1].y) || (seg[i].x<seg[i+1].x && seg[i].y>seg[i-1].y))
					SDL_BlitScaled(imgSnake,&SNAKE_BEND_UR,surface,&r);

				else if(seg[i].y==seg[i+1].y)
					SDL_BlitScaled(imgSnake,&SNAKE_HOR,surface,&r);

				else if(seg[i].x==seg[i+1].x)
					SDL_BlitScaled(imgSnake,&SNAKE_VER,surface,&r);

			}
		}
	}
	if(ateitself){
		seg=segc;
		ateitself=false;
	}
	move();
	SDL_BlitSurface(texSurface,NULL,surface,NULL);
}

void quit(){
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}
void mainloop(){
	if(!paused){
		frame++;
		if(frame>5){
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 144, 173, 47));
			update();
			frame=0;
		}
		SDL_UpdateWindowSurface(window);
		pupdated=false;
	}
	else{
		SDL_BlitSurface(pauseSurface,NULL,surface,&draw);
		if(!pupdated){SDL_UpdateWindowSurface(window); pupdated=true;}
	}
	
	while( SDL_PollEvent( &e ) != 0 ){
	 	if(e.type==SDL_QUIT){
	 		quit();
	 		exit(0);
	 	}
        else if( e.type == SDL_KEYDOWN )
        {
            //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                	//if(key!=1)
					key=0;
                break;

                case SDLK_DOWN:
                	//if(key!=0)
					key=1;
                break;

                case SDLK_LEFT:
                	//if(key!=3)
					key=2;
                break;

                case SDLK_RIGHT:
                	//if(key!=2)
					key=3;
                break;

				case SDLK_p:
					paused=!(paused);
				break;
            }
        }
    }
}

void init(){
	seg.push_back(point(128,64));
	seg.push_back(point(112,64));

	if(SDL_Init(SDL_INIT_VIDEO<0)){
		cout << "SDL could not start" << endl;
		exit(-1);
	}
	TTF_Init();
	window=SDL_CreateWindow("Snake",0,0,W_WIDTH,W_HEIGHT,SDL_WINDOW_SHOWN);

	if(window==NULL){
		cout << "Unable to create Window" << endl;
		exit(-1);
	}

	surface=SDL_GetWindowSurface(window);
}


void loadMedia(){
	imgSnake = SDL_LoadBMP( "assets/snake.bmp" );
	font= TTF_OpenFont("assets/font.ttf", 25);
	font1= TTF_OpenFont("assets/font.ttf", 75);
	if(imgSnake==NULL)cout << "Unable to load image" << endl;
}

int main(){
	init();
	loadMedia();
	srand(time(0));
	texSurface=TTF_RenderText_Blended(font,(string("Score: ")+to_string(score)).c_str(),{0,0,0});
	pauseSurface=TTF_RenderText_Blended(font1,"Paused",{0,0,0});
	#ifdef __EMSCRIPTEN__

		emscripten_set_main_loop(mainloop,0,1);

	#else

		while(true){
			mainloop();
			SDL_Delay(16);
		}

	#endif

	quit();

	return 0;
}
