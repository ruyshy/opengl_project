#include <pch.h>
#include <utill/TimeMeasure.h>

TimeMeasure::TimeMeasure(int type)
{
	mType = type;
	mStart = clock();
}

void TimeMeasure::Restart()
{
	mStart = clock();
}

float TimeMeasure::GetTime()
{
	mEnd = clock();
	return static_cast<float>(float(mEnd - mStart) / CLOCKS_PER_SEC);
}
