
#ifndef BUTTON_H
#define	BUTTON_H

#include "Quadrilateral.h"

class Button : public Quadrilateral
{
public:
	Button();
	~Button();

private:
	std::string buttonName;
};

#endif	/* BUTTON_H */