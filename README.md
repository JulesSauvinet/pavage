#pavage
</br>
Création d'un pavage de l'espace en simplexe de dimension N templatée.</br>
Cela doit permettre de pouvoir interpoler un point quelconque de l'espace selon le simplexe dans lequel il est contenu.</br>
</br>
By Olivier Hoarau & Jules Sauvinet </br>
</br>
* CONTENU DU DOSSIER *</br>

.</br>
├── bin </br>
│   └── // Contient l'executable après compilation</br>
│</br>
├── data</br>
│   └── // Contient les resources necessaires à Grapic </br>
│</br>
├── doc</br>
│   └── // Continent la documentation doxygen (html/index.html) </br>
│</br>
├── generate.py // Un script pour générer des points</br>
│</br>
├── grapic</br>
│   └── // Contient les sources de la bibliothèque Grapic</br>
│</br>
├── Makefile</br>
│</br>
├── obj</br>
│   └── // Contient les résidus de compilation</br>
│</br>
└── src</br>
    └── // Contient le code source du projet
</br>
</br>
</br>
* COMPILATION *</br>
</br>
Il faut installer SDL2 pour pouvoir compiler le projet :</br>


	sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev

Ensuite :</br>

	sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
	make

