#include "MainForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void Main(){
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault;
	OpenCV_Ball_Detector::MainForm form;
	Application::Run(%form);
}

