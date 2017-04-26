// EwEF.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include <iostream>
#include "labData.h"
#include "BOD.h"
#include "SCP.h"
using namespace std;

int main(int argc, char** argv)
{
	labData data(1024, 768, "dane_obrobione");
	data.menu();
    return 0;
}

