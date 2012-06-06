#ifndef __ISCORELISTENER_H__
#define __ISCORELISTENER_H__

class IScoreListener
{
public:
	virtual void OnScoreChanged(int score) = 0;
};

#endif