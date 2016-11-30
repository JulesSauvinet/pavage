#ifndef _FILEUTIL_H
#define _FILEUTIL_H

/*!
 * \file fileutil.hpp
 * \brief Createur de pavage à partir d'une liste de points d'un fichier
 * \author Olivier Hoarau & Jules Sauvinet
 * \version 0.1
 */

#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>

/*!
 *  \brief Initialise un pavage avec une séquence de points contenu dans un fichier
 *
 *  Ajoute au pavage pavage les points contenus dans le fichier file
 *
 *  \param pavage : le pavage auquel il faut ajouter les points contenu dans le fichier
 *  \param file : les points qu'il faut ajouter au pavage pavage
 *  \param filter : indique s'il faut filter les données pour avoir des points aux coordonnées bornées de manière a pouvoir les afficher
 */
template<std::size_t N>
void loadFromFile(Pavage<N>& pavage, const char* file, bool filter) {

	std::ifstream infile(file);
	if (infile.fail()) {
		std::cerr << "Impossible d'ouvrir le fichier : " << file << std::endl;
		abort();
	}
	std::string line;

	//On lit la dimension et le nombre de points
	std::getline(infile, line);
	std::istringstream is(line);
	int dim, nb;
	is >> dim;
	std::getline(infile, line);
	std::istringstream is2(line);
	is2 >> nb;
	//std::cout << "Lu : dim=" << dim << " nb=" << nb << std::endl;
	
	//Si la dimension est différente de celle du pavage, il ne sera pas possible 
	//d'ajouter les points
	if (dim != N)
	{
		std::cerr << "Pas la bonne dimension" << std::endl;
		abort();
	}
	//Sinon, on ajoute les points, a chaque ligne etant associee un point
	while (std::getline(infile, line))
	{
		Point<N> point;
		//On lit chaque ligne du fichier qui correspond à la description d'un point
		std::istringstream iss(line);
		double val;

		int i = 0;
		while(iss >> val || !iss.eof()) {
			if(iss.fail()) {
				iss.clear();
				std::string dummy;
				iss >> dummy;
				std::cout << "biip.";
				continue;
			}
			if (i!=N){
				point.setCoord(i, val);
			}
			i++;
		}
		//Si les valeurs du points sont trop grandes, on ne l'ajoute pas au pavage
		//dans le cas ou l'on veut filtrer (pour un futur affichage graphique en 2D)
		if(filter){
			if (!point.outOfBoundries()){
				pavage.addPoint(point, val);
			}
		}
	
		else {
			//On ajoute un point
			pavage.addPoint(point, val);
		}
	}
}
#endif
