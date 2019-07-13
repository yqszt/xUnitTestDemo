
#include "MainWindowPropertySink.h"

#include "../MainWindow.h"

MainWindowPropertySink::MainWindowPropertySink(MainWindow* pW) throw() : m_pW(pW)
{
}

void MainWindowPropertySink::OnPropertyChanged(const std::string& str)
{
	if (str == "heat_Result") {
		m_pW->view->update();
	}

}
