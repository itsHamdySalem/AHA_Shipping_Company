#pragma once
#ifndef UI_H
#define UI_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum MODE
{
	interactive,
	step_by_step,
	silent
};

class UI
{
private:
	MODE mode;
public:
	UI();

	void setMode ();
	void ApplyMode ();
	void ApplyInteractive ();
	void ApplyStepByStep ();
	void ApplySilent ();

	void LoadInputFile ();
	void generateOutputFile ();

	~UI();
};

#endif

