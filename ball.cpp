#include <SDL/SDL_opengl.h>
#include <cmath>
#include "structs.h"
#include "ball.h"

#include "defines.h"
#include "functions.h"
//#include "functionsp.h"

void Ball::Init(point i_Pos, float i_R) {
	setPos(i_Pos);
	setR(i_R);
	setColor(0.2f, 0.2f, 0.2f, 1.0f);
	Phys.M = 1.0f;
	Phys.V = (point){0.0f, 0.0f};
	Phys.N = (point){0.0f, 0.0f};
	Phys.A = (point){0.0f, 0.0f};
}

void Ball::setColor(float i_R, float i_G, float i_B, float i_A = 1.0f) {
	Color[0] = i_R;
	Color[1] = i_G;
	Color[2] = i_B;
	Color[3] = i_A;
}

void Ball::setPos(point i_Pos) {
	Pos = i_Pos;
}

void Ball::setPhysM(float i_M) {
	Phys.M = i_M;
}

void Ball::setPhysV(point i_V) {
	Phys.V = i_V;
}

void Ball::setPhysN(point i_N) {
	Phys.N = i_N;
	if(Phys.M > 0.0f) Phys.A = (point){Phys.N.X / Phys.M, Phys.N.Y / Phys.M};
}

void Ball::addPhysN(point i_N) {
	Phys.N.X += i_N.X;
	Phys.N.Y += i_N.Y;
	if(Phys.M > 0.0f) Phys.A = (point){Phys.N.X / Phys.M, Phys.N.Y / Phys.M};
}

/*void Ball::Draw(float dLight) {
	glPushMatrix();

	glLoadIdentity();
	glTranslatef(Pos.X, Pos.Y, 0.0f);
	glRotatef(dLight, 0.0f, 0.0f, -1.0f);

	glBegin(GL_TRIANGLES);
		glColor4fv(Color);
		for(float i = 0.0f; i < 360.0f; i++) {
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(0.0f, 0.0f);
			glColor3f(0.0f, 0.0f, (cos((i) * PI / 180.0f) + 1.0f) / 2.0f);
			glVertex2f(cos(i * PI / 180.0f) * R, -sin(i * PI / 180.0f) * R);
			glVertex2f(cos((i+1.0f) * PI / 180.0f) * R, -sin((i+1.0f) * PI / 180.0f) * R);
		}
	glEnd();

	glPopMatrix();
}*/

void Ball::Refresh(unsigned int Tstart, unsigned int Tend, bool Wcol) {
	Pos.X += Phys.V.X * (float)(Tend - Tstart) / 1000.0f + 0.5f * Phys.A.X * (float)(Tend - Tstart) / 1000.0f * (float)(Tend - Tstart) / 1000.0f;
	Pos.Y += Phys.V.Y * (float)(Tend - Tstart) / 1000.0f + 0.5f * Phys.A.Y * (float)(Tend - Tstart) / 1000.0f * (float)(Tend - Tstart) / 1000.0f;

	if(Wcol) checkCol();

	Phys.V.X += Phys.A.X * (float)(Tend - Tstart) / 1000.0f;
	Phys.V.Y += Phys.A.Y * (float)(Tend - Tstart) / 1000.0f;

	/*if(Phys.V.X > 0.0f) Phys.V.X -= 1.0f;
	else if(Phys.V.X < 0.0f) Phys.V.X += 1.0f;
	if(Phys.V.Y > 0.0f) Phys.V.Y -= 1.0f;
	else if(Phys.V.Y < 0.0f) Phys.V.Y += 1.0f;*/
}

void Ball::checkCol(void) {
	bool colY = true, colX = true;

	if(Pos.Y + R >= (float)DEF_HEIGHT) Pos.Y = (float)DEF_HEIGHT - R - (Pos.Y + R - (float)DEF_HEIGHT);
	else if(Pos.Y - R <= 0) Pos.Y = R - (Pos.Y - R);
	else colY = false;

	if(Pos.X + R >= (float)DEF_WIDTH) Pos.X = (float)DEF_WIDTH - R - (Pos.X + R - (float)DEF_WIDTH);
	else if(Pos.X - R <= 0) Pos.X = R - (Pos.X - R);
	else colX = false;

	int colV = 500.0f;
	if(colY) {
		Phys.V.Y = -Phys.V.Y;
		if(Phys.V.Y > colV) Phys.V.Y -= colV;
		else if(Phys.V.Y < -colV) Phys.V.Y += colV;
		else Phys.V.Y = 0.0f;
	}
	if(colX) {
		Phys.V.X = -Phys.V.X;
		if(Phys.V.X > colV) Phys.V.X -= colV;
		else if(Phys.V.X < -colV) Phys.V.X += colV;
		else Phys.V.X = 0.0f;
	}
}

point Ball::getPos(void) {
	return Pos;
}

phys Ball::getPhys(void) {
	return Phys;
}

float Ball::getR(void) {
	return R;
}

void Ball::setR(float i_R) {
	R = i_R;
	if(R < 1.0f) R = 1.0f;
}

//BALLLIST
BallList::BallList(void) {
	mode = 0x00;
}
void BallList::InitDL(void) {
	mode |= 0x01;
	DLindex = glGenLists(1);
	float R = 1.0f;
	glNewList(DLindex, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			for(float i = 0.0f; i < 360.0f; i++) {
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex2f(0.0f, 0.0f);
				glColor3f(0.0f, 0.0f, (cos((i) * PI / 180.0f) + 1.0f) / 2.0f);
				glVertex2f(cos(i * PI / 180.0f) * R, -sin(i * PI / 180.0f) * R);
				glVertex2f(cos((i+1.0f) * PI / 180.0f) * R, -sin((i+1.0f) * PI / 180.0f) * R);
			}
		glEnd();
	glEndList();
}

void BallList::InitGLSL(void) {
	sProg = LoadShaders("main.yvs", "main.yfs");
	yvsMat4 = glGetUniformLocation(sProg, "iMat4");
	mode |= 0x04;
	float R = 1.0f;
	glGenBuffers(1, &VBOid);

	float VBOcolor[3240], VBOvertex[2160];
	for(int i = 0; i < 360; i++) {
		int temp_nv = i * 6, temp_nc = i * 9;
		VBOcolor[temp_nc] = 0.0f;
		VBOcolor[temp_nc + 1] = 0.0f;
		VBOcolor[temp_nc + 2] = 1.0f;
		VBOcolor[temp_nc + 3] = 0.0f;
		VBOcolor[temp_nc + 4] = 0.0f;
		VBOcolor[temp_nc + 5] = (cos((float)(i) * PI / 180.0f) + 1.0f) / 2.0f;
		VBOcolor[temp_nc + 6] = 0.0f;
		VBOcolor[temp_nc + 7] = 0.0f;
		VBOcolor[temp_nc + 8] = (cos((float)(i) * PI / 180.0f) + 1.0f) / 2.0f;

		VBOvertex[temp_nv] = 0.0f;
		VBOvertex[temp_nv + 1] = 0.0f;
		VBOvertex[temp_nv + 2] = cos(i * PI / 180.0f) * R;
		VBOvertex[temp_nv + 3] = -sin(i * PI / 180.0f) * R;
		VBOvertex[temp_nv + 4] = cos((i+1.0f) * PI / 180.0f) * R;
		VBOvertex[temp_nv + 5] = -sin((i+1.0f) * PI / 180.0f) * R;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VBOcolor) + sizeof(VBOvertex), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VBOcolor), (void*)VBOcolor);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(VBOcolor), sizeof(VBOvertex), (void*)VBOvertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	VBOcolor_size = sizeof(VBOcolor);
	VBOvertex_size = sizeof(VBOvertex);
}

void BallList::InitVBO(void) {
	mode |= 0x02;
	float R = 1.0f;
	glGenBuffers(1, &VBOid);

	float VBOcolor[3240], VBOvertex[2160];
	for(int i = 0; i < 360; i++) {
		int temp_nv = i * 6, temp_nc = i * 9;
		VBOcolor[temp_nc] = 0.0f;
		VBOcolor[temp_nc + 1] = 0.0f;
		VBOcolor[temp_nc + 2] = 1.0f;
		VBOcolor[temp_nc + 3] = 0.0f;
		VBOcolor[temp_nc + 4] = 0.0f;
		VBOcolor[temp_nc + 5] = (cos((float)(i) * PI / 180.0f) + 1.0f) / 2.0f;
		VBOcolor[temp_nc + 6] = 0.0f;
		VBOcolor[temp_nc + 7] = 0.0f;
		VBOcolor[temp_nc + 8] = (cos((float)(i) * PI / 180.0f) + 1.0f) / 2.0f;

		VBOvertex[temp_nv] = 0.0f;
		VBOvertex[temp_nv + 1] = 0.0f;
		VBOvertex[temp_nv + 2] = cos(i * PI / 180.0f) * R;
		VBOvertex[temp_nv + 3] = -sin(i * PI / 180.0f) * R;
		VBOvertex[temp_nv + 4] = cos((i+1.0f) * PI / 180.0f) * R;
		VBOvertex[temp_nv + 5] = -sin((i+1.0f) * PI / 180.0f) * R;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VBOcolor) + sizeof(VBOvertex), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VBOcolor), (void*)VBOcolor);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(VBOcolor), sizeof(VBOvertex), (void*)VBOvertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	VBOcolor_size = sizeof(VBOcolor);
	VBOvertex_size = sizeof(VBOvertex);
}

BallList::~BallList(void) {
	if(mode & 0x01) glDeleteLists(DLindex, 1);
	if(mode & 0x02) glDeleteBuffers(1, &VBOid);
}

void BallList::Draw(point LPos) {
	if(mode & 0x01) DrawDL(LPos);
	else if(mode & 0x02) DrawVBO(LPos);
	else if(mode & 0x04) DrawGLSL(LPos);
}

void BallList::DrawDL(point LPos) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(Balls[i].getPos().X, Balls[i].getPos().Y, 0.0f);
		glRotatef(getAngle(Balls[i].getPos(), LPos), 0.0f, 0.0f, -1.0f);
		glScalef(Balls[i].getR(), Balls[i].getR(), 1.0f);
		glCallList(DLindex);
		glPopMatrix();
	}
}

void BallList::DrawGLSL(point LPos) {
	glUseProgram(sProg);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(VBOcolor_size));

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	float mat4[16];

	unsigned int t_num = VBOcolor_size / 3;
	for(unsigned int i = 0; i < Balls.size(); i++) {
		float cos_a = cos(getAngle(Balls[i].getPos(), LPos) * PI / 180.0f), sin_a = -sin(getAngle(Balls[i].getPos(), LPos) * PI / 180.0f);
		mat4[0] = Balls[i].getR() * cos_a;
		mat4[1] = Balls[i].getR() * sin_a;
		mat4[2] = 0.0f;
		mat4[3] = 0.0f;

		mat4[4] = -mat4[1];
		mat4[5] = mat4[0];
		mat4[6] = 0.0f;
		mat4[7] = 0.0f;

		mat4[8] = 0.0f;
		mat4[9] = 0.0f;
		mat4[10] = 1.0f;
		mat4[11] = 0.0f;

		mat4[12] = Balls[i].getPos().X;
		mat4[13] = Balls[i].getPos().Y;
		mat4[14] = 0.0f;
		mat4[15] = 1.0f;
		glUniformMatrix4fv(yvsMat4, 1, false, mat4);
		glDrawArrays(GL_TRIANGLES, 0, t_num);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void BallList::DrawVBO(point LPos) {
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, 0);
	glVertexPointer(2, GL_FLOAT, 0, (void*)(VBOcolor_size));

	unsigned int t_num = VBOcolor_size / 3;
	for(unsigned int i = 0; i < Balls.size(); i++) {
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(Balls[i].getPos().X, Balls[i].getPos().Y, 0.0f);
		glRotatef(getAngle(Balls[i].getPos(), LPos), 0.0f, 0.0f, -1.0f);
		glScalef(Balls[i].getR(), Balls[i].getR(), 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, t_num);

		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BallList::addBall(point i_Pos) {
	Ball temp_Ball;
	temp_Ball.Init(i_Pos, genR);
	Balls.push_back(temp_Ball);
}

Ball* BallList::getLastBall(void) {
	return &(Balls.back());
}

/*void BallList::Draw(point LPos) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].Draw(getAngle(Balls[i].getPos(), LPos));
	}
}*/

void BallList::Refresh(unsigned int Tstart, unsigned int Tend, bool Wcol) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].Refresh(Tstart, Tend, Wcol);
	}
}

void BallList::setPhysN(point i_N) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].setPhysN(i_N);
	}
}

void BallList::setPhysNAllTo(point FC, float i_N) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].setPhysN(getForce(Balls[i].getPos(), FC, i_N));
	}
}

void BallList::setPhysV(point i_V) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].setPhysV(i_V);
	}
}

void BallList::addPhysN(point i_N) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].addPhysN(i_N);
	}
}

void BallList::addPhysNAllToAll(float mult, float offset) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		for(unsigned int r = 0; r < Balls.size(); r++) {
			Balls[i].addPhysN(getForce(Balls[i].getPos(), Balls[r].getPos(), mult * (getDist(Balls[i].getPos(), Balls[r].getPos()) + offset)));
		}
	}
}

Ball* BallList::operator[](int i) {
	return &(Balls[i]);
}

void BallList::setRAll(float i_R) {
	genR = i_R;
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].setR(i_R);
	}
}

void BallList::addRAll(float i_R) {
	genR *= (1.0f + i_R / 100.0f);
	if(genR < 1.0f) genR = 1.0f;
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].setR(genR);
	}
}

void BallList::setPosAll(point i_Pos) {
	for(unsigned int i = 0; i < Balls.size(); i++) {
		Balls[i].setPos(i_Pos);
	}
}

unsigned int BallList::getListSize(void) {
	return Balls.size();
}

float BallList::getRAll(void) {
	return genR;
}

void BallList::deleteBall(point i_Pos) {
	std::vector<Ball>::reverse_iterator rit;
	for(rit = Balls.rbegin(); rit < Balls.rend(); rit++) {
		if(getDist(rit->getPos(), i_Pos) < rit->getR()) {
			Balls.erase(--rit.base());
			//return;
		}
	}
}
