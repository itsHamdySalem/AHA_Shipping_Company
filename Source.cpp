#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void LoadFile (string FileName);

int main ()
{
	cout << '\n' << "========================= AHA Shipping Company =========================" << '\n';
	cout << "Load File Testing...\nFile Name: ";
	string FileName;
	cin >> FileName;
	LoadFile(FileName);
	system("pause");
	return 0;
}

void LoadFile (string FileName)
{
	ifstream InFile;
	InFile.open(FileName+".txt");
	if (!InFile.is_open())
	{
		cout << FileName << " not fount!\n";
		return;
	}
	
	int N, S, V;
	InFile >> N >> S >> V;
	cout << N << '\t' << S << '\t' << V << '\n';

	int NS, SS, VS;
	InFile >> NS >> SS >> VS;
	cout << NS << '\t' << SS << '\t' << VS << '\n';

	int NTC, STC, VTC;
	InFile >> NTC >> STC >> VTC;
	cout << NTC << '\t' << STC << '\t' << VTC << '\n';

	int J, CN, CS, CV;
	InFile >> J >> CN >> CS >> CV;
	cout << J << '\t' << CN << '\t' << CS << '\t' << CV << '\n';

	int AutoP, MaxW;
	InFile >> AutoP >> MaxW;
	cout << AutoP << '\t' << MaxW << '\n';

	int E;
	InFile >> E;
	cout << E << '\n';

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
			cout << 'R' << '\t' << TYP << '\t' << ET << '\t' << ID << '\t' << DIST << '\t' << LT << '\t' << Cost << '\n';

			break;
		case 'X':
			InFile >> ET >> ID;
			cout << 'X' << '\t' << ET << '\t' << ID << '\n';

			break;
		case 'P':
			InFile >> ET >> ID >> ExtraMoney;
			cout << 'P' << '\t' << ET << '\t' << ID << '\t' << ExtraMoney << '\n';

			break;
		}
	}
	cout << '\n';

	InFile.close();
}

