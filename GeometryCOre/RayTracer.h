#pragma once
#include <string>
#include "FloatMatrix4.h"
#include "Scene.h"

class RayTracer
{
	Scene* _scene;

	unsigned char* _buffer;
	unsigned int _width;
	unsigned int _height;

	FloatMatrix4 _camera_to_world_matrix;
	FloatMatrix4 _world_to_camera_matrix;

	static Vector3f getReflectedDirection(const Vector3f& incident, const Vector3f& normal);

public:
	RayTracer(Scene* scene, unsigned int pixelWidth, unsigned int pixelHeight);
	
	void Render(int max_ray_depth);

	void RenderFlat();

	void RenderAndSave(int max_ray_depth, std::string file_path);

	void RenderAndSaveFlat(int max_ray_depth, std::string file_path);

	void initTransformMatrix();
	
	Vector3f getRasterToWorldSpaceCoordinates(unsigned x, unsigned y) const;

	GraphicObject* getNearest(Ray& ray, Vector3f& intersect, Vector3f& normal) const;
	
	RGBAColor cast(Ray& ray, int max_ray_depth, bool getColor = true) const;
	
	FloatMatrix4 getCameraToWorldMatrix() const;

	FloatMatrix4 getWorldToCameraMatrix() const;

	float getWidth() const;

	float getHeight() const;

	RGBAColor getIllumination(
		Ray& ray, 
		Vector3f intersect, 
		Vector3f normal, 
		Materials::Material material) const;

	RGBAColor getPhong(
		Ray& ray, 
		Vector3f intersect, 
		Vector3f normal, 
		Materials::Material material) const;

	bool isInShadow(Vector3f& intersect, Vector3f lighPos) const;
};