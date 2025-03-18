#ifndef PAIROFXY_H
#define PAIROFXY_H

struct PairOfXY
{
	int x, y;
}; // To represent a position or area

void copyPairOfXYArray(const PairOfXY* oldArr, PairOfXY* newArr, const int sz);

#endif // PAIROFXY_H
