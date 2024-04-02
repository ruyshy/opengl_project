#pragma once

#ifndef OBJECT_H_
#define OBJECT_H_

class ObjectBase
{
public:
	ObjectBase() = delete;
	ObjectBase(unsigned int ID, string Name = "GameObject");
	virtual ~ObjectBase();

public:
	unsigned int GetID();
	string GetName();

	void SetID(unsigned int id);
	void SetName(string name);

private:
	unsigned int mID;
	string mName;
};

#endif // !GOBJECT_H_

