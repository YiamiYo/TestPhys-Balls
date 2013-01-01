#ifndef Y_FUNCTIONS_H
#define Y_FUNCTIONS_H

#include "defines.h"
#include "structs.h"
#include <cmath>
#include <fstream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource; //ARB too
extern PFNGLCOMPILESHADERPROC glCompileShader; //ARB too
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram; //ARB too
extern PFNGLGETPROGRAMIVPROC glGetProgramiv; //ARB too
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLGENBUFFERSPROC glGenBuffers; //ARB too
extern PFNGLBINDBUFFERPROC glBindBuffer; //ARB too
extern PFNGLBUFFERDATAPROC glBufferData; //ARB too
extern PFNGLBUFFERSUBDATAPROC glBufferSubData; //ARB too
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray; //ARB too
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer; //ARB too
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray; //ARB too
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation; //ARB too
extern PFNGLACTIVETEXTUREPROC glActiveTexture; //ARB too
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv; //ARB too
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers; //ARB too
extern PFNGLDELETEPROGRAMPROC glDeleteProgram; //ARB too
//extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
//extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

int loadGLFunctions(void);
unsigned int LoadShaders(const char*,const char*);

float getDist(point, point);

float getAngle(point, point);

point getForce(point, point, float);

#endif
