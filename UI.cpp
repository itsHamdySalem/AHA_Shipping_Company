#include "UI.h"


UI::UI()
{
}

void UI::setMode ()
{
	int m;
	cout << "Select a mode from the following:\n1-Interactive\t2-Step-by-Step\t3-Silent\n";
	cout << "Enter mode number: ";
	cin >> m;
	switch (m)
	{
	case 1:
		mode = interactive;
		break;
	case 2:
		mode = step_by_step;
		break;
	case 3:
		mode = silent;
		break;
	default:
		cout << "Unvalid mode...\nYou should enter a mode number of {1, 2, 3}...!\n\n";
		break;
	}
}

void UI::ApplyMode ()
{
	LoadInputFile();
	switch (mode)
	{
	case interactive:
		cout << "Interactive Mode\n";
		ApplyInteractive();
		break;
	case step_by_step:
		cout << "Step-by-Step Mode\n";
		ApplyStepByStep();
		break;
	case silent:
		cout << "Silent Mode\n";
		ApplySilent();
		break;
	default:
		break;
	}
}
void UI::ApplyInteractive ()
{
	// apply
	// _sleep(1000);
	generateOutputFile();
}
void UI::ApplyStepByStep ()
{
	// apply
	generateOutputFile();
}
void UI::ApplySilent ()
{
	cout << "Simulation starts...\n";
	generateOutputFile();
	cout << "Simulation ends, Output file created...\n";
}

void UI::LoadInputFile ()
{
	string FileName;
	cout << "Enter The File Name: ";
	cin >> FileName;
	cout << "Reading File...\n\n";

	ifstream InFile;
	InFile.open(FileName+".txt");
	if (!InFile.is_open())
	{
		cout << FileName << " not fount!\n";
		return;
	}

	int N, S, V;
	InFile >> N >> S >> V;
	// do something...

	int NS, SS, VS;
	InFile >> NS >> SS >> VS;
	// do something...

	int NTC, STC, VTC;
	InFile >> NTC >> STC >> VTC;
	// do something...

	int J, CN, CS, CV;
	InFile >> J >> CN >> CS >> CV;
	// do something...

	int AutoP, MaxW;
	InFile >> AutoP >> MaxW;
	// do something...

	int E;
	InFile >> E;
	// do something...

	char Etype;
	char TYP;
	string ET;
	int ID, DIST, LT, Cost, ExtraMoney;

	for (int i = 0; i < E; i++)
	{
		InFile >> Etype;
		switch (Etype)
		{
		case 'R':
			InFile >> TYP >> ET >> ID >> DIST >> LT >> Cost;
			// do something...

			break;
		case 'X':
			InFile >> ET >> ID;
			// do something...

			break;
		case 'P':
			InFile >> ET >> ID >> ExtraMoney;
			// do something...

			break;

		default:
			break;
		}
	}

	InFile.close();
	cout << "File has been loaded successfully!\n";

}
void UI::generateOutputFile ()
{
}

UI::~UI()
{
}
