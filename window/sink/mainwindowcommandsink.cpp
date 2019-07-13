#include "mainwindowcommandsink.h"

MainWindowCommandSink::MainWindowCommandSink(MainWindow* pW)throw():m_pW(pW)
{
}

void MainWindowCommandSink::OnCommandComplete(const std::string& str, bool bOK) {

}
