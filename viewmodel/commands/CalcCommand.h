#pragma once

#include "etlbase.h"

#include "../../common/workboard.h"

class HeatViewModel;

class CalcCommand : public ICommandBase
{
public:
	CalcCommand(HeatViewModel *p) throw();

	virtual void SetParameter(const std::any& param);
	virtual void Exec();

private:
	HeatViewModel* m_pVM;

	workboardPass m_param;
};