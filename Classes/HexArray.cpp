#include "HexArray.h"


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

HexArray* HexArray2D::row(size_t index)
{
	if(index < hexagons.size()){
		return hexagons[index];
	}else{
		return NULL;
	}
}


Hexagon* HexArray2D::at(int x, int y)
{
	HexArray* arr = row(y);
	if(!arr) return NULL;

	return arr->at(x);
}


Hexagon* HexArray2D::sideHexAt(HexSide side, size_t x, size_t y)
{
	switch(side){
		case HexTopLeft: y-=1; break;
		case HexTopRight: x+=1; y-=1; break;
		case HexLeft: x-=1; break;
		case HexRight: x+=1; break;
		case HexBottomLeft: y+=1; break;
		case HexBottomRight: x+=1; y+=1; break;
	}

	return at(x, y);
}
