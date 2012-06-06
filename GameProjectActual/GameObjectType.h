#ifndef __GAMEOBJECTTYPE__H__
#define __GAMEOBJECTTYPE__H__

class GameObjectType
{
public:
	explicit GameObjectType(char const * const pTypeName)
		: mTypeName(pTypeName), mTypeID(HashName(pTypeName))
	{}

	unsigned long GetTypeID() const { return mTypeID; }
	char const * const GetTypeName() const { return mTypeName; }

	bool operator< (GameObjectType const & o) const { return (GetTypeID() < o.GetTypeID()); }
   	bool operator== (GameObjectType const & o) const { return (GetTypeID() == o.GetTypeID()); }
	bool operator== (char const * c) const { return (mTypeName == c); }
	bool operator!= (GameObjectType const & o) const { return (GetTypeID() != o.GetTypeID()); }

	static unsigned long HashName(char const * const pTypeName);

private:

	unsigned long mTypeID;
	char const * mTypeName;
};

#endif
