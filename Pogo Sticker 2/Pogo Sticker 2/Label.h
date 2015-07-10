#ifndef LABEL_H
#define LABEL_H

#include "Sprite.h"
#include <string>

namespace gameEngine {

	/* A text label which can be updated. Also a function can be supplied for
	additional behaviour. */
	class Label : public Sprite
	{
	public:
		/* A name for a function pointer is defined for easier reference. */
		typedef std::string(*FuncPtr)();

		/* Protected constructors (allow subclasses) and public getInstance
		methods to only allow dynamic instantiation of this class. */
		static Label* getInstance(int x, int y, int w, int h, std::string text,
			FuncPtr fp);
		static Label* getInstance(int x, int y, int w, int h, std::string text);

		void tick(); // Inherited from Sprite
		std::string getText();
		void setText(std::string text);
		~Label();
	protected:
		Label(int x, int y, int w, int h, std::string text, FuncPtr fp);
		Label(int x, int y, int w, int h, std::string text);
	private:
		Label(const Label&);		   			/* Value semantics is disabled. */
		const Label& operator=(const Label&);	/* Value semantics is disabled. */

		static const SDL_Color black;
		std::string text;
		FuncPtr funcPtr;
	};

}

#endif