#pragma once

struct RGBAColor
{
	float r;
	float g;
	float b;
	float a;

	RGBAColor() :r(0), g(0), b(0), a(1) {};
	RGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {};
	RGBAColor(float r, float g, float b) :r(r), g(g), b(b), a(1) {};
	
	RGBAColor operator+(float f) const
	{
		return RGBAColor{r + f, g + f, b + f, a};
	}

	RGBAColor operator*(float f) const
	{
		return RGBAColor{r * f, g * f, b * f, a};
	}

	RGBAColor operator+(const RGBAColor& c1) const
	{
		return RGBAColor{
			c1.r + r,
			c1.g + g,
			c1.b + b,
			c1.a + a
		};
	}

	RGBAColor operator*(const RGBAColor& c1) const
	{
		return RGBAColor{
			c1.r * r,
			c1.g * g,
			c1.b * b,
			c1.a * a
		};
	}

	RGBAColor capped()
	{
		return RGBAColor{
			cap(r),
			cap(g),
			cap(b),
			cap(a)
		};
	}

	RGBAColor& operator+=(const RGBAColor& c)
	{
		r = c.r + r;
		g = c.g + g;
		b = c.b + b;
		a = c.a + a;

		return *this;
	}

private:
	static float cap(float value)
	{
		return value > 1 ? 1 : value < 0 ? 0 : value;
	}
};

namespace Materials
{
	
	struct Material
	{
		RGBAColor finish; //color

		float diffuse;
		float specular;
		float emission;

		float reflectance;
		float shininess; // 0.0f .. 128.0f

		bool is_transparent;
		bool is_metallic;
	};

	const Material MirrorLike = {
		RGBAColor(1, .5, 0),

		1,
		1,
		0,
		1,
		250,
		false,
		true
	};

	const Material Plastic = {
	RGBAColor(1, 0, 1),

	0.8,
	0.04,
	0,
	0,
	2,
	false,
	false
	};

	const Material Default = {
		RGBAColor(1, 1, 1),

		1,
		0.5,
		0.0,
		0.2,
		100,
		false,
		false
	};

	//struct Material
	//{
	//	RGBAColor finish; //color

	//	RGBAColor ambient;
	//	RGBAColor diffuse;
	//	RGBAColor specular;
	//	RGBAColor emission;
	//	
	//	RGBAColor shininess; // 0.0f .. 128.0f

	//	bool is_transparent;
	//};
	
	//const Material MirrorLike = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.2, 0.2, 0.2, 1.0},
	//	RGBAColor{0.8, 0.8, 0.8, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 1.0},
	//	77.0,
	//	false
	//};

	//const Material Glass = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.0, 0.0, 0.0, 1.0},
	//	RGBAColor{0.588235, 0.670588, 0.729412, 1.0},
	//	RGBAColor{0.9, 0.9, 0.9, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 1.0},
	//	96.0,
	//	true
	//};
	//
	//const Material Bronze = {
	//	RGBAColor(1, 1, 1),
 //       RGBAColor{0.25, 0.25, 0.25, 1.0},
 //       RGBAColor{0.4, 0.4, 0.4, 1.0},
 //       RGBAColor{0.774597, 0.774597, 0.774597, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 0.0},
	//	25.6,
	//	false
	//};

	//const Material Brass = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.329412, 0.223529, 0.027451, 1.0},
	//	RGBAColor{0.780392, 0.568627, 0.113725, 1.0},
	//	RGBAColor{0.992157, 0.941176, 0.807843, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 0.0},
	//	27.8974,
	//	false
	//};

	//const Material Chrome = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.25, 0.25, 0.25, 1.0},
	//	RGBAColor{0.4, 0.4, 0.4, 1.0},
	//	RGBAColor{0.774597, 0.774597, 0.774597, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 0.0},
	//	76.8,
	//	false
	//};

	//const Material Gold = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.24725, 0.1995, 0.0745, 1.0},
	//	RGBAColor{0.75164, 0.60648, 0.22648, 1.0},
	//	RGBAColor{0.628281, 0.555802, 0.366065, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 0.0},
	//	51.2,
	//	false
	//};

	//const Material Black_Plastic = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.0, 0.0, 0.0, 1.0},
	//	RGBAColor{0.01f, 0.01f, 0.01f, 1.0},
	//	RGBAColor{0.50, 0.50, 0.50, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 0.0},
	//	32,
	//	false
	//};

	//const Material Black_Rubber = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.02, 0.02, 0.02, 1.0},
	//	RGBAColor{0.01, 0.01, 0.01, 1.0},
	//	RGBAColor{0.4, 0.4, 0.4, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 0.0},
	//	10,
	//	false
	//};

	//const Material Default = {
	//	RGBAColor(1, 1, 1),
	//	RGBAColor{0.2, 0.2, 0.2, 1.0},
	//	RGBAColor{0.8, 0.8, 0.8, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 1.0},
	//	RGBAColor{0.0, 0.0, 0.0, 1.0},
	//	25.6,
	//	false
	//};
	
}