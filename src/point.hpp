#ifndef _POINT_H
#define _POINT_H

/*!
 * \file point.hpp
 * \brief Bibliothèque d'opération sur des points de dimension N templatée
 * \author Olivier Hoarau & Jules Sauvinet
 * \version 0.1
 */

#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstdarg>
#include <array>
#include <cmath>
#include <initializer_list>


/*!< Template N : la dimension de l'espace */
template<std::size_t N>
/*! \class Point
 * \brief classe representant un point dans un espace de dimension N
 *
 *  La classe gère des opérations basiques sur un point destiné à faire partie d'un pavage, c'est-à-dire une représentation d'un 
 *  espace comme un ensemble de figure constituée de N+1 points disjointes dans un espace de dimension N
 */
class Point
{
	private:
		std::array<double, N> coordinates; /*!< Tableau des coordonnées réelles du point de taille N */
		bool boundry = false; /*!< Attribut qui identifie un point comme une borne */

	public:
		/*!
		 *  \brief Constructeur
		 *
		 *  Constructeur vide de la classe Point
		 *
		 */
		Point();

		/*!
		 *  \brief Constructeur par copie
		 *
		 *  Constructeur par copie de la classe Point
		 *
		 */
		Point(const Point& other);

		/*!
		 *  \brief Constructeur par initialisation de coordonnées
		 *
		 *  Constructeur de la classe Point prenant une série de valeurs
		 *
		 *  \param val, ...: les valeurs associées aux index de coordonnée du point à initialiser
		 */
		Point(double val, ...);

		/*!
		 *  \brief Constructeur par initialisation
		 *
		 *  Constructeur de la classe Point prenant une liste de valeurs
		 *
		 *  \param l : la liste des coordonnée à affecter aux coordonnée du point, l'index des valeurs de la liste
		 *  correspondant à l'index des coordonnées du point
		 */
		Point(std::initializer_list<double> l);


		/*!
		 *  \brief Constructeur par déplacement
		 *
		 *  Constructeur de la classe Point par déplacement
		 *
		 *  \param other : le point à déplacer
		 */
		Point(Point&& other);

		/*!
		 * \brief Opérateur d’affectation par déplacement  
		 *
		 * Opérateur d’affectation par déplacement qui fait un transfert des données du point passé en paramètre à this
		 * #rule of 5 #soOpti
		 * 
		 * \param other : le point à déplacer
		 *
		 */
		const Point& operator=(Point&& other);

		/*!
		 *  \brief Opérateur d'affectation
		 *
		 *  Une copie du point passé en paramètre
		 *
		 *  \param other le point à copier
		 *  \return Une copie du point passé en paramètre
		 */
		Point& operator=(const Point& other);

		/*!
		 *  \brief setter d'une coordonnée du point e la coordonnée d'index index du point
		 *
		 *  Met la valeur val à la coordonnée d'index index du point
		 *
		 *  \param index : l'index de la coordonnée
		 *  \param val : la valeur à mettre à la coordonnée
		 */
		void setCoord(unsigned int index, double val);

		/*!
		 *  \brief Setter d'un nombre variable de coordonnées
		 *
		 *  Met les valeurs val en coordonnée du point de la classe, la position de l'argument dans la signature de la fonction
		 *  correspond à l'index du point à définir
		 *
		 *  \param val : la valeur de la premire coordonée, ... les potentielles valeur des autres coordonnées
		 */
		void setCoords(double val, ...);

		/*!
		 *  \brief Getter d'une coordonnée
		 *
		 *  Getter d'une coordonéee d'index index
		 *
		 *  \param index : l'index de la coordonnée à retourner
		 *  \return la valeur de la coordonée d'index index
		 */
		double getCoord(unsigned int index) const;

		/*!
		 *  \brief Determine si le point est dans une zone statique
		 *
		 *  Determine si les coordonnées d'un point ne dépasse pas des limites statiques pour un affichage
		 *
		 *  return true si le point est hors limite, false sinon
		 */
		bool outOfBoundries();

		/*!
		 *  \brief Opérateur d'égalité
		 *
		 *  Surcharge de l'opérateur d'égalité
		 *
		 *  \param other le point avec lequel il faut tester l'égalité
		 *  \return true si toutes les coordonnées du point sont égal au point de la classe, false sinon
		 */
		bool operator==(Point const& other);

		/*!
		 *  \brief Opérateur d'infériorité stricte
		 *
		 *  Surcharge de l'opérateur d'infériorité stricte
		 *
		 *  \param other le point avec lequel il faut tester l'infériorité stricte
		 *  \return true si toutes les coordonnées du point sont inférieure strictement au coordonnées du point de la classe, false sinon
		 */
		bool operator<(const Point& other) const;

		/*!
		 *  \brief Opérateur de supériorité
		 *
		 *  Surcharge de l'opérateur de supériorité
		 *
		 *  \param other le point avec lequel il faut tester la supériorité
		 *  \return true si toutes les coordonnées du point sont supérieure ou égale au coordonnées du point de la classe, false sinon
		 */
		bool operator>=(const Point& other) const;

		/*!
		 *  \brief Opérateur d'infériorité
		 *
		 *  Surcharge de l'opérateur d'infériorité
		 *
		 *  \param other le point avec lequel il faut tester l'infériorité
		 *  \return true si toutes les coordonnées du point sont inférieure ou égale au coordonnées du point de la classe, false sinon
		 */
		bool operator<=(const Point& other) const;

		/*!
		 *  \brief Opérateur de supériorité strict
		 *
		 *  Surcharge de l'opérateur de supériorité strict
		 *
		 *  \param other le point avec lequel il faut tester l'infériorité
		 *  \return true si toutes les coordonnées du point sont supérieures aux coordonnées du point de la classe, false sinon
		 */
		bool operator>(const Point&  other) const;
		
		/*!
		 *  \brief Calcul de distance entre deux points
		 *
		 *  Calcul de distance entre deux points
		 *
		 *  \param other le point 
		 *  \return la distance euclidienne entre deux points
		 */
		double distance(const Point<N>& other) const;

		/*!
		 *  \brief Identificateur d'un point comme borne
		 *
		 *  Identifie le point comme étant une borne
		 *
		 */
		void toBoundry();

		/*!
		 *  \brief Détermine si le point est une borne
		 *
		 *  Détermine si le point est une borne
		 *
		 *  \return true si le point est une borne, false sinon
		 */
		bool isBoundry();

		/*!
		 *  \brief Opérateur d'affichage
		 *
		 *  Surcharge de l'opérateur d'affichage
		 *
		 *  \param Point le point à afficher
		 *  \return (chaque coordonnées séparées par une virgule)
		 */
		template<std::size_t P>
		friend std::ostream& operator<<(std::ostream& os, const Point<P>& point);

};

template<std::size_t N>
Point<N>::Point(){
	//std::cout << "Point::Constructeur vide" << std::endl;
	for(unsigned i=0; i<N; i++){
		coordinates[i] = 0.0;
	}
}

template<std::size_t N>
Point<N>::Point(const Point& other){
	std::cout << "Point::Constructeur par copie" << std::endl;
	for(unsigned i = 0; i<N; i++){
		coordinates[i] = other.coordinates[i];
	}
	this->boundry=other.boundry;
}

template<std::size_t N>
Point<N>::Point(Point&& other){
	//std::cout << "Point::Constructeur par deplacement" << std::endl;
	coordinates = std::move(other.coordinates);
	this->boundry=other.boundry;
	other.coordinates.empty();
}

template<std::size_t N>
Point<N>::Point(double val, ...){
	//std::cout << "Point::Constructeur par valeur (...)" << std::endl;
	this->setCoord(0, val);
	va_list ap;

	va_start(ap,NULL);
	for (unsigned i = 1; i<N; i++){
		this->setCoord(i, va_arg(ap,double));
	}

	va_end(ap);
}

template<std::size_t N>
Point<N>::Point(std::initializer_list<double> l){
	//std::cout << "Point::Constructeur par valeur (initializer_list)" << std::endl;
	for(unsigned i=0; i<N; i++){
		coordinates[i] = 0.0;
	}
	size_t pos = 0;
	for(double v : l){
		if(pos >= N)
			break;
		coordinates[pos] = v;
		pos++;
	}
}

template<std::size_t N>
Point<N>& Point<N>::operator=(const Point& other){
	//std::cout << "Point::Operator=" << std::endl;
	for(unsigned i = 0; i<N; i++){
		coordinates[i] = other.coordinates[i];
	}
	this->boundry=other.boundry;
	return *this;
}

template<std::size_t N>
const Point<N>& Point<N>::operator=(Point&& other){
	//std::cout << "Point::Operateur d'affectation par deplacement" << std::endl;
	if (this != &other){
		coordinates = std::move(other.coordinates);
		other.coordinates.empty();
		delete other.coordinates;
	}
	this->boundry=other.boundry;
	return *this;
}

template<std::size_t P>
std::ostream& operator<<(std::ostream& os, const Point<P>& point){
	os << "(";
	for(unsigned i=0; i<P; i++){
		os << point.getCoord(i);
		if (i != P-1)
			os << ", ";
	}
	os << ")";
	return os;
}

template<std::size_t N>
void Point<N>::setCoord(unsigned int index, double val){
	if (index >= N) {
		std::cerr << "Depassement !" << std::endl;
		abort();
	}
	coordinates[index] = val;
}

template<std::size_t N>
void Point<N>::setCoords(double val, ...){
	this->setCoord(0, val);
	va_list ap;

	va_start(ap,NULL);
	for (unsigned i = 1; i<N; i++){
		this->setCoord(i, va_arg(ap,double));
	}
	va_end(ap);
}

template<std::size_t N>
double Point<N>::getCoord(unsigned int index) const{
	return coordinates[index];
}

template<std::size_t N>
bool Point<N>::outOfBoundries(){
	double MIN_VALUE = -250.0;
	double MAX_VALUE = 250.0;

	for (unsigned int i =0; i<N; i++){
		if (this->getCoord(i) < MIN_VALUE || this->getCoord(i) > MAX_VALUE){
			return true;
		}
	}

	return false;
}

template<std::size_t N>
bool Point<N>::operator==(Point<N> const& other){
	for (unsigned i=0; i<N; i++){
		if (other.getCoord(i) != this->getCoord(i))
			return false;
	}
	return true;
}

template<std::size_t N>
bool Point<N>::operator<(const Point<N>& other) const{
	for (unsigned i=0; i<N; i++){
		if (other.getCoord(i) > this->getCoord(i))
			return false;
	}
	return true;
}

template<std::size_t N>
bool Point<N>::operator>(const Point<N>& other) const{
	return !(*this<other || *this==other);
}

template<std::size_t N>
bool Point<N>::operator<=(const Point<N>& other) const{
	return !(*this>other);
}

template<std::size_t N>
bool Point<N>::operator>=(const Point<N>& other) const{
	return !(*this<other);
}

template<std::size_t N>
double Point<N>::distance(const Point<N>& other) const{
	Point<N> diffOfPoints;
	double dist = 0.0;
	for (unsigned int i=0; i<N; i++){
		dist += (this->getCoord(i)-other.getCoord(i))*(this->getCoord(i)-other.getCoord(i));
	} 
	return std::sqrt(dist);
}

template<std::size_t N>
void Point<N>::toBoundry(){
	boundry= true;
}

template<std::size_t N>
bool Point<N>::isBoundry(){
	return boundry;
}

#endif
