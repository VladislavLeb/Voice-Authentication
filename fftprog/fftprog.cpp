// fftprog.cpp: ������� ���� �������.

#include "stdafx.h"
#include "Form1.h"
#include <math.h>
#include "bass.h"

using namespace fftprog;




[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	return 0;
}
