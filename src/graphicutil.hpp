#ifndef _GRAPHUTIL_H
#define _GRAPHUTIL_H

/*!
 * \file grapicutil.hpp
 * \brief Fonctions de dessin d'un pavage de dimension 2
 * \author Olivier Hoarau & Jules Sauvinet
 * \version 0.1
 */

#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include "pavage.hpp"
#include "point.hpp"
#include "../grapic/Grapic.h"

/*! \namespace grapic
 *
 * espace de nommage regroupant les outils de la bibliothèque graphique grapic
 */
using namespace grapic;

/*!
 *  \brief Dessin d'un pavage
 *
 *  Methode qui permet de dessiner un pavage de dimension 2 à l'aide de la bibliothèque graphique grapic
 *  Dessiner les figures du pavage en reliant chaque points lié dans une figure par un segment blanc
 *  Il est possible de mettre en valeur la figure à laquelle appartient un point quelconque de l'espace en
 *  cliquant sur l'interface avec un clic gauche
 *  Il est possible d'ajouter un point au pavage en
 *  cliquant sur l'interface avec un clic droit dans une figure du pavage
 *
 *  \param pavage : le pavage à dessiner
 */
void drawPavage(Pavage<2>& pavage);

#endif
