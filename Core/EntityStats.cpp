#include "stdafx.h"
#include "EntityStats.h"

namespace Brans
{
	EntityStats::EntityStats() : _correctAnswersCount(0), _effectiveness(0)
	{
	}

		EntityStats::~EntityStats()
	{
	}

	void EntityStats::SetEntity(Entity id)
	{
		_id = id;
	}

	void EntityStats::AddAnswer(bool result)
	{
		_correctAnswersCount += result;
	}

	Entity EntityStats::GetEntity()
	{
		return _id;
	}

	void EntityStats::CalculateEffectiveness(mainDataType totalAnswersCount)
	{
		_effectiveness = _correctAnswersCount / (double)totalAnswersCount;
	}

	double EntityStats::GetEffectiveness()
	{
		return _effectiveness;
	}
}
