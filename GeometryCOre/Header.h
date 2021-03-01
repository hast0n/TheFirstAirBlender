#pragma once

class graphic_object
{
public:
	virtual void RTRender();
	virtual void GLRender();
};

class cube : public graphic_object
{
private:
	unsigned int X;
	unsigned int Y;
	unsigned int Side;
public:
	cube(unsigned int posX, unsigned int posY, unsigned int side);
	void RTRender() override;
	void GLRender() override;
};
