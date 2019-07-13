#include "CalcCommand.h"

#include "../HeatViewModel.h"

CalcCommand::CalcCommand(HeatViewModel* p) throw() : m_pVM(p)
{

}

void CalcCommand::SetParameter(const std::any& param)
{
	m_param = std::any_cast<workboardPass>(param);
}

void CalcCommand::Exec()
{
	bool bresult = m_pVM->Calculate(m_param);
	m_pVM->Fire_OnCommandComplete("heat_Result", bresult);
}