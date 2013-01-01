#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
//#define GL_GLEXT_PROTOTYPES
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>


#include "structs.h"
#include "ball.h"

#include "defines.h"
#include "functions.h"
#include "functionsp.h"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_SetVideoMode(DEF_WIDTH, DEF_HEIGHT, 0, SDL_OPENGL | SDL_DOUBLEBUF);


	if(loadGLFunctions()) return 15;

	glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
	glViewport(0.0f, 0.0f, (float)DEF_WIDTH, (float)DEF_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, DEF_WIDTH, DEF_HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	BallList BL;
	BL.setRAll(BALLS_R);
	BL.InitDL();
	//BL.InitGLSL();
	//BL.InitVBO();

	std::stringstream ss;
	//BL.addBall((point){(float)DEF_WIDTH / 2.0f, (float)DEF_HEIGHT / 2.0f});
	for(int i = 0; i < BALLS_NUM; i++) {
		BL.addBall((point){(float)DEF_WIDTH / 2.0f + cos((float)i / (float)BALLS_NUM * PI / 180.0f * 360.0f) * 200.0f, (float)DEF_HEIGHT / 2.0f - sin((float)i / (float)BALLS_NUM * PI / 180.0f * 360.0f) * 200.0f});
	}
	unsigned int Tlast, Tnow = SDL_GetTicks(), Tspent;
	float lastFPS, curFPS = 0.0f, showFPS = 0.0f;
    SDL_Event event;
    point MousePos;
    bool Btn[5] = {false, false, false, false, true};
    bool cont = true;
    while(cont) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) cont = false;
            else if(event.type == SDL_KEYDOWN) {
            	if(event.key.keysym.sym == SDLK_SPACE) {
            		for(unsigned int i = 0; i < BL.getListSize(); i++) {
						BL[i]->setPos((point){(float)DEF_WIDTH / 2.0f + cos((float)i / (float)BL.getListSize() * PI / 180.0f * 360.0f) * 200.0f, (float)DEF_HEIGHT / 2.0f + sin((float)i / (float)BL.getListSize() * PI / 180.0f * 360.0f) * 200.0f});
						BL[i]->setPhysV((point){0.0f, 0.0f});
					}
            	}
            	else if(event.key.keysym.sym == SDLK_EQUALS) {
            		Btn[2] = true;
            	}
            	else if(event.key.keysym.sym == SDLK_MINUS) {
            		Btn[3] = true;
            	}
            	else if(event.key.keysym.sym == SDLK_TAB) {
            		Btn[4] = !Btn[4];
            	}
            }
            else if(event.type == SDL_KEYUP) {
				if(event.key.keysym.sym == SDLK_EQUALS) {
            		Btn[2] = false;
            	}
            	else if(event.key.keysym.sym == SDLK_MINUS) {
            		Btn[3] = false;
            	}
            	else if(event.key.keysym.sym == SDLK_TAB) {
            		//Btn[4] = false;
            	}
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
            	if(event.button.button == SDL_BUTTON_LEFT) {
            		Btn[0] = true;
            	}
            	else if(event.button.button == SDL_BUTTON_RIGHT) {
            		Btn[1] = true;
            	}
            	else if(event.button.button == SDL_BUTTON_WHEELUP) {
            		BL.addRAll(-10.0f);
            	}
				else if(event.button.button == SDL_BUTTON_WHEELDOWN) {
            		BL.addRAll(10.0f);
            	}
            	else if(event.button.button == SDL_BUTTON_MIDDLE) {
					BL.setPhysV((point){0.0f, 0.0f});
            	}
            }
			else if(event.type == SDL_MOUSEBUTTONUP) {
            	if(event.button.button == SDL_BUTTON_LEFT) {
            		BL.setPhysN((point){0.0f, 0.0f});
            		Btn[0] = false;
            	}
            	else if(event.button.button == SDL_BUTTON_RIGHT) {
					BL.setPhysN((point){0.0f, 0.0f});
            		Btn[1] = false;
            	}
            }
            else if(event.type == SDL_MOUSEMOTION) {
            	MousePos.X = (float)event.motion.x;
            	MousePos.Y = (float)event.motion.y;
            }
        }
        Tlast = Tnow;
        Tnow = SDL_GetTicks();
        Tspent = Tnow - Tlast;
        if(Tspent <= 0) Tspent = 1;
		lastFPS = curFPS;
		curFPS = 1000.0f / (float)Tspent;
		if(abs(showFPS - curFPS) > 2.0f) {
        	showFPS = curFPS;
        }

		if(Btn[1]) BL.setPhysNAllTo(MousePos, -2000.0f);
		if(Btn[0]) BL.setPhysNAllTo(MousePos, 2000.0f);
		if(Btn[2]) BL.addBall(MousePos);
		if(Btn[3]) BL.deleteBall(MousePos);

		ss.str("");
		ss.precision(2);
		ss<<"Balls: "<<BL.getListSize();
		ss<<" | Wall: ";
		if(Btn[4]) ss<<"On";
		else ss<<"Off";
		ss<<" | FPS: "<<showFPS;

		SDL_WM_SetCaption(ss.str().c_str(), NULL);
		//BL.addPhysNAllToAll(0.1f, -200.0f);

        glClear(GL_COLOR_BUFFER_BIT);

    	BL.Refresh(Tlast, Tnow, Btn[4]);
    	BL.Draw(MousePos);
    	//BL.DrawVBO(MousePos);
    	//BL.DrawDL(MousePos);
    	//BL.Draw(MousePos);
    	//BL.DrawGLSL(MousePos);

		SDL_GL_SwapBuffers();
        //SDL_Delay(1);
    }
    SDL_Quit();
    return 0;
}
