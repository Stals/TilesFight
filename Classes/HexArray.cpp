#include "HexArray.h"


size_t HexArray::size()
{
	return row.size();
}

Hexagon* HexArray::at(size_t index)
{
	if(index < row.size()){
		return row[index];
	}else{
		return NULL;
	}
}

void HexArray::push_back(Hexagon* hex)
{
	row.push_back(hex);
}

// -----------------------------------------------------------------

HexArray2D::~HexArray2D()
{
	while(!hexagons.empty()) delete hexagons.back(), hexagons.pop_back();
}

size_t HexArray2D::size()
{
	return hexagons.size();
}

void HexArray2D::addRow()
{
	hexagons.push_back(new  HexArray);
}

HexArray* HexArray2D::row(size_t index)
{
	if(index < hexagons.size()){
		return hexagons[index];
	}else{
		return NULL;
	}
}


Hexagon* HexArray2D::at(size_t x, size_t y)
{
	HexArray* arr = row(y);
	if(!arr) return NULL;

	return arr->at(x);
}


Hexagon* HexArray2D::sideHexAt(HexSide side, size_t x, size_t y)
{
	bool even = (y % 2) == 0;

	switch(side){
		case HexTopLeft:
			if(even){x-=1;} 
			y-=1;
			break;
		case HexTopRight: 
			if(!even){x+=1;} 
			y-=1;
			break;
		case HexLeft: 
			x-=1; 
			break;
		case HexRight: 
			x+=1; 
			break;
		case HexBottomLeft: 
			if(even){x-=1;}
			y+=1; 
			break;
		case HexBottomRight:
			if(!even){x+=1;} 
			y+=1; 
			break;
	}

	return at(x, y);
}


bool HexArray2D::areConnected(Hexagon* first, Hexagon* second)
{
	const size_t x = first->getXCoord();
	const size_t y = first->getYCoord();

	for(int side = 0; side < HexSidesCount; ++side)	{
		Hexagon* hex = sideHexAt((HexSide)side, x, y);
		if(hex && (second == hex)){
			return true;
		}
	}

	return false;
}
