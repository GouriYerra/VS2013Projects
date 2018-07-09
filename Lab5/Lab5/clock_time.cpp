//Header files
#include "clock_time.h"
#include <iomanip>

clock_time::clock_time()
{
	_seconds = 0;
}

clock_time::clock_time(int h, int m, int s)
{
	set_time(h, m, s);
}

void clock_time::set_time(int h, int m, int s)
{
	_seconds = (h * 60 * 60) + (m * 60) + s;
	_seconds = test_sec(_seconds);
}

int clock_time::get_hour()
{
	if (((_seconds / 3600) % 24) >= 0) 
	{
		return (_seconds / 3600) % 24;
	}
	else
	{
		return ((_seconds / 3600) % 24) + 23;
	}
}

int clock_time::get_minute()
{
	return (_seconds % 3600) / 60;
}

int clock_time::get_second()
{
	return _seconds % 60;
}

int clock_time::test_sec(int sec)
{
	if (sec < 0)
	{
		sec = 24 * 3600 + sec;
	}
	else if (sec > 24 * 3600 - 1)
	{
		sec = sec - (24 * 3600);
	}
	return sec;
}

bool operator==(clock_time &t1, clock_time &t2)
{
	return (t1._seconds == t2._seconds);
}

bool operator !=(clock_time &t1, clock_time &t2)
{
	return (t1._seconds != t2._seconds);
}

clock_time operator+(clock_time &t1, clock_time &t2) 
{
	int sec = t1._seconds + t2._seconds;
	clock_time a = clock_time(0, 0, sec);
	return a;
}

ostream& operator<<(ostream & out, clock_time c)
{
	out << to_string(c);
	return out;
}

string to_string(clock_time c)
{
	stringstream t;
	t << c.get_hour() << ":" << setfill('0') << setw(2) << c.get_minute() << ":" << setfill('0') << setw(2) << c.get_second();
	return t.str();
}