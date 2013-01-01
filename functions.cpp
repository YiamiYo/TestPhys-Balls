#include "functions.h"

int loadGLFunctions(void) {
	if(!(glCreateShader = (PFNGLCREATESHADERPROC) SDL_GL_GetProcAddress("glCreateShader"))) return 10;
	if(!(glShaderSource = (PFNGLSHADERSOURCEPROC) SDL_GL_GetProcAddress("glShaderSource"))) return 20;
	if(!(glCompileShader = (PFNGLCOMPILESHADERPROC) SDL_GL_GetProcAddress("glCompileShader"))) return 30;
	if(!(glGetShaderiv = (PFNGLGETSHADERIVPROC) SDL_GL_GetProcAddress("glGetShaderiv"))) return 40;
	if(!(glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) SDL_GL_GetProcAddress("glGetShaderInfoLog"))) return 50;
	if(!(glCreateProgram = (PFNGLCREATEPROGRAMPROC) SDL_GL_GetProcAddress("glCreateProgram"))) return 60;
	if(!(glAttachShader = (PFNGLATTACHSHADERPROC) SDL_GL_GetProcAddress("glAttachShader"))) return 70;
	if(!(glLinkProgram = (PFNGLLINKPROGRAMPROC) SDL_GL_GetProcAddress("glLinkProgram"))) return 80;
	if(!(glGetProgramiv = (PFNGLGETPROGRAMIVPROC) SDL_GL_GetProcAddress("glGetProgramiv"))) return 90;
	if(!(glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) SDL_GL_GetProcAddress("glGetProgramInfoLog"))) return 100;
	if(!(glDeleteShader = (PFNGLDELETESHADERPROC) SDL_GL_GetProcAddress("glDeleteShader"))) return 110;
	if(!(glGenBuffers = (PFNGLGENBUFFERSPROC) SDL_GL_GetProcAddress("glGenBuffers"))) return 120;
	if(!(glBindBuffer = (PFNGLBINDBUFFERPROC) SDL_GL_GetProcAddress("glBindBuffer"))) return 130;
	if(!(glBufferData = (PFNGLBUFFERDATAPROC) SDL_GL_GetProcAddress("glBufferData"))) return 140;
	if(!(glBufferSubData = (PFNGLBUFFERSUBDATAPROC) SDL_GL_GetProcAddress("glBufferSubData"))) return 141;
	if(!(glUseProgram = (PFNGLUSEPROGRAMPROC) SDL_GL_GetProcAddress("glUseProgram"))) return 150;
	if(!(glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) SDL_GL_GetProcAddress("glEnableVertexAttribArray"))) return 160;
	if(!(glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) SDL_GL_GetProcAddress("glVertexAttribPointer"))) return 170;
	if(!(glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) SDL_GL_GetProcAddress("glDisableVertexAttribArray"))) return 180;
	if(!(glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) SDL_GL_GetProcAddress("glGetUniformLocation"))) return 190;
	if(!(glActiveTexture = (PFNGLACTIVETEXTUREPROC) SDL_GL_GetProcAddress("glActiveTexture"))) return 200;
	if(!(glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) SDL_GL_GetProcAddress("glUniformMatrix4fv"))) return 210;
	if(!(glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) SDL_GL_GetProcAddress("glDeleteBuffers"))) return 220;
	if(!(glDeleteProgram = (PFNGLDELETEPROGRAMPROC) SDL_GL_GetProcAddress("glDeleteProgram"))) return 230;
	return 0;
}

unsigned int LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
	}
	//printf("</--Vertex Shader--\\>%s\n<\\--Vertex Shader--/>\n\n", VertexShaderCode.c_str());

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    ////printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    //printf("Code: \n %s \n", VertexSourcePointer);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char VertexShaderErrorMessage[InfoLogLength];
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
    ////printf("%s\n", VertexShaderErrorMessage);

    // Compile Fragment Shader
    ////printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char FragmentShaderErrorMessage[InfoLogLength];
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
    ////printf("%s\n", FragmentShaderErrorMessage);

    // Link the program
    ////printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char ProgramErrorMessage[std::max(InfoLogLength, int(1))];
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
    ////printf("%s\n", ProgramErrorMessage);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

float getDist(point p1, point p2) {
	point dif = (point){p1.X - p2.X, p1.Y - p2.Y};
	return (float)sqrt(dif.X * dif.X + dif.Y * dif.Y);
}

float getAngle(point p1, point p2) {
	float ret = 0.0f;

	point dif = {p1.X - p2.X, p1.Y - p2.Y};
	float hyp = sqrt(dif.X * dif.X + dif.Y * dif.Y);

	float angle_cos = dif.X / hyp;
	if(std::isnan(angle_cos)) angle_cos = 0.0f;
	else if(angle_cos < -1.0f) angle_cos = -1.0f;
	else if(angle_cos > 1.0f) angle_cos = 1.0f;
	if(dif.Y > 0.0f) {
		ret = (180.0f - acos(angle_cos) * 180.0f / PI);  //ret = [180.0f, 0.0f];
	}
	else {
		ret = (acos(angle_cos) * 180.0f / PI + 180.0f);	//ret = [180.0f, 360.0f];

	}
	return ret;
}

point getForce(point pFrom, point pTo, float force) {
	//point dif = {p1.X - p2.X, p1.Y - p2.Y};
	//if(dif.X < 0.0f) dif.X = -dif.X;
	//if(dif.Y < 0.0f) dif.Y = -dif.Y;
	//float hyp = sqrt(dif.X * dif.X + dif.Y * dif.Y);
	/*if(dif.Y < 0.0f) return (point){cos(dif.Y / hyp) * force * dif.X, -sin(dif.Y / hyp) * force * dif.Y};
	return (point){cos(dif.Y / hyp) * force * dif.X, sin(dif.Y / hyp) * force * dif.Y};*/
	/*if(dif.X < 0.0f) return (point){-cos(dif.Y / hyp) * force, sin(dif.Y / hyp) * force};
	return (point){cos(dif.Y / hyp) * force, sin(dif.Y / hyp) * force};*/
	float dist = getDist(pFrom, pTo);
	float t = (pow(dist, 2) + 100000) / 100000;
	t = 1;
	float angle = getAngle(pTo, pFrom);
	return (point){-cos(angle * PI / 180.0f) * force / t, sin(angle * PI / 180.0f) * force / t};
	/*point difabs = (point){abs(dif.X), abs(dif.Y)};
	if(difabs.X < 1.0f) difabs.X = 1.0f;
	if(difabs.Y < 1.0f) difabs.Y = 1.0f;
	if(dif.X < 0.0f) return (point){-cos(asin(dif.Y / hyp)) * force * difabs.X, dif.Y / hyp * force * difabs.Y};
	return (point){cos(asin(dif.Y / hyp)) * force * difabs.X, dif.Y / hyp * force * difabs.Y};*/
}
