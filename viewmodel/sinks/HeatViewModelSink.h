#pragma once

#include "etlbase.h"

class HeatViewModel;

class HeatViewModelSink : public IPropertyNotification
{
public:
	HeatViewModelSink(HeatViewModel* p) throw();

	virtual void OnPropertyChanged(const std::string& str);

private:
	HeatViewModel * m_pVM;
};