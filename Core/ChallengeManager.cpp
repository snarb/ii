#include "stdafx.h"
#include "ChallengeManager.h"
#include <vector>

namespace Brans
{
	ChallengeManager* ChallengeManager::_chManager;

	ChallengeManager::ChallengeManager() : _inputs(), _correctAnswers(), _entityGenerator(), _rvp(RandomUpperLimit),
		_curEntityId(0), _currentLine(0), _goodPopulation()
	{
		_curChallangeType = ChallengeTypes::One;
		_chManager = this;
		srand_sse();
	}

	ChallengeManager::~ChallengeManager()
	{
	}

	void ChallengeManager::SetChallengeType(ChallengeTypes chType)
	{
		_curChallangeType = chType;
	}

	void ChallengeManager::GenerateRandomInputs()
	{
		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 0; i < ExternalInputsCount; i++)
			{
				_inputs[cline][i] = _rvp.GetNextValue();
			}
		}
	}

	void ChallengeManager::FillAnswers()
	{
		static const unsigned short rex = ExternalOutputsCount - 1;

		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 0; i < rex;)
			{
				mainDataType nextI = i + 1;
#define fContValue _inputs[cline][i] //value of first contact
#define sContValue _inputs[cline][nextI] //value of second contact
#define outValue _correctAnswers[cline][i] //value of third contact

				switch (_curChallangeType)
				{
				case (Division) :
					if (sContValue != 0) {
						outValue = fContValue / sContValue;
					}
					break;
				case (Equal) :
					outValue = fContValue;
					break;
				case (If) :
					if (fContValue > sContValue){
						outValue = 1;
					}
					else{
						outValue = 0;
					}
					break;
				case (Minus) :
					outValue = fContValue - sContValue;
					break;
				case (Multiplication) :
					outValue = fContValue * sContValue;
					break;
				case (One) :
					outValue = 1;
					break;
				case (Plus) :
					outValue = fContValue + sContValue;
					break;
				default:
					throw L"Not implemented";
				}
				i = nextI;
			}
		}
	}

	mainDataType ChallengeManager::GetEntityExternalInput(mainDataType inputId)
	{
		return _inputs[_currentLine][inputId];
	}

	mainDataType ChallengeManager::GetCorrectAnswer(mainDataType inputId)
	{
		return _correctAnswers[_currentLine][inputId];
	}

	void ChallengeManager::SelectGoodEnteties()
	{
		for (size_t i = 0; i < EntitiesStartPopulation; i++)
		{
			Entity& ent = _entityGenerator.GenerateEntity();
			for (int pr = 0; pr < EntityProcessCount; pr++) {
				ent.mProcessAll();
			}

			//const unsigned int totalTry = ChallangesCount * EntityProcessCount;
			//ent.CalculateEffectiveness(totalTry);
			ent.CalculateEffectiveness(EntityProcessCount);
			if (ent.GetEffectiveness() > 0) {
				_goodPopulation.push_back(&Entity(ent));
			}
		}
	}

	Entity* ChallengeManager::AchiveEffectivity(double targetEffectivity)
	{
		GenerateRandomInputs();
		FillAnswers();

		while (true)
		{
			SelectGoodEnteties();

			if (_goodPopulation.size() > 0)
			{
				Entity* targetEntity = CustomAlgs::SelectKth(_goodPopulation, _goodPopulation.size());
				if (targetEntity->GetEffectiveness() >= targetEffectivity) return targetEntity;

				//std::vector<Entity*> vinners = CustomAlgs::SelectTopNs(_goodPopulation, 1);
				/*if (vinners.size() > 0)
				{*/
				//if (vinners[0]->GetEffectiveness() >= targetEffectivity) return vinners[0];
				//_population.push_back(vinners[0]);
				/*}*/
			}

			//Here we need to impliment testing with different _currentLine (=different inputs-correct answers)
			//now i don't clear _goodPopulation but in future i need to impliment
		}
	}

	ChallengeManager* ChallengeManager::GetChallangeManager()
	{
		return _chManager;
	}
}

