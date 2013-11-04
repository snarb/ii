#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\EntityGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{		
	TEST_CLASS(TestBasicEntityGenerator) 
	{
	private:
		EntityGenerator* entityGenerator;
		Entity* testEntity;

	public:
		TEST_METHOD_INITIALIZE(ClassInitialize)
		{
			entityGenerator = new EntityGenerator();
			testEntity = &entityGenerator->GenerateEntity();
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
			delete entityGenerator;
			delete testEntity;
		}

		TEST_METHOD(TestExternalOutputs)
		{
			OperatorsTypes opType = (OperatorsTypes) testEntity->mGetOperatorType(ExternalOutputsCount);
			Assert::IsTrue(opType == ExternalOutput);
		}

		TEST_METHOD(TestExternalInputs)
		{
			OperatorsTypes opType = (OperatorsTypes) testEntity->mGetOperatorType(ExternalOutputsCount + ExternalInputsCount);
			Assert::IsTrue(opType == ExternalInput);
		}

		TEST_METHOD(GeneratedOperatorsTypesAreValid)
		{
			for (size_t i = 0; i < 1000; i++)
			{
				Entity* curEntity = &entityGenerator->GenerateEntity();
				for (mainDataType i = Entity::FirstInternalOper; i < EntityOperatorsCount; i++)
				{
					OperatorsTypes curOperType = (OperatorsTypes) curEntity->mGetOperatorType(i);
					Assert::IsTrue(curOperType >  OperatorsTypes::Zero && curOperType < OperatorsTypes::ExternalInput);
				}

				delete curEntity;
			}
		}

		TEST_METHOD(GeneratedOperatorsIdsAreValid)
		{
			Entity* curEntity;
			for (size_t i = 0; i < 1000; i++)
			{
				curEntity = &entityGenerator->GenerateEntity();
				for (mainDataType curOp = Entity::FirstInternalOper; curOp < EntityOperatorsCount; curOp++)
				{
					OperatorsTypes curOperType = (OperatorsTypes)curEntity->mGetOperatorType(curOp);
					for (int curContact = 1; curContact <= EntityGenerator::GetOperTypeContactsCount(curOperType); curContact++)
					{
						mainDataType curVal = curEntity->GetContactValue(curOp, curContact);
						if (!(curVal > 0 && curVal < curEntity->GetNextOperatorId()))
						{
							curVal = curVal;
						}

						Assert::IsTrue(curVal > 0 && curVal < curEntity->GetNextOperatorId());
					}
				}
				delete curEntity;
			}
		}

		TEST_METHOD(LastGeneratedOperatorIsNotZero)
		{
			Entity* curEntity;
			for (size_t i = 0; i < 1000; i++)
			{
				curEntity = &entityGenerator->GenerateEntity();
				mainDataType lastOpId = curEntity->GetOperatorsCount();
				Assert::IsTrue(curEntity->GetContactValue(lastOpId, 0) != Zero);
				delete curEntity;
			}
		}
	};
}