#ifndef _PAVAGE_H
#define _PAVAGE_H

/*!
 * \file pavage.hpp
 * \brief Construction d'un pavage, gestion d'ajout de point et interpolation d'un point du pavage
 * \author Olivier Hoarau & Jules Sauvinet
 * \version 0.1
 */

#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstdarg>
#include <cmath>
#include <set>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include "point.hpp"
#include "mathutil.hpp"

/*!< Template N : la dimension de l'espace */
template<std::size_t N>
/*! \class Pavage
 * \brief classe representant un pavage consitué de trisimplexe dans un espace de dimension N
 *
 *  La classe gère des opérations sur un pavage, l'ajout de point de figure et l'interpolation de points
 */
class Pavage
{
	private:
		std::set<std::vector<Point<N>*>> figures; /*!< Liste des figures constituant le pavage */
		std::list<std::pair<Point<N>, double>> points; /*!< Liste des points appartenant au pavage */
		int toUpdate = 0;
	public:
		/*!
		 *  \brief Constructeur vide d'un pavage
		 *
		 *  Constructeur vide de la classe pavage
		 *
		 */
		Pavage() {};

		/*!
		 *  \brief Constructeur d'un pavage avec une enveloppe de base
		 *
		 *  Constructeur de la classe Pavage, qui construit un pavage avec au départ 2^n points pour construire
		 *	l'enveloppe de départ avec ou non des valeurs bornées pour permettre un affichage
		 *  Les valeurs des coordonnées des points
		 *	sont toutes nulles sauf une dont la valeur est soit égale à une valeur extreme minimale ou maximale
 	 	 *
		 *  \param notToDisplay permet de ne pas borner les valeurs et de na pas permettrre
		 *  une optimisation dans le cas ou le pavage sera affichée et l'espace est employé de manière à avoir
 		 *  un meilleur visuel, le booleen a true n'a de reel sens qu'en dimension 2, et l'optimisation n'est faite qu'en dimension 2.
 		 *
 		 *  \return le pavage construit
 		 */
		Pavage(bool notToDisplay);

		/*!
		 *  \brief Constructeur par initialisation
		 *
		 *  Constructeur de la classe Point prenant une liste de points-valeurs
		 *
		 *  \param _points une liste de pair (point, valeur)
		 */
		Pavage(std::list<std::pair<Point<N>, double>>& _points);

		/*!
		 *  \brief Test d'appartenance d'un point à une figure
		 *
		 *  Teste si un point appartient appartient à une figure
		 *
		 *  \param figure : un vecteur de point consituant une figure
		 *  \param pt : un point donné
		 *  \return true si le point est à l'intérieur strictement de la figure, false sinon
		 */
		bool isPointInFigure(const std::vector<Point<N>*>& figure, const Point<N>& pt) const;

		/*!
		 *  \brief Ajout d'un point au pavage
		 *
		 *  Ajoute un point au pavage si celui-ci est à l'intérieur d'une figure du pavage existant (de lespace prédéfini)
		 *
		 *  \param pt : le point à ajouter
		 *  \param val : la valeur à associer au point à ajouter
		 */
		void addPoint(Point<N>& pt, double val);

		/*!
		 *  \brief Getter des figures du pavage
		 *
		 *  Getter de la liste des figures constituant le pavage
		 *
		 *  \return une référence de la liste des figures du pavage
		 */
		std::set<std::vector<Point<N>*>>& getFigures();

		/*!
		 *  \brief Getter des couples (point, valeur) du pavage
		 *
		 *  Getter de la liste des couples (point,valeur) attribut du pavage
		 *
		 *  \return une référence de la liste des couples (point,valeur) attribut du pavage
		 */
		std::list<std::pair<Point<N>, double>>& getPoints();

		/*!
		 *  \brief Calcul du volume d'une figure
		 *
		 *  Calcul le volume d'une figure en faisant appel au déterminant
		 *
		 *  \param figure : un vecteur de pointeurs de point constituant un simplexe
		 *  \return le volume réel de la figure passée en paramètre
		 */
		double volume(const std::vector<Point<N>*>& figure) const;

		/*!
		 *  \brief Calcul de la valeur d'interpolation d'un point
		 *
		 *  Calcule la valeur d'interpolation d'un point appartenant au pavage à partir des valeurs
		 *  des points constituant le simplexe auquel le point appartient
		 *
		 *  \param point : un point donné
		 *  \return la valeur réelle d'interpolation du point passé en paramètre
		 */
		double interpolation(const Point<N>& point) const;

		/*!
		 *  \brief Test d'appartenance d'un point a une liste de pointeurs sur point
		 *
		 *  Teste si un point apparient à un liste de pointeurs sur point
		 *
		 *  \param _points : une liste de points
		 *  \param _point : un point donnée
		 *  \return true si le point appartient au vecteur, false sinon
		 */
		bool contain(std::list<Point<N>*> _points, const Point<N>& _point) const;

		/*!
		 *  \brief Getter des points du pavage
		 *
		 *  Getter des points consituant le pavage à partir de la liste points-valeurs attribut du pavage
		 *
		 *  \return retourne une liste de pointeurs de points extrait de la liste de points-valeurs du pavage
		 */
		std::list<Point<N>*> getSinglePoints() const;

		/*!
		 *  \brief Teste si le pavage est vide
		 *
		 *  Teste s'il n'y a aucune figure de créée dans le pavage
		 *
		 *  \return true s'il n'y a aucune figure dans le pavage, false sinon
		 */
		bool empty() const;
		
		/*!
		 *  \brief Affectation de valeurs aux bornes du pavage
		 *
		 *  Affecte une valeur aux points bornes du pavage correspondant à une moyenne pondérée des
		 *  valeurs de tous les autres points du pavage hors points bornes en fonction de la distance
		 *
		 */
		void affectValToBoundries();
		
		/*!
		 *  \brief Récupềre les bornes du pavage
		 *
		 *  Récupère les points borne du pavage dans une liste
		 *
		 *  \return la liste des points de l'enveloppe du pavage
		 */
		std::list<std::pair<Point<N>, double>*> getBoundries();

		/*!
		 *  \brief Affichage du pavage
		 *
		 *  Affichage de la dimension du pavage, du nombre de points, du nombre de figures puis
		 * de la liste des figures du pavage sous la forme figure i : affichage des points séparé par un espace
		 *
		 */
		template<std::size_t P>
		friend std::ostream& operator<<(std::ostream& os, const Pavage<P>& pavage);
};


template<std::size_t N>
Pavage<N>::Pavage(bool notToDisplay /* =true */)
{	
	/*
	 *  On va créer un pavage composé d'une enveloppe
	 *  Les points de l'enveloppe seront NOTAMMENT de la forme :
	 *  P1 :    (x1_min, 0 , 0 ..., 0)
	 *  P2 :    (x1_max, 0 , 0 ..., 0)
	 *  P2i :   (0, ...,  xi_min, ..., 0)
	 *  P2i+1 : (0, ...,  xi_max, ..., 0)
	 *  ...
	 * avec x1_min = x2_min = ... = xi_min = xn_min = VAL_MIN
	 * et   x1_max = x2_max = ... = xi_max = xn_max = VAL_MAX
	 * */


	double valmin = 0.;
	double valmax = 0.;

	// Convention : Si on ne doit pas etre amené a afficher le pavage :
	// VAL_MIN = -25000
	// VAL_MAX = 25000
	if (notToDisplay){
		valmin= -25000.0;
		valmax= 25000.0;
	}
	// Convention : Si on ne doit etre amené a afficher le pavage :
	// VAL_MIN = -300
	// VAL_MAX = 300
	else {
		valmin=-300.0;
		valmax=300.0;
	}

	//On créé les différents points de l'enveloppe
	Point<N> *pointXMin;
	Point<N> *pointXMax;

	points.push_back(std::make_pair(Point<N>({valmin}), 0.0));
	pointXMin = &(points.back().first);
	pointXMin->toBoundry();
	points.push_back(std::make_pair(Point<N>({valmax}), 0.0));
	pointXMax = &(points.back().first);
	pointXMax->toBoundry();

	std::vector<Point<N>*> figureCur;
	for (unsigned i=0; i<=N-1; i++){

		std::vector<double> v(N-1, valmin);

		for (unsigned j=0;j<i;j++){
			v.at(j)=valmax;
		}

		int coord_cpt = 0;
		do {
				coord_cpt++;
				figureCur.clear();

				figureCur.push_back(pointXMin);
				figureCur.push_back(pointXMax);
				for(unsigned k=0; k<v.size(); k++){
					Point<N> p{};
					p.toBoundry();

					for(unsigned l=0; l<N; l++){
							p.setCoord(l, 0.0);
					}

					p.setCoord(k+1, v.at(k));
					Point<N>* pointToInsert;

					bool insert = false;

					for (typename std::list<std::pair<Point<N>, double>>::iterator it1=points.begin(); it1 != points.end(); ++it1){
						if ((*it1).first==p){
							insert = true;
							pointToInsert = &((*it1).first);
							pointToInsert->toBoundry();
						}
					}

					if (insert){
							figureCur.push_back(pointToInsert);
					}
					else {
							points.push_back(std::make_pair(std::move(p), 0.0));
							figureCur.push_back(&(points.back().first));
					}
				}

				figures.insert(figureCur);
		//Pour créer les différents points, il faut faire des permutations sur un vecteur de points 
		} while (std::prev_permutation(v.begin(), v.end()));
	}

	/*
	 *  On effectue une rotation de pi/2 pour chaque point du pavage
	 *	pour un meilleur rendu visuel si on va afficher le pavage
	 * */
	if (!notToDisplay && N==2){
		for (std::pair<Point<N>, double>& paire : points){
			Point<N>& pt = paire.first;
			double x= pt.getCoord(0);
			double y= pt.getCoord(1);

			double theta = pi()/4.;
			double newX = std::round(std::sin(theta)*y + std::cos(theta)*x);
			double newY = std::round(std::cos(theta)*y - std::sin(theta)*x);

			pt.setCoord(0,newX);
			pt.setCoord(1,newY);
		}
	}
}

template<std::size_t N>
Pavage<N>::Pavage(std::list<std::pair<Point<N>, double>>& _points)
{
	if (_points.size() != N+1) {
		std::cerr << "Il faut donner " << N+1 << " points" << std::endl;
		abort();
	}
	points = _points;
	std::vector<Point<N>*> newFigure;

	for(auto& pair : _points){
		newFigure.push_back(&pair.first);
	}

	figures.insert(newFigure);
}

template<std::size_t N>
std::list<Point<N>*> Pavage<N>::getSinglePoints() const{
	std::list<Point<N>*> singlePoints;
	for (const std::pair<Point<N>, double>& pair : this->points){
		singlePoints.push_back(const_cast<Point<N>* >(&(pair.first)));
	}
	return singlePoints;
}

template<std::size_t N>
bool Pavage<N>::contain(std::list<Point<N>*> _points, const Point<N>& _point) const{
	for (Point<N>* point : _points){
		if (*point ==_point){
			return true;
		}
	}
	return false;
}

template<std::size_t N>
std::ostream& operator<<(std::ostream& os, const Pavage<N>& pavage){
	auto& figures = const_cast<Pavage<N>&>(pavage).getFigures();

	int cpt=1;
	os <<  const_cast<Pavage<N>&>(pavage).getPoints().size() <<" points, " << figures.size() << " figures." << std::endl;
	for (typename std::set<std::vector<Point<N>*>>::iterator it=figures.begin(); it != figures.end(); ++it){
		os << "Figure " << cpt << " : ";
		for(unsigned int i=0; i<N+1; i++){
			os << *(it->at(i)) << "  ";
		}
		os << std::endl;
		cpt++;
	}
    return os;
}

template<std::size_t N>
std::set<std::vector<Point<N>*>>& Pavage<N>::getFigures(){
	return this->figures;
}

template<std::size_t N>
std::list<std::pair<Point<N>, double>>& Pavage<N>::getPoints(){
	return this->points;
}

template<std::size_t N>
bool Pavage<N>::empty() const{
	if (this->figures.size() == 0){
		return true;
	}
	return false;
}

template<std::size_t N>
bool Pavage<N>::isPointInFigure(const std::vector<Point<N>*>& figure, const Point<N>& pt) const {
	//On va déterminer si un point P appartient a une figure F
	//représentée par un vecteur de points
	for(unsigned int i=0; i<figure.size(); i++){
		std::vector<std::vector<double>> det1;
		std::vector<std::vector<double>> det2;
		
		//Pour chaque point Pi de la figure F
		Point<N>* pointDuMemeCote = figure.at(i);
		
		//Pour ce faire, on calcule deux déterminants pour chaque point de la figure F
		for (unsigned int j=0 ; j < N; j++){
			std::vector<double> line1;
			std::vector<double> line2;
			for (unsigned int k=0; k< figure.size(); k++){
				if (k!=i){
					//Le premier est celui de la matrice composée des vecteurs
					//PPj pour chaque Pj appartenant à la figure F privé de Pi
					line1.push_back(pt.getCoord(j) - figure.at(k)->getCoord(j));
					
					//Le deuxieme est celui de la matrice composée des vecteurs
					//PiPj pour chaque Pj appartenant à la figure F privé de Pi
					line2.push_back(pointDuMemeCote->getCoord(j) - figure.at(k)->getCoord(j));
				}
			}
			det1.push_back(line1);
			det2.push_back(line2);
			line1.empty();
			line2.empty();
		}
		double determinant1 = determinant(det1);
		double determinant2 = determinant(det2);
		det1.empty();
		det2.empty();
		
		//Si la multiplication des deux déterminants est négative, le point n'appartient pas à la figure
		//Moralement, cela veut dire que le point est "du meme coté" que chaque point de la figure
		if (determinant1*determinant2<=0){
			return false;
		}
	}
	return true;
}

template<std::size_t N>
void Pavage<N>::addPoint(Point<N>& pt, double val) {
	
	//Pour ajouter un point au pavage qui contient au moins une figure
	if (this->points.size() >= N+1){
		
		//Si le point n'appartient pas déja au pavage
		if (!contain(this->getSinglePoints(), pt)){
			
			//On l'ajoute à la liste des points du pavage
			points.push_back(std::make_pair(std::move(pt), val));
			
			Point<N>& noCopyPt = points.back().first;
			std::set<std::vector<Point<N>*>> newFigures;
			
			//On recherche la figure F à laquelle appartient le point P
			//On créé à partir de la figure de N+1 points, 
			//N+1 nouvelles figures composées de N points parmi les N+1 points + le point P
			//Puis on supprime la figure F
			for (typename std::set<std::vector<Point<N>*>>::iterator it=figures.begin(); it != figures.end(); ++it){
				std::vector<Point<N>*> figureCur = *it;
				if (this->isPointInFigure(figureCur,noCopyPt) && newFigures.find(figureCur) == newFigures.end()){

					//On créé les nouvelles figures
					for (unsigned i=0; i <figureCur.size(); i++){
						//On créé la nouvelle figure
						std::vector<Point<N>*> newFigure;
						for (unsigned j=0; j < figureCur.size(); j++){
							Point<N>* copyPoint(figureCur.at(j));
							if (i!=j){
								newFigure.push_back(copyPoint);
							}
						}
						//On ajoute la nouvelle figure parmi la liste des nouvelles figures à ajouter au pavage
						newFigure.push_back(&(noCopyPt));
						newFigures.insert(newFigure);
					}
					//On supprime F
					this->figures.erase(it);

				}
			}
			
			//On insère les figures précédemment crées dans la liste des figures du pavage
			for (typename std::set<std::vector<Point<N>*>>::iterator it=newFigures.begin(); it != newFigures.end(); ++it){
				if (volume(*it) != 0){
					this->figures.insert(*it);
				}
			}
		}
		//Si le point appartient déja au pavage, on met juste à jour sa valeur
		else {
			for (std::pair<Point<N>, double>& pair : this->points){
				if (const_cast<Point<N>& >(pt) == pair.first){
					pair.second = val;
				}
			}
		}
	}
	//Si le pavage ne contient aucune figure mais qui lui manque un seul point pour en créer une
	//On ajoute le point à la liste des points du pavage et on créé la premiere figure du pavage
	else if (this->points.size() == N) {
		this->points.push_back(std::make_pair(std::move(pt), val));
		std::vector<Point<N>*> figure;

		for (std::pair<Point<N>, double>& paire : this->points) {
			Point<N>& pt = paire.first;
			figure.push_back(&pt);
		}
		this->figures.insert(figure);
	}
	//Si le pavage est à plus de 1 point d'avoir une premiere figure,
	//On ajoute juste le point a la liste des points du pavage
	else{
		this->points.push_back(std::make_pair(std::move(pt), val));
	}
	
	//Convention
	//On décide de mettre à jour la valeur des points de l'enveloppe du pavage après l'ajout de 5 points
	//Les points qui ont permis au départ de créer le pavage n'avait pas de valeur affectée par l'utilisateur
	//On conviendra ainsi que leur valeur sera la moyenne pondéré des valeurs des autres points 
	//du pavage en fonction de la distance
	this->toUpdate++;
	if(this->toUpdate > 5){
		this->toUpdate =0;
		this->affectValToBoundries();
	}

}

template<std::size_t N>
double Pavage<N>::volume(const std::vector<Point<N>*>& figure) const{
	//On va construire une matrice de coordonnées qui nous permettre de calculer le déterminant récursivement en s'affranchissant des templates
	std::vector<std::vector<double>> det;
	//Si la figure ne possède aucun points, il n'est pas possible de calculer le volume 
	if (figure.size() ==0){
		std::cerr << "Volume impossible a calculer" << std::endl;
		abort();
	}
	//Si la figure possède un seul point ou deux points, on conviendra que le volume est nul
	if (figure.size() ==1){
		return 0.0;
	}
	if (figure.size() ==2){
		return 0.0;
	}
	//Cas où la dimension est égale à 2 on a pour un triangle ABC,
	//avec A(xA,yA), B(xB,yB), C(xC,yC): 
	//			|xA	 xB  xC|
	// volume = |yA	 yB  yC| / factorielle(N)
	// 			|1	 1   1 |
	// avec |...| qui représente l'opération du déterminant
	if (figure.size()==3){
		std::vector<double> curColumn;
		for(unsigned int i=0; i<figure.size(); i++){
			curColumn.clear();
			for(unsigned j=0; j<N; j++){
				curColumn.push_back(figure.at(i)->getCoord(j));
			}
			curColumn.push_back(1);
			det.push_back(curColumn);
		}
	}
	//Cas où la dimension est supérieure à 2 et égale à N on a pour un N-Simplexe,
	//avec P1(x1,1;x1,2;...;x1,n), P2(x2,1;x2,2;...;x2,n), ..., Pn+1(xn+1,1;xn+1,2;...;xn+1,n): 
	//
	//			|x2,2 - x1,1	 ...   xn+1,1 - x1,1|
	//  		|x2,2 - x1,2	 ...   xn+1,2 - x1,2|   
	// volume = |...  	         ...	     ...    |  / factorielle(N)
	// 			|...	         ...	     ...    |
	//			|x2,n - x1,n  ...      xn+1,n - x1,n|
	//
	// avec |...| qui représente l'opération du déterminant
	else{
		Point<N>* firstPoint = figure.at(0);
		for(unsigned int i=1; i<figure.size(); i++){
			std::vector<double> curColumn;
			for(unsigned j=0; j<N; j++){
				curColumn.push_back(figure.at(i)->getCoord(j)-firstPoint->getCoord(j));
			}
			det.push_back(curColumn);
			curColumn.clear();
		}
	}

	return determinant(det)/(Factorial<N>::valeur);
}

template<std::size_t N>
double Pavage<N>::interpolation(const Point<N>& point) const{

	double interpo=0.;
	
	for (typename std::set<std::vector<Point<N>*>>::iterator it=figures.begin(); it != figures.end(); ++it){
		//On recherche tout d'abord la figure F1 à laquelle appartient le point passé en argument
		std::vector<Point<N>*> figureCur = *it;
		if (this->isPointInFigure(figureCur,point)){
			//On calcule le volume de la figure F1 dans laquelle le point est contenu
			double denominateur = this->volume(figureCur);
			if (denominateur == 0){
				std::cerr << "Volume de la figure nulle"<<std::endl;
				abort();
			}
			std::vector<double> coordsBarycentriques;
			//On calcule les coordonnées barycentriques du points
			for (unsigned i=0; i < figureCur.size(); i++){
				//Pour calculer une coordonnée barycentrique d'un point P associé à un point Pi de F1, 
				
				//Il faut tout d'abord calculer le volume de la figure F2 de N+1 points
				//formée par :
				// N points parmi les N+1 points de la figure à laquelle le point appartient (privé du point Pi)
				// + le point du point P
				
				//On créé la figure F2
				std::vector<Point<N>*> newFigure;
				newFigure.clear();
				for (unsigned j=0; j < figureCur.size(); j++){
					if (i!=j){
						newFigure.push_back(figureCur.at(j));
					}
				}
				newFigure.push_back(&(const_cast<Point<N>&>(point)));
				
				//On calcule le volume de la figure F2
				double numerateur = this->volume(newFigure);
				
				//La coordonnée barycentrique est alors volume(F20)/volume(F2)
				double coordBarycentriquei=std::abs(numerateur)/std::abs(denominateur);
				coordsBarycentriques.push_back(coordBarycentriquei);
			}
			for (unsigned i=0; i < figureCur.size(); i++){
				double eval = 0.;
				for(std::pair<Point<N>, double>& pair : const_cast<std::list<std::pair<Point<N>, double> >& >(points)){
					if (const_cast<Point<N>&>(pair.first) == *figureCur.at(i)){
						eval = pair.second;
					}
				}
				//L'interpolation du point est finalement 
				//la somme des coordonnées barycentriques associé à Pi * la valeur associée au point Pi
				interpo += coordsBarycentriques.at(i)*eval;
			}
		}
	}
	return interpo;
}


template<std::size_t N>
void Pavage<N>::affectValToBoundries() {
	auto& pts = this->getPoints();
	
	for (std::pair<Point<N>, double>* boundry : this->getBoundries()){
		double sumDist = 0.;
		double moyVal  = 0.;
		for (auto& pt : pts){
			if (!pt.first.isBoundry()){
				double distance = boundry->first.distance(pt.first);
				sumDist += distance;
				moyVal += distance*pt.second;
			}
		}
		boundry->second=moyVal/sumDist;
	}
}

template<std::size_t N>
std::list<std::pair<Point<N>, double>*> Pavage<N>::getBoundries(){

	std::list<std::pair<Point<N>, double>*> boundries;
	std::list<std::pair<Point<N>, double>>& listOfPoints = this->getPoints();

	typename std::list<std::pair<Point<N>, double>>::iterator it;

	for (it = listOfPoints.begin(); it != listOfPoints.end(); ++it){
		Point<N>& pt = (*it).first;
		for (unsigned int i=0; i<N; i++){
			if (pt.isBoundry()){
				std::pair<Point<N>, double>& paire = *it;
				boundries.insert(boundries.end(),&paire);
				break;
			}
		}
	}

	return boundries;
}	
	
	
#endif
