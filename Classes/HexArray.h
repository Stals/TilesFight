#pragma once
#include <vector>

#include "Hexagon.h"

enum HexSide{
	HexTopLeft,
	HexTopRight,
	HexLeft,
	HexRight,
	HexBottomLeft,
	HexBottomRight,
	HexSidesCount
};

class HexArray{
public:
	Hexagon* at(size_t index);
	void push_back(Hexagon* hex);

	size_t size();

private:
	std::vector<Hexagon*> row;
};


//2d array of hexes with flat parts on left and right
/*
	 /\
	|  |
	 \/
*/

// NOTE:
/*
	При верианте где начинается вот так
		*****
		 *****
		*****
	Обращение идет просто вверх чтобы получить сверху слева, Направо вверх чтобы получить то что справа сверху
	Направо и налево как обычно
	Снизу также как сверху

	!ЕСЛИ ЖЕ!
	Нужно будет сделать
		 *****
		*****
		 *****
	то нужно будет делать обращения вверх влево для вверх влево.
	И Вверх по индексам для того чтобы получить hex которых находится сверху справа. И тоже для тех что снизу
*/
class HexArray2D
{
public:
	~HexArray2D();

	void addRow();
	HexArray* row(size_t index);
	Hexagon* at(size_t x, size_t y);
	// Возвращает hexagon в сторону от переданных координат
	// Note: Можно проитерировать по Hex со всех сторон [for(HexSide side = 0; side < HexSidesCount; ++side)]
	Hexagon* sideHexAt(HexSide side, size_t x, size_t y);

	size_t size();

private:
	std::vector<HexArray* > hexagons;
};

// TODO добавить получения Hexagon'a со стороны в сам Hexagon?
// чтобы он лез в array этот?
