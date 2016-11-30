#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include "point.hpp"
#include "pavage.hpp"
#include "graphicutil.hpp"
#include "fileutil.hpp"

void constructAndDrawPavage(const char* filepath);
void constructPavageFromFile(unsigned int dim, const char* filepath);
void constructPavageWithEnvelop(unsigned int dim);
void constructEmptyPavage(unsigned int dim);
unsigned int getDim();
std::string getFilePath();
void checkDim(unsigned int dim);
void displayMenu();
void getBackToMenu();
void displayPossibilities();
void getBackToMenuPossibilies();
void doChoice(unsigned int choice);

int main() {
	displayMenu();
	return 0;
}

void displayMenu(){
	
	std::cout <<std::endl;
	std::cout << "**********************************************************************************************" << std::endl;
	std::cout << "*****                                                                                    *****" << std::endl;
	std::cout << "***    Simplexus - Création de pavage de dimension générique (inférieure ou égale à 15)    ***" << std::endl;
	std::cout << "*****                                                                                    *****" << std::endl;
	std::cout << "**********************************************************************************************" << std::endl;
	std::cout << std::endl;
	std::cout << "          - > Taper 1. Créer un pavage vide." << std::endl;
	std::cout << "          - > Taper 2. Créer un pavage avec une enveloppe de base." << std::endl;
	std::cout << "          - > Taper 3. Créer un pavage a partir d'un fichier de points." << std::endl;
	std::cout << "          - > Taper 4. Quitter." << std::endl;
	std::cout << std::endl;
	std::cout << "**********************************************************************************************" << std::endl;
	std::cout << std::endl;

	unsigned int choice = 0;
	std::cin.clear();
	std::cin >> choice;

	if (choice < 1 || choice > 5){
		system("clear");
		std::cout <<std::endl;
		std::cout << "Veuillez taper un entier compris entre 1 et 5" << std::endl;
		std::cout <<std::endl;
		std::cout <<std::endl;
		displayMenu();
	}
	else{
		unsigned int dim = 0;
		std::string filePath;
		switch(choice){
			case 1:
				dim = getDim();
				checkDim(dim);
				constructEmptyPavage(dim);
				getBackToMenu();
				break;
			case 2:
				dim = getDim();
				checkDim(dim);
				constructPavageWithEnvelop(dim);
				getBackToMenu();
				break;
			case 3:
				dim = getDim();
				checkDim(dim);
				filePath = getFilePath();
				if (dim ==2){
					char answer = 'a';
					std::cout << "Dessiner le pavage (y/n)? ";
					std::cin.clear();
					std::cin >> answer;
					if (answer=='y'){
						constructAndDrawPavage(filePath.c_str());
						getBackToMenu();
					}
					else {
						constructPavageFromFile(dim, filePath.c_str());
					}
				}
				else {
					constructPavageFromFile(dim, filePath.c_str());
					getBackToMenu();
				}
				break;
			case 4:
				std::cout << std::endl << "CIAO.." << std::endl;
				break;
			default:
				break;
		}
	}
}

unsigned int getDim(){
	unsigned int dim = 0;
	std::cin.clear();
	std::cout << std::endl;
	std::cout << "Taper la dimension du pavage : ";
	std::cin >> dim;
	std::cout << std::endl;

	return dim;
}

std::string getFilePath(){
	std::string filePath;
	std::cin.clear();
	std::cout << "Taper le chemin du fichier : ";
	std::cin >> filePath;
	std::cout << std::endl;
	return filePath;
}

void getBackToMenu(){
	char quit = 'a';
	std::cin.clear();
	std::cout << std::endl << "Taper q pour revenir au menu" << std::endl;
	std::cin>>quit;
	while (quit != 'q'){
		std::cin.clear();
		std::cin>>quit;
	} 
	system("clear");
	displayMenu();
}

void getBackToMenuPossibilies(){
	/* char quit = 'a';
	std::cin.clear();
	std::cout << std::endl << "Taper q pour revenir au menu" << std::endl;
	std::cin>>quit;
	while (quit != 'q'){
		std::cin.clear();
		std::cin>>quit;
	} */
	system("clear");
	displayPossibilities();
}

void checkDim(unsigned int dim){
	if (dim <= 1){
		std::cerr << std::endl << "La dimension ne peut pas être inférieure à deux" << std::endl << std::endl ;
		abort();
	}
	if (dim > 15){
		std::cerr << std::endl << "La dimension ne peut pas être supérieure à 15" << std::endl << std::endl ;
		abort();
	}
}

template<int X>
void doChoice(unsigned int choice, Pavage<X>& p){
		switch(choice){
			case 1: {
				Point<X> ptToAdd;
				for (int i=0; i<X; i++){
						std::cout << std::endl << "Taper la coordonnée " << i << " du point : ";
						double val;
						std::cin.clear();
						std::cin >> val;
						ptToAdd.setCoord(i,val);
						std::cout << std::endl;
				}
				double val;
				std::cout << std::endl << "Taper la valeur associée au point : ";
				std::cin.clear();
				std::cin >> val;
				p.addPoint(ptToAdd, val);
				std::cout << std::endl;
				//getBackToMenuPossibilies();
				break; }
			case 2: {
				Point<X> ptToInterpol;
				for (int i=0; i<X; i++){
						std::cout << std::endl << "Taper la coordonnée " << i << " du point : ";
						double val;
						std::cin.clear();
						std::cin >> val;
						ptToInterpol.setCoord(i,val);
						std::cout << std::endl;
				}
				std::cout << "La valeur d'interpolation du point " << ptToInterpol << "est : " << p.interpolation(ptToInterpol) << std::endl;  
				// getBackToMenuPossibilies();
				break; }
			case 3: {
				std::cout << p <<std::endl; 
				// getBackToMenuPossibilies();
				break; }
			case 4: {
				system("clear");
				displayMenu();
				break; }
			default:
				break;
		}
}

#define CASE_DIM(X) case X :{ \
	Pavage<X> p(true); \
	loadFromFile(p, file, filter); \
	std::cout << p <<std::endl; \
	unsigned int choice = 0; \
	while(choice != 4) { \
		displayPossibilities(); \
		std::cin.clear(); \
		std::cin >> choice; \
		doChoice<X>(choice, p); }\
	break;}

void displayPossibilities(){
	std::cout << "**********************************************************************************************" << std::endl;
	std::cout << std::endl;
	std::cout << "          - > Taper 1. Ajouter un point." << std::endl;
	std::cout << "          - > Taper 2. Interpoler un point." << std::endl;
	std::cout << "          - > Taper 3. Afficher le pavage." << std::endl;
	std::cout << "          - > Taper 4. Retour au menu principal." << std::endl;
	std::cout << std::endl;
	std::cout << "**********************************************************************************************" << std::endl;


}

#define CASE_DIM2(X) case X :{ Pavage<X> p; std::cout << p <<std::endl; break; }
#define CASE_DIM3(X) case X :{ Pavage<X> p(true); std::cout << p <<std::endl; break; }

void constructPavageFromFile(unsigned int dim, const char* filepath){
	const char* file = filepath;
	bool filter = false;
	
	std::cout << "*******************************************************"<< std::endl;
	std::cout << "***** Création pavage de dimension " << dim << "*****"  << std::endl;
	std::cout << "*******************************************************"<< std::endl;
	
	//UGLY
	switch(dim){
		CASE_DIM(2)
		CASE_DIM(3)
		CASE_DIM(4)
		CASE_DIM(5)
		CASE_DIM(6)
		CASE_DIM(7)
		CASE_DIM(8)
		CASE_DIM(9)
		CASE_DIM(10)
		CASE_DIM(11)
		CASE_DIM(12)
		CASE_DIM(13)
		CASE_DIM(14)
		CASE_DIM(15)
		default :
			 break;
	}
}

void constructEmptyPavage(unsigned int dim){
	//UGLY
	switch(dim){
		CASE_DIM2(2)
		CASE_DIM2(3)
		CASE_DIM2(4)
		CASE_DIM2(5)
		CASE_DIM2(6)
		CASE_DIM2(7)
		CASE_DIM2(8)
		CASE_DIM2(9)
		CASE_DIM2(10)
		CASE_DIM2(11)
		CASE_DIM2(12)
		CASE_DIM2(13)
		CASE_DIM2(14)
		CASE_DIM2(15)
		default :
			 break;
	}
}
void constructPavageWithEnvelop(unsigned int dim){
	switch(dim){
		CASE_DIM3(2)
		CASE_DIM3(3)
		CASE_DIM3(4)
		CASE_DIM3(5)
		CASE_DIM3(6)
		CASE_DIM3(7)
		CASE_DIM3(8)
		CASE_DIM3(9)
		CASE_DIM3(10)
		CASE_DIM3(11)
		CASE_DIM3(12)
		CASE_DIM3(13)
		CASE_DIM3(14)
		CASE_DIM3(15)
		default :
			 break;
	}
}

void constructAndDrawPavage(const char* filepath){
	std::cout << "***************************************************************"<< std::endl;
	std::cout << "***** Création pavage de dimension 2 avec affichage       *****" << std::endl;
	std::cout << "***************************************************************"<< std::endl;
	Pavage<2> p(false);
	loadFromFile(p, filepath, true);
	std::cout<<p<<std::endl;
	drawPavage(p);
}
