/* 
 * File:   StrategixSingleton.h
 * Author: akela
 *
 * Created on 2 Апрель 2010 г., 17:58
 */

#ifndef _STRAXSINGLETON_H
#define	_STRAXSINGLETON_H

namespace Strategix
{
	template<typename T>
	class StrategixSingleton
	{
	private:
		static T *instance;

	protected:
		StrategixSingleton() {}

	private:		
		StrategixSingleton(const StrategixSingleton<T> &);
		StrategixSingleton &operator=(const StrategixSingleton<T> &);

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
	T* StrategixSingleton<T>::instance = 0;
}

#endif	/* _STRAXSINGLETON_H */

