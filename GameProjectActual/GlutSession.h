#ifndef __GLUTSESSION_H__
#define __GLUTSESSION_H__

#include <map>

using namespace std;

class GlutWindow;
class ITimerListener;

typedef unsigned int uint;
typedef unsigned char uchar;

class GlutSession
{
public:
	inline static GlutSession& GetInstance(void)
	{
		static GlutSession mInstance;
		return mInstance;
	}

	GlutWindow* GetWindow(void);
	void SetWindow(GlutWindow* w);

	void DisableIdleFunction(void) { mIdleFunctionEnabled = false; }
	void EnableIdleFunction(void) { mIdleFunctionEnabled = true; }
	bool IdleFunctionEnabled(void) { return(mIdleFunctionEnabled); }

	static void RegisterSessionTimer(uint msecs, int value);
	static void RegisterWindowTimer(uint msecs, int value);

	static void Init(int &argc, char* argv[]);
	static void Start(void);
	static void Stop(void);

	void SetTimer(uint msecs, ITimerListener* listener, int value = 0);
	void OnTimer(int value);

private:
	GlutSession(void) {}
	~GlutSession(void) {}

	typedef pair<ITimerListener*, int> ListenerValuePair;
	typedef map<int, ListenerValuePair> TimerListenerMap;
	TimerListenerMap mTimerListeners;

	static void CallBackDisplayFunc(void);
	static void CallBackIdleFunc(void); 
	static void CallBackKeyboardFunc(uchar key, int x, int y);
	static void CallBackKeyboardUpFunc(uchar key, int x, int y);
	static void CallBackSpecialFunc(int key, int x, int y);   
	static void CallBackSpecialUpFunc(int key, int x, int y);   
	static void CallBackMotionFunc(int x, int y);
	static void CallBackMouseFunc(int button, int state, int x, int y);
	static void CallBackPassiveMotionFunc(int x, int y);
	static void CallBackReshapeFunc(int w, int h); 
	static void CallBackVisibilityFunc(int visibility);
	
	static void CallBackSessionTimerFunc(int value);
	static void CallBackWindowTimerFunc(int value);

	static void RegisterCallbacks(void);

	static GlutWindow* mWindow;
	static bool mIdleFunctionEnabled;
};

#endif