#include "MyForm.h"

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(cli::array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Project2::MyForm form;
	Application::Run(% form);
}

