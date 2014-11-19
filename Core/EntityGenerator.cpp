#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"
#include "assert.h"

namespace Brans 
{
	static const unsigned short ExternalOutputsCountAdd = ExternalOutputsCount + 1; // We didn't connect  from ExternalOutputs to opers

	EntityGenerator::EntityGenerator() : _entity(), _operatorsConProvider(EntityOperatorsCount, ExternalOutputsCountAdd),
		_externalOutputsConProvider(EntityOperatorsCount, ExternalOutputsCountAdd + ExternalInputsCount)
	{
		state[0] = 0;

		for (size_t i = 1; i < EntityInternalOperatorsCount; i++)
		{
			state[i] = OperatorsTypes::If;
		}
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	bool EntityGenerator::NextEntityCore()
	{
		for (int curOper = 0; curOper < EntityInternalOperatorsCount; curOper++) {
			state[curOper]++;
			if (state[curOper] <= OperatorsTypes::Plus) {
				for (int nextOper = 0; nextOper < curOper; nextOper++) {
					state[nextOper] = state[curOper];
				}
				return true;
			}
		}

		// no more legal values
		return false;
	}

	Entity& EntityGenerator::GenerateEntity()
	{
		static ULONGLONG stat[OperatorsTypesCount] = {};

		_entity.Reset();

		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating opers
			int operType = RandomOperatorsProvider::GetNextOperator();
			stat[operType]++;
			_entity.mCreateOperatorUnsafe(operType);
		}

		for (int curOper = Entity::FirstExtOutputPos; curOper <= ExternalOutputsCount; curOper++)
		{
			GenerateConnections(curOper);
		}

		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			GenerateConnections(curOper);
		}

		return _entity;
	}

	void EntityGenerator::GenerateConnections(mainDataType toOper)
	{
		OperatorsTypes operType = static_cast<OperatorsTypes>(_entity.mGetOperatorTypeUnsafe(toOper));
		mainDataType operTypeCntsCount = Entity::mGetOperTypeContactsCountUnsafe(operType);

		for (int curContact = Entity::FirstContact; curContact <= operTypeCntsCount; curContact++)
		{
			mainDataType fromOper = _operatorsConProvider.GetNextValue();
			CreateChannelIfAppropriate(toOper, curContact, fromOper);
		}
	}

	void EntityGenerator::CreateChannelIfAppropriate(mainDataType toOper, mainDataType curOperContactId, mainDataType fromOper)
	{
		for (size_t i = 0; i < EntityOperatorsCount - ExternalOutputsCount; i++)
		{
			if ((toOper != fromOper) && _entity.HasOperExit(fromOper)) //ToDo: Add compatibility, at least with time check?
			{
				_entity.mCreateChannelUnsafe(fromOper, toOper, curOperContactId);
				break;
			}
			else
			{
				fromOper++;

				if (fromOper == Entity::FirstExtOutputPos)
				{
					fromOper += ExternalOutputsCount;
				}

				if (fromOper == EntityOperatorsCount)
				{
					fromOper = Entity::FirstExtInputPos;
				}
			}
		}
	}
}