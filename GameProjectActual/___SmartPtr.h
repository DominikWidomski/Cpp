//-------------------------------------------------------------
// Author: Erez Efrati (ereze@netmedia.net.il)
//
// A template smart pointer.
// It is suitable for any class or simple type,
// because it does not assume that the type supports reference
// counting interface.
//
// History:
//			14-09-1999 original version
//
//
// You may freely use or modify this code provided that above notice
// and notes on your changes are included in all derived versions.
//-------------------------------------------------------------
#ifndef SMART_PTR_H
#define SMART_PTR_H

#pragma warning (disable: 4284)

#ifdef _DEBUG
#define DBG(expr) expr
#else
#define DBG(expr)
#endif

#include <assert.h>

//-------------------------------------------------------------
// NAME: RefCountRep
//
// DESCRIPTION:
//	This template implements the reference counting. When the
//	reference count drops down to 0 the referenced object
//	is freed.
//-------------------------------------------------------------
template <class T> class RefCountRep
{
	public:

		explicit RefCountRep (T* pT = 0);

		template <class U> RefCountRep (RefCountRep<U>& x) {

			m_ptr = x.m_ptr;
			// READ THIS ERROR DESCRIPTION:
			// Getting an compilation error here, means that
			// you are probably trying to perform the following:
			//
			// a) pDerivedClass = pBaseClass;
			// b) assigning non-related pointers.
			//
			// Unfortunately the compiler does let you see
			// the original source line.
		};

		RefCountRep (const RefCountRep& x):
				m_count(x.m_count), m_ptr(x.m_ptr){};

		~RefCountRep ();

		void ReleaseRef ();
		void AddRef ();
		T*	GetRealPointer () const;

		long	m_count;
		T*		m_ptr;
};


template <class T>
   RefCountRep<T>::RefCountRep (T* pT)
   : m_count(1), m_ptr (pT)
{
}

// we get to here because the RefCountRep::ReleaseRef
// deleted this (committed suicide) once it noticed
// that no one really holds.
template <class T>
   RefCountRep<T>::~RefCountRep ()
{
	if (m_ptr != 0)
		delete m_ptr;
}

template <class T>
   void RefCountRep<T>::ReleaseRef ()
{
	assert (m_count > 0);

	m_count--;
	if (m_count == 0)
		delete this;
}

template <class T>
   void RefCountRep<T>::AddRef ()
{
	assert (m_count >= 0);
	m_count++;
}

template <class T>
   T* RefCountRep<T>::GetRealPointer () const
{
	assert (m_ptr != 0);
	return m_ptr;
}


//-------------------------------------------------------------
// NAME: SmartPtr
//
// DESCRIPTION:
//	This is the smart pointer template.
//-------------------------------------------------------------
template <class T> class SmartPtr
{
	public:
		~SmartPtr ();

		SmartPtr (T* ptr = 0);

		template <class U> SmartPtr (const SmartPtr<U>& that) {

			// the following line is for debugging purposes only!
			// Compilation of the following line makes sure that
			// the class U is derived from class T or the same, and
			// assigning pT = pU is legal. This makes the SmartPtr<T>
			// behaves like a normal pointer with all of its constrains.
			DBG (RefCountRep<T> URep = RefCountRep<U>());

			m_pRep = reinterpret_cast<RefCountRep<T>* > (that.m_pRep);
			AddRef ();
		}

		SmartPtr (const SmartPtr& that) {
			m_pRep = that.m_pRep;
			AddRef ();
		}

		template <class U> SmartPtr& operator= (const SmartPtr<U>& that) {

			// the following line is for debugging purposes only!
			// Compilation of the following line makes sure that
			// the class U is derived from class T or the same, and
			// assigning pT = pU is legal. This makes the SmartPtr<T>
			// behaves like a normal pointer with all of its constrains.
			DBG (RefCountRep<T> URep = RefCountRep<U>());

			if (m_pRep != reinterpret_cast<RefCountRep<T>* > (that.m_pRep))
			{
				ReleaseRef ();
				m_pRep = reinterpret_cast<RefCountRep<T>* > (that.m_pRep);
				AddRef ();
			}
			return *this;
		}

		SmartPtr& operator= (const SmartPtr& that)
		{
//			if (this != &that)
			if (m_pRep != that.m_pRep)
			{
				ReleaseRef ();
				m_pRep = that.m_pRep;
				AddRef ();
			}

			return *this;
		}


		SmartPtr& operator= (T*);

		T&	operator* ();
		T*	operator-> ();
		operator T* () { return m_pRep != 0 ? m_pRep->GetRealPointer() : 0; }

		void ReleaseRef ();
		void AddRef ();

		// data
		RefCountRep<T>	*m_pRep;

};


template <class T>
   SmartPtr<T>::SmartPtr (T* ptr)
   : m_pRep (0)
{
	if (ptr != 0)
		m_pRep = new RefCountRep<T> (ptr);
}

template <class T>
   SmartPtr<T>::~SmartPtr ()
{
	ReleaseRef ();
}


template <class T>
 SmartPtr<T>& SmartPtr<T>::operator= (T* pT)
{
	ReleaseRef ();
	if (pT != 0)
		m_pRep = new RefCountRep<T> (pT);

	return *this;
}

template <class T>
 T&	SmartPtr<T>::operator* ()
{
	assert (m_pRep != 0);
	return *(m_pRep->GetRealPointer ());
}


template <class T>
 T*	SmartPtr<T>::operator -> ()
{
	assert (m_pRep != 0);
	return m_pRep->GetRealPointer ();
}

template <class T>
void SmartPtr<T>::ReleaseRef ()
{
	if (m_pRep != 0)
		m_pRep->ReleaseRef ();
}

template <class T>
void SmartPtr<T>::AddRef ()
{
	if (m_pRep != 0)
		m_pRep->AddRef ();
}

#endif // SMART_PTR_H
