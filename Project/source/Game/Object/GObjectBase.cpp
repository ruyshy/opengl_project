#include <pch.h>
#include <Game/Object/GObjectBase.h>

GObjectBase::GObjectBase(unsigned int ID, string Name)
{
	mID = ID;
	mName = mName;
}

GObjectBase::~GObjectBase() {}

unsigned int GObjectBase::GetID() { return mID; }
string GObjectBase::GetName() { return mName; }

void GObjectBase::SetID(unsigned int id) { mID = id; }
void GObjectBase::SetName(string name) { mName = name; }

