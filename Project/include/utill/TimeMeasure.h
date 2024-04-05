#pragma once

#ifndef TIMEMEASURE_H_
#define TIMEMEASURE_H_

class TimeMeasure
{
public:
	TimeMeasure(int type = 0);
	~TimeMeasure() {}

	void Restart();
	float GetTime();

	int mType = 0;
	clock_t mStart, mEnd;
};

#endif // !TIMEMEASURE_H_
