#include "time_util.h"
#include <sys/time.h>
#include <unistd.h>

using namespace std;


int TimeUtil::GetTimestamp() 
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return tv.tv_sec;
}

std::string TimeUtil::GetTimestampStr() 
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	string ts = to_string(tv.tv_sec) + "_" + to_string(tv.tv_usec);
	return ts;
}
