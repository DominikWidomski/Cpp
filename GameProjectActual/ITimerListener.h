#ifndef __ITIMERLISTENER_H__
#define __ITIMERLISTENER_H__

class ITimerListener
{
public:
	virtual void OnTimer(int value) = 0;
};

#endif