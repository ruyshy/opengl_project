#pragma once

#ifndef EVENT_H_
#define EVENT_H_

template <typename T>
class Event 
{
protected:
	T _type;
	std::string _name;
	bool _handled = false;
public:
	Event() = default;
	Event(T type, const std::string& name = "") : _type(type), _name(name) {};
	inline const T GetType() const { return _type; };
	inline const std::string& GetName() const { return _name; };
	virtual bool IsHandled() { return _handled; };
private:
};


#endif // !EVENT_H_
