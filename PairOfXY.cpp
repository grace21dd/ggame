#include "PairOfXY.h"

void copyPairOfXYArray(const PairOfXY* oldArr, PairOfXY* newArr, const int sz)
{
	for (int i = 0; i < sz; ++i) {
		newArr[i] = oldArr[i];
	}
}
