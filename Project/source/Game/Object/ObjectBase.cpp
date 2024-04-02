#include <pch.h>
#include <Game/Object/ObjectBase.h>

ObjectBase::ObjectBase(unsigned int ID, string Name)
{
	mID = ID;
	mName = mName;
}

ObjectBase::~ObjectBase() {}

unsigned int ObjectBase::GetID() { return mID; }
string ObjectBase::GetName() { return mName; }

void ObjectBase::SetID(unsigned int id) { mID = id; }
void ObjectBase::SetName(string name) { mName = name; }

