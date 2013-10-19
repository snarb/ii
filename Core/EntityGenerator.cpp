#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"

namespace Brans 
{
	EntityGenerator::EntityGenerator()
	{
		_conProvider = new RandomValuesProvider(EntityOperatorsCount);
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	Entity& EntityGenerator::GenerateEntity()
	{
		Entity* ent= new Entity();
	
		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating oper
			ent->mCreateOperator(RandomOperatorsProvider::GetNextOperator());

			OperatorsTypes lastOperType = (OperatorsTypes)ent->mGetOperatorType(curOper);
			//Creating connections
			for (int curContact = 0; curContact <= GetOperTypeContactsCount(lastOperType); curContact++)
			{
				ent->mCreateChannel(_conProvider->GetNextValue(), curOper, curContact);
			}
		}

		return *ent;
	}

	mainDataType EntityGenerator::GetOperTypeContactsCount(OperatorsTypes ot)
	{
		switch (ot)
		{
		case Brans::Zero:
			return 0;
			break;
		case Brans::Division:
			return 2;
			break;
		case Brans::Equal:
			return 1;
			break;
		case Brans::If:
			return 2;
			break;
		case Brans::Minus:
			return 2;
			break;
		case Brans::Multiplication:
			return 2;
			break;
		case Brans::One:
			return 0;
			break;
		case Brans::Plus:
			return 2;
			break;
		case Brans::RandomNumber:
			return 1;
			break;
		case Brans::Time:
			return 0;
			break;
		case Brans::CreateChannel:
			return 3;
			break;
		case Brans::CreateOperator:
			return 1;
			break;
		case Brans::DeleteChannel:
			return 2;
			break;
		case Brans::GetTypeOfOperator:
			return 0;
			break;
		case Brans::IsChannelExists:
			return 3;
			break;
		case Brans::RemoveOperator:
			return 1;
			break;
		case Brans::GetInputOperatorId:
			return 1;
			break;
		case Brans::GetOperatorContactsCount:
			break;
		case Brans::ExternalInput:
			break;
		case Brans::ExternalOutput:
			break;
		case Brans::Nothing:
			break;
		default:
			break;
		}
	}
}