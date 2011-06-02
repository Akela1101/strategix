
// by some good guy


#ifndef _OBJECTTITLE_H
#define	_OBJECTTITLE_H

#include <Ogre.h>


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
		ObjectTitle(MovableObject* object, const String& title,
				const String& fontName, const ColourValue& color = ColourValue::White);
		virtual ~ObjectTitle();

		void setTitle(const String& title);
		void setColor(const ColourValue& color);
		void update();
		void show(bool isShow);

	private:
		ObjectTitle(const ObjectTitle&);
		ObjectTitle& operator=(const ObjectTitle&);


	protected:
		Vector2 getTextDimensions(String text);
	};
}

#endif	/* _OBJECTTITLE_H */

