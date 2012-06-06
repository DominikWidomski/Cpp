#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "GameObjectType.h"
#include "GameUtil.h"
#include "GameWorld.h"
#include "Shape.h"
#include "Sprite.h"

class BoundingShape;

class GameObject : public IRefCountImpl<GameObject>
{
public:
	GameObject(char const * const type_name);
	GameObject(char const * const type_name, GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	GameObject(const GameObject& o);
	virtual ~GameObject(void);

	void Reset();

	virtual void Update(int t);
	virtual void PreRender(void);
	virtual void Render(void);
	virtual void PostRender(void);

    virtual bool SelectionTest(GLVector3f w) { return false; }
	virtual bool CollisionTest(SmartPtr<GameObject> o) { return false; }
	virtual void OnCollision(const GameObjectList& objects) {}

	const GameObjectType& GetType() const { return mType; }

	void SetWorld(GameWorld *w) { mWorld = w; }
	GameWorld* GetWorld() { return mWorld; }

	void SetAngle(GLfloat a) { mAngle = a; }
	void SetRotation(GLfloat r) { mRotation = r; }
	void SetPosition(GLVector3f p) { mPosition = p; }
	void SetVelocity(GLVector3f v) { mVelocity = v; }
	void SetAcceleration(GLVector3f a) { mAcceleration = a; }
	void MakeSelected() { mSelected = true; }
	void MakeUnselected() { mSelected = false; }

	bool IsSelected() { return mSelected; }

	void SetSelectedShape(SmartPtr<Shape> s) { mSelectedShape = s; }

	void AddAngle(GLfloat a) { mAngle += a; if (mAngle < 0) mAngle += 360; if (mAngle > 360) mAngle -= 360; }
	void AddRotation(GLfloat r) { mRotation += r; }
	void AddPosition(GLVector3f p) { mPosition += p; }
	void AddVelocity(GLVector3f v) { mVelocity += v; }
	void AddAcceleration(GLVector3f a) { mAcceleration += a; }

	GLfloat GetAngle() { return mAngle; }
	GLfloat GetRotation() { return mRotation; }
	GLVector3f GetPosition() { return mPosition; }
	GLVector3f GetVelocity() { return mVelocity; }
	GLVector3f GetAcceleration() { return mAcceleration; }

	//int GetDamage() { return mDamage; }
	SmartPtr<Shape> GetSelectedShape() { return mSelectedShape; }

	void SetScale(float s) { mScale = s; }
	float GetScale() { return mScale; }

	void SetShape(SmartPtr<Shape> shape) { mShape = shape; }
	void SetSprite(SmartPtr<Sprite> sprite) { mSprite = sprite; }
	const SmartPtr<BoundingShape> GetBoundingShape() const { return mBoundingShape; }

protected:
	GameObjectType mType;

	GameWorld* mWorld;
	GLVector3f mPosition;
	GLVector3f mVelocity;
	GLVector3f mAcceleration;
	GLfloat mAngle;
	GLfloat mRotation;
	GLfloat mScale;

	bool mSelected;
	//int mDamage;

	SmartPtr<Shape> mShape;
	SmartPtr<Shape> mSelectedShape;
	SmartPtr<Sprite> mSprite;
	SmartPtr<BoundingShape> mBoundingShape;

	static bool mRenderDebug;
};

#endif
