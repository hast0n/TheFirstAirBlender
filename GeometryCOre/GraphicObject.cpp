class Vector3f;

class GraphicObject
{

public:
	virtual ~GraphicObject() = default;
	
	virtual void RTRender() const = 0;
	
	virtual void GLRender() const = 0;
	
	//virtual Vector3f* GetVertexBuffer() const = 0;
	
	virtual void SetColor(const Vector3f& color) = 0;
	
	virtual void Move(const Vector3f& vect3) = 0;
	
	virtual void Scale(float factor) = 0;
};