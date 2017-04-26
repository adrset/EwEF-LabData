#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include "Misc.h"
#include "labData.h"

std::string labData::directory = "";

labData::labData(int width, int height, std::string dir)
{
	struct stat info;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
	std::string str(buffer);

	if (stat(dir.c_str(), &info) != 0)
	{
		directory = dir + "/";
		dir = "mkdir " + dir;
		system(dir.c_str());
	}
	if (stat((dir + "/" + buffer).c_str(), &info) != 0)
	{
		dir = "mkdir " + dir + "\\" + str; // for windows only
		system(dir.c_str());
	}


}


labData::~labData()
{
}

void labData::menu()
{
	std::vector<std::string> temp;
	std::cout << "EwEF LabData 0.2" << std::endl;
	std::cout << "Autor: Adrian Setniewski" << std::endl;
	bool go = true;
	char decyzja;
	std::string tmp;
	while (go) {
		std::cout << std::endl << " Co chcesz zrobic? " << std::endl;
		std::cout << " 1) wczytac plik BOD" << std::endl;
		std::cout << " 2) wczytac plik SCP" << std::endl;
		std::cout << " 3) wypisac na ekran i-ty plik SCP/BOD" << std::endl;
		std::cout << " 4) wczytac plik ELVIS dla czasu" << std::endl;
		std::cout << " 5) wczytac plik ELVIS dla czestotliwosci" << std::endl;
		std::cout << " 6) Zapisac wszystkei pliki" << std::endl;
		std::cout << " 8) wyjsc" << std::endl;
		std::string tmp;
		std::getline(std::cin, tmp);

		decyzja = tmp[0];

		switch (decyzja)
		{
		case '1':
			system("@cls||clear");
			std::cout << "Podaj sciezke pliku: " << std::endl;
			std::cin >> tmp;
			m_bods.emplace_back();
			if (m_bods.back().readBodFile(tmp)) {
				std::cout << "Plik wpisany" << std::endl;
			}
			else {
				m_bods.pop_back();
			}
			break;
		case '2':
			system("@cls||clear");
			std::cout << "Podaj sciezke pliku: " << std::endl;
			std::cin >> tmp;
			m_scps.emplace_back();
			if (m_scps.back().readScpFile(tmp)) {
				std::cout << "Plik wpisany" << std::endl;
			}
			else {
				m_scps.pop_back();
			}
			break;
		case '3':
			system("@cls||clear");
			if (m_bods.size() == 0 && m_scps.size() == 0 && m_elvisF.size() == 0 && m_elvisT.size() == 0) {
				std::cout << "Nie wczytano zadnych danych!!!" << std::endl;
			}
			else {
				std::cout << "Aktualnie wpisano prawidlowo " << std::endl;
				std::cout << m_bods.size() << " plikow BOD" << std::endl;
				std::cout << m_scps.size() << " plikow SCP" << std::endl;
				std::cout << m_elvisT.size() << " plikow ELVISt" << std::endl;
				std::cout << m_elvisF.size() << " plikow ELVISf" << std::endl;
				std::cout << "Co wypisac? Wpisz BOD(i), SCP(i) PRF(i), PRT(i)";
				std::cout << " gdzie i to numer obiektu numerowany od 1 do n" << std::endl;

				std::string tmp;
				std::cin >> tmp;
				if (tmp.find("BOD(") != std::string::npos && tmp.find(")") != std::string::npos) {
					if ((unsigned int)std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) <= m_bods.size() && m_bods.size() != 0) {//I am aware of this cast!
						m_bods[std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) - 1].printHeader();
					}
					else {
						std::cout << "Nie ma takiego numeru!" << std::endl;
					}
				}
				else if (tmp.find("SCP(") != std::string::npos && tmp.find(")") != std::string::npos) {
					if ((unsigned int)std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) <= m_scps.size() && m_scps.size() != 0) {
						m_scps[std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) - 1].printHeader();
					}
					else {
						std::cout << "Nie ma takiego numeru!" << std::endl;
					}
				}
				else if (tmp.find("PRT(") != std::string::npos && tmp.find(")") != std::string::npos) {
					if ((unsigned int)std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) <= m_elvisT.size() && m_elvisT.size() != 0) {
						m_elvisT[std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) - 1].printAll();
					}
					else {
						std::cout << "Nie ma takiego numeru!" << std::endl;
					}
				}
				else if (tmp.find("PRF(") != std::string::npos && tmp.find(")") != std::string::npos) {
					if ((unsigned int)std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) <= m_elvisF.size() && m_elvisF.size() != 0) {
						m_elvisF[std::strtol(&tmp[tmp.find('(') + 1], nullptr, 10) - 1].printAll();
					}
					else {
						std::cout << "Nie ma takiego numeru!" << std::endl;
					}
				}



				else {
					std::cout << "Wpisano nieprawidlowe zadanie!" << std::endl;
				}
			}
			break;
		case '4':
			system("@cls||clear");
			std::cout << "Podaj sciezke pliku: " << std::endl;
			std::cin >> tmp;
			m_elvisT.emplace_back();
			if (m_elvisT.back().readElvisFile(tmp)) {
				std::cout << "Plik wpisany" << std::endl;
			}
			else {
				m_elvisT.pop_back();
			}
			break;
		case '5':
			system("@cls||clear");
			std::cout << "Podaj sciezke pliku: " << std::endl;
			std::cin >> tmp;
			m_elvisF.emplace_back();
			if (m_elvisF.back().readElvisFile(tmp)) {
				std::cout << "Plik wpisany" << std::endl;
			}
			else {
				m_elvisF.pop_back();
			}
			break;
		case '6':
			system("@cls||clear");
			
			for (auto &it : m_scps) {
				it.saveFile();
			}
			for (auto &it : m_bods) {
				it.saveFile();
			}
			for (auto &it : m_elvisF) {
				it.saveFile();
			}
			for (auto &it : m_elvisT) {
				it.saveFile();
			}

			std::cout << "Zapisano. " << std::endl;
			break;
		default:
			go = false;
			break;
		}
		if (go != false) {
			std::cin.ignore();
			std::cin.clear();
		}

	}

}
