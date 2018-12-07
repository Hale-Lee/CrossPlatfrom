#include "base_thread.h"

base_thread::base_thread()
{
#ifdef WIN32
	m_handle = NULL;
#else
	m_thread_t = 0;
#endif
}
 
base_thread::~base_thread()
{
#ifdef WIN32
	if (NULL != m_handle)
	{
		CloseHandle(m_handle);
	}
	m_handle = NULL;
#else
	m_thread_t = 0;
#endif
}
 
bool base_thread::create()
{
	bool ret = false;
#ifdef WIN32
	m_handle = (HANDLE)_beginthreadex(NULL, 0, thread_func, this, 0, NULL);
	if (NULL != m_handle)
	{
		ret = true;
	}
#else
	if (0 == pthread_create(&m_thread_t, NULL, thread_func, this))
	{
		ret = true;
	}
	else
	{
		m_thread_t = 0;
	}
#endif
	return ret;
}
 
void base_thread::wait()
{
#ifdef WIN32
	WaitForSingleObject(m_handle, INFINITE);
	if (NULL != m_handle)
	{
		CloseHandle(m_handle);
	}
	m_handle = NULL;
#else
	pthread_join(m_thread_t, NULL);
	m_thread_t = 0;
#endif // WIN32
}
 
#ifdef WIN32
unsigned __stdcall base_thread::thread_func(void* arg)
#else
void* base_thread::thread_func(void* arg)
#endif
{
	base_thread *pthis = (base_thread*)arg;
	pthis->run();
	return NULL;

}