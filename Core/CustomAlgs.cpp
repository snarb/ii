#include "stdafx.h"
#include "CustomAlgs.h"

namespace Brans
{
	//Quick selection alhorithm. Selects the Kth MINIMAL value from the array according to the Effectiveness
	EntityStats CustomAlgs::SelectKth(EntityStats* arr, mainDataType k, mainDataType arrayElementsCount)
	{
		int from = 0, to = arrayElementsCount - 1;

		// if from == to we reached the kth element
		while (from < to) {
			int r = from, w = to;
			double mid = arr[(r + w) / 2].GetEffectiveness();

			// stop if the reader and writer meets
			while (r < w) {
				if (arr[r].GetEffectiveness() >= mid) { // put the large values at the end
					EntityStats tmp = arr[w];
					arr[w] = arr[r];
					arr[r] = tmp;
					w--;
				} else { // the value is smaller than the pivot, skip
					r++;
				}
			}

			// if we stepped up (r++) we need to step one down
			if (arr[r].GetEffectiveness() > mid)
				r--;

			// the r pointer is on the end of the first k elements
			if (k <= r) {
				to = r;
			} else {
				from = r + 1;
			}
		}

		return arr[k];
	}

	//Returns n elements array of the EntityStats
	EntityStats* CustomAlgs::SelectTopNs(EntityStats* arr, mainDataType n, mainDataType arrayElementsCount)
	{
		EntityStats* retAr = new EntityStats[n];
		unsigned short curRetArIndex = 0;
		double targetK = SelectKth(arr, arrayElementsCount - n, arrayElementsCount).GetEffectiveness();

		for (int i = 0; i < arrayElementsCount; i++)
		{
			if (arr[i].GetEffectiveness() >= targetK)
			{
				retAr[curRetArIndex] = arr[i];
				curRetArIndex++;
			}
		}

		return retAr;
	}
}