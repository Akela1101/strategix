/* 
 * File:   StraxSingleton.h
 * Author: akela
 *
 * Created on 2 Апрель 2010 г., 17:58
 */

#ifndef _STRAXSINGLETON_H
#define	_STRAXSINGLETON_H

namespace Strategix
{
	template<typename T>
	class StraxSingleton
	{
	private:
		static T *instance;

	protected:
		StraxSingleton() {}

	private:		
		StraxSingleton(const StraxSingleton<T> &);
		StraxSingleton &operator=(const StraxSingleton<T> &);

	public:
		// Get singleton
		static T &GS()
		{
			if( !instance )
				instance = new T();
			return *instance;
		}
	};

	template<typename T>
	T* StraxSingleton<T>::instance = 0;
}

#endif	/* _STRAXSINGLETON_H */

