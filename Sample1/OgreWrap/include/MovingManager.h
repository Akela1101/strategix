/* 
 * File:   MovingManager.h
 * Author: Akela1101
 *
 * Created on 22 Апрель 2010 г., 21:10
 */

#ifndef _MOVINGMANAGER_H
#define	_MOVINGMANAGER_H

#include "Nya.hpp"
#include "EntityManager.h"

#include "Kernel.h"
#include <deque>

namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;

	class MovingManager : public EntityManager
	{
	protected:
		Real distance; // The distance the object has left to travel
		Vector3 direction; // The direction the object is moving
		Vector3 destination; // The destination the object is moving towards
		std::deque<Strategix::MapCoord> *walkList; // The list of points we are walking on
		Real walkSpeed; // The speed at which the object is moving

	public:
		MovingManager(Player *player, const String &name, const MapCoord &mapCoord);
		virtual ~MovingManager();
		virtual bool frameRenderingQueued(const FrameEvent &event);

		void AddWayTo(Vector3 &pos); // Mouse pointer intersection with earth

		void AddWayTo_Debug(Vector3 &pos);

	protected:
		void MoveOnTime(Real time);
		Strategix::MapCoord GetMapCoord(const Vector3 &pos);
		Vector3 GetDiscretePos(const Strategix::MapCoord &mapCoord);
		Vector3 GetDiscretePos(const Vector3 &pos);
	};
}

#endif	/* _MOVINGMANAGER_H */

