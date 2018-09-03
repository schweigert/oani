/* generated by dia/codegen.py */
class LinearInterpolator : Interpolator 
{
public:
	LinearInterpolator ();
	LinearInterpolator (const LinearInterpolator& );
	LinearInterpolator (LinearInterpolator* );
	void OnLoop (double );
};

class Vector3 
{
public:
	Vector3 (float ,
	         float ,
	         float ,
	         float );
	Vector3 (const Vector3& );
	float Length ();
	void Normalize ();
	void Resize (float );
	float DotProduct (Vector3 );
	Vector3 CrossProduct (Vector3 );
	Vector3 operator + (Vector3 );
	Vector3 operator - (Vector3 );
	Vector3 operator * (Vector3 );
	Vector3 operator * (float );
	Vector3 operator = (Vector3 );
	float x;
	float y;
	float z;
	float w;
};

class Fence : Object 
{
public:
	Fence ();
	Fence (const Fence& );
	Fence (Fence* );
	virtual void Initialize ();
};

class House : Object 
{
public:
	House ();
	House (const House& );
	House (House* );
	virtual void Initialize ();
};

class Object : Entity 
{
public:
	Object ();
	Object (const Object& );
	Object (Object* );
	~Object ();
protected:
	vector<Entity*> listOfEntities;
/* implementation: */
	virtual void Initialize ();
	virtual void OnRender ();
	virtual void OnLoop (double );
};

class Tree : Object 
{
public:
	Tree ();
	Tree (const Tree& );
	Tree (Tree* );
};

class Robot : Actor 
{
public:
	Robot ();
	Robot (const Robot& );
	Robot (Robot* );
};

class Actor : Object 
{
public:
	Actor ();
	Actor (const Actor & );
	Actor (Actor* );
	~Actor ();
	void SetAnimator (Animator * );
	Animator* GetAnimator ();
	void OnLoop (double );
private:
	Animator* ptrAnimator;
};

class Entity 
{
public:
	Entity ();
	Entity (const Entity& );
	Entity (Entity* );
	void setTranslate (Vector3 );
	void setRotate (Vector3 );
	void setScale (Vector3 );
	Vector3 getTranslate ();
	Vector3 getRotate ();
	Vector3 getScale ();
protected:
	Vector3 vTranslate;
	Vector3 vRotate;
	Vector3 vScale;
/* implementation: */
	virtual void OnRender ();
	virtual void OnLoop ();
};

class Application 
{
public:
	Application (string );
	~Application ();
	void setWindowSize (unsigned int ,
	                    unsigned int );
	unsigned int getWidth ();
	unsigned int getHeight ();
	string getTitle ();
	int Execute (double );
	void RenderFrame ();
	void addEntity (Entity* );
	bool setEntity (Entity* ,
	                unsigned int );
	Entity* getEntity (unsigned int );
	Camera* getCamera ();
private:
	void CalculateFPS (double );
	string strAppName;
	string strCurrentFPS;
	unsigned int uiWindowWidth;
	unsigned int uiWindowHeight;
	unsigned int uiFrames;
	double dCounterTimer;
	vector<Entity*> listOfEntities;
};

class Camera : Entity 
{
public:
	Camera (Camera::CameraType );
	Camera (const Camera& );
	Camera (Camera* );
	void setViewport (unsigned int ,
	                  unsigned int );
	void setClippingPlanes (float ,
	                        float );
	float getNearPlane ();
	float getFarPlane ();
	void setFOV (float );
	void Yaw (float );
	void Pitch (float );
	void Roll (float );
	void TurnAround_H (float );
	void TurnAround_V (float );
	void LookAt (Vector3 );
	Vector3 getFocalPoint ();
	void setUp (Vector3 );
	Vector3 getOrientation ();
	void OnRender ();
	void OnLoop (double );
private:
	Camera::CameraType cameraType;
	unsigned int uiWidth;
	unsigned int uiHeight;
	float fNearPlane;
	float fFarPlane;
	float fFOV;
	Vector3 vFocalPoint;
	Vector3 vUpVector;
};

class PrimitiveGL : Entity 
{
public:
	PrimitiveGL (PrimitiveGL::PrimitiveType );
	PrimitiveGL (const PrimitiveGL& );
	PrimitiveGL (PrimitiveGL* );
	void setColor (Vector3 );
	Vector3 getColor ();
	void OnRender ();
	void OnLoop (double );
	void setSize (GLdouble );
	void setHeight (GLdouble );
	void setResolution (GLint ,
	                    GLint );
protected:
	Vector3 vColor;
	PrimitiveGL::PrimitiveType oType;
	dSize GLdouble;
	GLdouble dHeight;
	GLint iSlices;
	GLint iStacks;
};

class PoseAttr 
{
public:
	PoseAttr (Vector3 ,
	          double ,
	          PoseAttr::AttrName );
	void setTime (double );
	double getTime ();
	PoseAttr::AttrName getName ();
	void setValue (Vector3 );
	Vector3 getValue ();
	void updateParent (Entity* );
protected:
	PoseAttr::AttrName attrName;
	double dAttrTime;
	Vector3 Value;
};

class Interpolator 
{
public:
	Interpolator ();
	Interpolator (const Interpolator& );
	Interpolator (Interpolator* );
	void setParent (Entity* );
	void addAttribute (PoseAttr );
protected:
	void updateParent (Entity* );
	Entity* ptrOwner;
	vector<PoseAttr> listOfPoseAttr;
/* implementation: */
	virtual void OnLoop ();
};

class Animator 
{
public:
	Animator (Animator::AnimationType );
	Animator (const Animator & );
	Animator (Animator* );
	 Animator~ ();
	void setParent (Entity* );
	void OnLoop (double );
	 addInterpolator (Interpolator* );
protected:
	Entity* ptrOwner;
	AnimationType animationType;
	double dAnimationTime;
	vector<Interpolator*> listOfInterpolators;
};

