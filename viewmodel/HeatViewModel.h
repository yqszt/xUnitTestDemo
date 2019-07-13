 #pragma once
#include "etlbase.h"
#include "../model/HeatDataModel.h"
#include "./sinks/HeatViewModelSink.h"
#include "./commands/CalcCommand.h"

class HeatViewModel : public Proxy_PropertyNotification<HeatViewModel>,
	public Proxy_CommandNotification<HeatViewModel>
{
public:
	HeatViewModel();

	void SetModel(const std::shared_ptr<HeatDataModel>& model);

	std::shared_ptr<workboard> getResult() throw();

	std::shared_ptr<ICommandBase> getCalcCommand();

	bool Calculate(const workboardPass& para);

private:
	std::shared_ptr<HeatDataModel> m_HeatModel;

	std::shared_ptr<CalcCommand> m_cmdCalc;

	std::shared_ptr<HeatViewModelSink> m_sink;

};