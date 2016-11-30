#ifndef _MATHUTIL_H
#define _MATHUTIL_H

/*!
 * \file mathutil.hpp
 * \brief Fonction mathématiques de base
 * \author Olivier Hoarau & Jules Sauvinet
 * \version 0.1
 */

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>

/*!
 *  \brief Calcul de la Factorial de N
 *
 *  Template qui permet de calculer la Factorial d'un entier positif, n doit être positif
 *
 *  \param N : le nombre dont on veut obtenir la Factorial
 *  \return la Factorial de n
 */
template <unsigned int N> struct Factorial
{ enum { valeur = N*Factorial<N-1>::valeur};};
template <> struct Factorial<0>
{ enum {valeur =1}; };

/*!
 *  \brief Calcul d'un déterminant
 *
 *  Methode qui permet de calculer un déterminant à partir d'une matrice de réel
 *
 *  \param det : un vecteur de vecteur de réel correspondant à la représentation en matrice du déterminant
 *  \return le déterminant associée à la représentation matricielle
 */
double determinant(std::vector<std::vector<double>> det);

/*!
 *  \brief Determine si une chaine de caractere est un entier
 *
 *  Permet de déteminer si une chaine de caractère est un entier
 *
 *  \param s : chaine de caractere dont il faut tester la nature
 *  \return true si la chaine de caractere est un entier, false sinon
 */
inline bool isInteger(char* &s){
	if (s == nullptr)
		return false;
	if (( !isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))
		return false;
	char *p;
	strtol (s, &p, 10);
	return (*p==0);
}

/*!
 *  \brief Calcul de Pow
 *
 *  Template qui permet de calculer la Pow d'un nombre
 *
 *  \param nombre : la nombre à élever en Pow
 *  \param puis : l'exposant de la Pow à calculer
 *  \return le nombre nomrbe élevé à l'exposant puis
 */
 template  <unsigned int N>
 inline double Pow(double x)
 {return x*Pow<N-1>(x);}

 template <>
 inline double Pow<0>(double)
 {return 1.0;}

/*!
 *  \brief Calcul de pi
 *
 *  Methode qui permet de calculer pi
 *
 *  \return une valeur approximée satisfaisante de pi
 */
constexpr double pi(){return std::atan(1)*4;}

#endif
