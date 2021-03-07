#pragma once

#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>

enum class LogLevel { INFO = 0, WARNING = 1, FATAL = 2 };

struct Vector3f {

	float X;
	float Y;
	float Z;

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& v);

	Vector3f operator+(const Vector3f& v1) const;
	void operator+=(const Vector3f& v2);

	Vector3f operator-() const;
	Vector3f operator-(const Vector3f& v2) const;
	void operator-=(const Vector3f& v2);

	float operator*(const Vector3f& v2) const;
	Vector3f operator*(float scalar) const;
	void operator*=(float scalar);

	bool operator==(const Vector3f& v2) const;
	void operator=(const Vector3f& v2);

	Vector3f operator^(const Vector3f& v2) const;
};

class GraphicObject
{
public:
	virtual void RTRender() const = 0;
	virtual void GLRender() const = 0;
	//virtual Vector3f* GetVertexBuffer() const = 0;
	virtual void SetColor(const Vector3f& color) = 0;
	virtual void Move(const Vector3f& vect3) = 0;
	virtual void Scale(float factor) = 0;
};

class Logger
{
	static std::string _getFlag(LogLevel logLevel);
	Logger() = delete;
	~Logger() = delete;

public:
	static void Write(std::string message, LogLevel logLevel);
};

class Cube : public GraphicObject
{

public:
	Vector3f Pos;
	Vector3f Color;
	float Size;

	~Cube() {}
	Cube(const Vector3f& cubePosition, float cubeSize);

	void SetColor(const Vector3f& color) override;
	void Move(const Vector3f& vect3) override;
	void Scale(const float factor) override;

	void RTRender() const override;

	void GLRenderFaces(const Vector3f& faceColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const override;

private:
	Vector3f* _vertexBuffer[8];
	int _facesIndexBuffer[36];
	int _linesIndexBuffer[24];

	void LogInit() const;
	void SetVertexBuffers();
};

class Sphere : public GraphicObject
{
public:
	Vector3f Pos;
	Vector3f Color;
	float Radius;

	~Sphere() {}
	Sphere(const Vector3f& center, float radius);

	void SetColor(const Vector3f& color);
	void Move(const Vector3f& vect3);
	void Scale(float factor);

	void RTRender() const;

	void GLRenderFill(const Vector3f& fillColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const;

private:
	void GLAddToDisplayList() const;
};

class Scene
{
	int _nbGraphicObject = 0;

public:
	GraphicObject* graphic_object_array[10];

	//~Scene() = delete; // Scene will only be deleted on program exit (for now)
	void Add(GraphicObject* obj);
	void Init();
	void GLDraw();
};