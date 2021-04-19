#include "RayTracer.h"
#include <iostream>
#include <string>

#include "Windows.h"
#include "gl/GLU.h"

#include "Cube.h"
#include "PNGExporter.h"
#include "Ray.h"
#include "Sphere.h"

# define M_PI 3.14159265358979323846  /* pi */
# define EPSILON 0.0001  /* min value for ray intersection distance else ignore */

RayTracer::RayTracer(Scene* scene, unsigned pixelWidth, unsigned pixelHeight)
{
	_scene = scene;
	_width = pixelWidth;
	_height = pixelHeight;

	_buffer = new unsigned char[pixelHeight * pixelWidth * 4];
}

void RayTracer::Render(int max_ray_depth)
{
	this->initTransformMatrix();
	const auto cameraPos = _camera_to_world_matrix.leftMult(Vector3f(0, 0, 0));

	GraphicObject* unused = new Sphere();
	
	for (unsigned y = 0; y < _height; y++)
	{
		for (unsigned x = 0; x < _width; x++)
		{
			Vector3f pixel_pos = getRasterToWorldSpaceCoordinates(x, y);
			Vector3f dir = (pixel_pos - cameraPos).normalize();

			auto ray = Ray(cameraPos, dir);
		
			const RGBAColor color = cast(ray, &unused, max_ray_depth);
			
			_buffer[4 * _width * y + 4 * x + 0] = static_cast<unsigned char>(color.r * 255);
		    _buffer[4 * _width * y + 4 * x + 1] = static_cast<unsigned char>(color.g * 255);
		    _buffer[4 * _width * y + 4 * x + 2] = static_cast<unsigned char>(color.b * 255);
		    _buffer[4 * _width * y + 4 * x + 3] = static_cast<unsigned char>(color.a * 255);
		}
	}
}

void RayTracer::initTransformMatrix()
{
	_world_to_camera_matrix = _scene->Camera->getState();		
	_camera_to_world_matrix = _world_to_camera_matrix.getInverse();
}

Vector3f RayTracer::getRasterToWorldSpaceCoordinates(unsigned x, unsigned y) const
{
	const float zNear = _scene->Camera->getZNear();
	const float fov = _scene->Camera->getFOV(); // horizontal fov
	const float ar = _scene->Camera->getAspectRatio();

	const float raster_space_width = 2 * zNear * static_cast<float>(std::tan(fov / 2.f * M_PI / 180));
	const float raster_space_height = raster_space_width / ar;

	const float x_unit = raster_space_width / this->_width;
	const float y_unit = raster_space_height / this->_height;

	const float newX = - (raster_space_width / 2) + x_unit * x + x_unit / 2;
	const float newY = raster_space_height / 2 - y_unit * y - y_unit / 2;

	return _camera_to_world_matrix.leftMult(Vector3f(newX, newY, - zNear));
}

// incident is toward intersect
Vector3f RayTracer::getReflectedDirection(const Vector3f& incident, const Vector3f& normal)
{
	return (incident - 2 * (normal * incident) * normal).normalize();
}

RGBAColor RayTracer::cast(Ray& ray, GraphicObject** nearest, int max_ray_depth, bool getColor) const
{
	// return no illumination if max recursion reached
	if (max_ray_depth < 0) return RGBAColor{0, 0, 0, 1};
	
	float distMin = INFINITY;
	bool found = false;

	RGBAColor color = _scene->BackgroundColor * _scene->AmbientLighting;
	Vector3f normal;
	Vector3f intersect;
	
	for (int i = 0; i < _scene->nbGraphicObject; ++i)
	{
		GraphicObject* obj = _scene->getGraphicObject(i);
		Vector3f p;
		Vector3f n;
		
		if (obj->Intersects(ray, p, n))
		{
			const float dist = (p - ray.Origin).length();

			if (dist < distMin && dist > EPSILON)
			{
				*nearest = obj;
				intersect = p;
				normal = n;
				distMin = dist;
				found = true;
			}
		}
	}

	if (found && getColor)
	{
		auto material = (*nearest)->getMaterial();
		RGBAColor c0 = this->getIllumination(ray, intersect, normal, material);
		
		auto rdir = getReflectedDirection(ray.Direction, normal);
		Ray rray = Ray(intersect, rdir);
		const RGBAColor c1 = cast(rray, nearest, --max_ray_depth);

		color = (c0 + c1 * material.reflectance) * (material.is_metallic ? material.finish : RGBAColor(1, 1, 1));
		color = (color).capped();
	}

	return color;
}

FloatMatrix4 RayTracer::getCameraToWorldMatrix() const
{
	return _camera_to_world_matrix;
}

FloatMatrix4 RayTracer::getWorldToCameraMatrix() const
{
	return _world_to_camera_matrix;
}

float RayTracer::getWidth() const
{
	return _width;
}

float RayTracer::getHeight() const
{
	return _height;
}

RGBAColor RayTracer::getIllumination(Ray& ray, Vector3f intersect, Vector3f normal,
	Materials::Material material) const
{
	return getPhong(ray, intersect, normal, material);
}

RGBAColor RayTracer::getPhong(Ray& ray, Vector3f intersect, Vector3f normal,
	Materials::Material material) const
{
	const RGBAColor ambientColor = _scene->AmbientLighting * material.finish;
	RGBAColor diffuseColor = RGBAColor();
	RGBAColor specularColor = RGBAColor();

	for (int i = 0; i < _scene->nbLights; ++i)
	{
		Light* light = _scene->getLight(i);

		if (isInShadow(intersect, light->getPosition())) continue;
		
		Vector3f L = (light->getPosition() - intersect).normalize(); //intercept to light vector
		Vector3f R = getReflectedDirection(-L, normal);
		Vector3f V = (ray.Origin - intersect).normalize();
		
		float diffuse = (L * normal) * material.diffuse; // * ;
		diffuseColor += (material.finish * diffuse).capped();

		auto t = R * V;
		if (t > 0)
		{
			float specular = std::pow(t, material.shininess) * material.specular;

			specularColor += material.is_metallic ? light->getColor() * material.finish * specular : light->getColor() * specular;
		}
		
	}

	return (ambientColor + diffuseColor + specularColor).capped();
}

bool RayTracer::isInShadow(Vector3f& intersect, Vector3f lightPos) const
{
	GraphicObject* base = new Sphere();
	GraphicObject* block = base;
	const Vector3f dir = (lightPos - intersect).normalize();
	auto ray = Ray(intersect, dir);

	cast(ray, &block, 0, false);

	return block != base;
}

void RayTracer::RenderAndSave(int max_ray_depth, std::string file_path)
{
	this->Render(max_ray_depth);
	
	PNGExporter exporter = PNGExporter(_buffer, _width, _height);
	exporter.Export(file_path);
}
