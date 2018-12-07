#ifdef WIN32
#include <Windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif
 
/*
#ifdef WIN32
typedef unsigned int(__stdcall *thread_func)(void*);
#else
typedef void*(*thread_func)(void*);
#endif
*/
 
class base_thread
{
public:
	base_thread();
	virtual ~base_thread();
 
	bool create();
	void wait();
	virtual void run() = 0;
 
#ifdef WIN32
	static unsigned __stdcall thread_func(void* arg);
#else
	static void* thread_func(void* arg);
#endif
 
protected:
#ifdef WIN32
	HANDLE m_handle;
#else
	pthread_t m_thread_t;
#endif
};
 
#endif
