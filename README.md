#pavage

Création d'un pavage de l'espace en simplexe de dimension N templatée.
Cela doit permettre de pouvoir interpoler un point quelconque de l'espace selon le simplexe dans lequel il est contenu.

By Olivier Hoarau & Jules Sauvinet 

* CONTENU DU DOSSIER *

.
├── bin 
│   └── // Contient l'executable après compilation
│
├── data
│   └── // Contient les resources necessaires à Grapic 
│
├── doc
│   └── // Continent la documentation doxygen (html/index.html) 
│
├── generate.py // Un script pour générer des points
│
├── grapic
│   └── // Contient les sources de la bibliothèque Grapic
│
├── Makefile
│
├── obj
│   └── // Contient les résidus de compilation
│
└── src
    └── // Contient le code source du projet



* COMPILATION *

Il faut installer SDL2 pour pouvoir compiler le projet :

	sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev

Ensuite :

	make


* UTILISATION *

//TODO gérer des arguments en ligne de commande
