#pragma once

#ifndef EVENT_H_
#define EVENT_H_

template <typename T>
class Event 
{
protected:
	T _type;
	string _name;
	bool _handled = false;
public:
	Event() = default;
	Event(T type, const std::string& name = "") : _type(type), _name(name) {};
	inline const T type() const { return _type; };
	inline const std::string& getName() const { return _name; };
	virtual bool isHandled() { return _handled; };
private:
};


#endif // !EVENT_H_
