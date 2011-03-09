
// by some good guy who I don't really know...


#ifndef _OBJECTTITLE_H
#define	_OBJECTTITLE_H

#include "Ogre.h"

namespace Sample1
{
	using namespace Ogre;

	class ObjectTitle
	{
		const MovableObject* object;
		const Camera* camera;
		Overlay* overlay;
		OverlayElement* textArea;
		OverlayContainer* container;
		Vector2 textDim;
		Font* font;
		bool isShow;

	public:
		ObjectTitle(const String& name, MovableObject* object, Camera* camera, const String& title,
				const String& fontName, const ColourValue& color = ColourValue::White);
		~ObjectTitle();

		void setTitle(const String& title);
		void setColor(const ColourValue& color);
		void update();
		void show(bool isShow);

	protected:
		Vector2 getTextDimensions(String text);
	};
}

#endif	/* _OBJECTTITLE_H */

