/* 
 * File:   Feature.h
 * Author: Akela1101
 *
 * Created on 23 Март 2011 г., 16:05
 */

#ifndef _FEATURE_H
#define	_FEATURE_H

namespace Strategix
{
	class Enti;

	class Feature
	{
	protected:
		Enti *enti;
		
	public:
		Feature();
		virtual ~Feature() = 0;

		virtual void Tick(const float seconds) {}

	private:
		Feature(const Feature &_c);
		Feature & operator =(const Feature &_c);
	};
}

#endif	/* _FEATURE_H */

