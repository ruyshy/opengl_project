#pragma once

#ifndef GOBJECT_H_
#define GOBJECT_H_

class GObjectBase
{
public:
	GObjectBase() = delete;
	GObjectBase(unsigned int ID, string Name = "GameObject");
	virtual ~GObjectBase();

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

