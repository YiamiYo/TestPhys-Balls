#ifndef Y_BALL_H
#define Y_BALL_H

#include <vector>

class Ball {
	private:
		point Pos;
		float R;
		float Color[4];
		phys Phys;
	public:
		void Init(point, float);
		void setColor(float, float, float, float);
		void setPhysM(float);
		void setPhysV(point);
		void setPhysN(point);
		void addPhysN(point);
		//void Draw(float);
		void Refresh(unsigned int, unsigned int, bool);
		void checkCol(void);
		point getPos(void);
		void setPos(point);
		phys getPhys(void);
		float getR(void);
		void setR(float);
};

class BallList {
	private:
		std::vector<Ball> Balls;
		unsigned int sProg;
		unsigned int DLindex;
		unsigned int VBOid, yvsMat4;
		char mode;
		long int VBOcolor_size, VBOvertex_size;
		float genR;
	public:
		Ball* operator[](int);
		BallList(void);
		void InitDL(void);
		void InitVBO(void);
		void InitGLSL(void);
		~BallList(void);
		void addBall(point);
		void deleteBall(point);
		Ball* getLastBall(void);
		void Draw(point);
		void DrawDL(point);
		void DrawVBO(point);
		void DrawGLSL(point);
		void Refresh(unsigned int, unsigned int, bool);
		void setPosAll(point);
		void setRAll(float);
		float getRAll(void);
		void addRAll(float);
		void setPhysN(point);
		void setPhysNAllTo(point, float);
		void setPhysV(point);
		void addPhysN(point);
		void addPhysNAllToAll(float, float);
		unsigned int getListSize(void);
};

#endif
