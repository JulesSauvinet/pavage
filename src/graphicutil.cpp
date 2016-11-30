#include "graphicutil.hpp"

using namespace grapic;

//TODO interface plus friendly, boutons fonctionnalités, écran d'accueil et choix pavage de départ?
void drawPavage(Pavage<2>& pavage){
	
	//Création de la fenetre
	winInit("Pavage Drawing", 800, 610);
	backgroundColor( 185, 210, 225, 255 );
	
	//Definition de la taille de police 
	fontSize(16);

	//Nettoyage de la fenetre
	winClear();   								
											
	Point<2> pt((double)(300.), (double)(300.));
	bool stop = false;
	while(!stop)
	{
		stop = winManageEvent();

		int x,y;
		mousePos(x, y);
		pt.setCoord(0, (double)x - 300.);
		pt.setCoord(1, (double)y - 300.);

		bool clicked = false;
		bool addpt = false;
		bool insidePavage = false;
		bool empty = pavage.empty();

		if(grapic::isMousePressed(SDL_BUTTON_LEFT)) {
					clicked = true;
		}

		if(grapic::isMousePressed(SDL_BUTTON_RIGHT)) {
					addpt = true;
		}

		color(0,0,0);
		std::set<std::vector<Point<2>*>> figures = pavage.getFigures();

		std::vector<Point<2>*> highlight;
		
		//On créé le dessin du pavage : les points liés entre eux par des segments
		for (std::vector<Point<2>*> figure : figures){

				if ((clicked || addpt) && pavage.isPointInFigure(figure, pt)) {
					highlight.empty();
					highlight=figure;
					insidePavage=true;
				}
				else if (pavage.isPointInFigure(figure, pt)) {
					insidePavage=true;
				}

				for (unsigned int i=0; i<figure.size(); i++){
					Point<2>* pointCur = figure.at(i);
					for (unsigned int j=i+1; j<figure.size(); j++){
						Point<2>* pointCur2 = figure.at(j);
						line(300+pointCur->getCoord(0),300+pointCur->getCoord(1),300+pointCur2->getCoord(0),300+pointCur2->getCoord(1));
					}
				}

		}

		//Si l'on a cliqué avec la souris sur le bouton droit
		//Et que l'on est à l'intérieur du pavage ou que le pavage est vide (sans figure)
		//On demande à l'utilisateur un point pour l'ajouter dans l'espace et dans le pavage
		if (addpt && (insidePavage || empty)){
			double valeur;
			std::cout << "Entrez une valeur : ";
			std::cin >> valeur;
			pavage.addPoint(pt, valeur);
			std::cout<<pt<<std::endl;
		}
		//Si l'on est hors du pavage, on ne peut pas ajouter de point
		else if (addpt && !insidePavage){
			color(255,0,0);
			std::stringstream avert;
			avert << "Impossible d'ajouter le point " << pt << " qui n'est pas dans le pavage!";
			grapic::print(1, 1,  avert.str().c_str());
		}
		//Si l'on a cliqué sur le bouton gauche et que l'on est à l'intérieur du pavage
		//On met en valeur la figure à laquelle appartient le point pointé par la souris
		//Et on affiche les informations de la figure, puis la valeur d'interpolation du point
		else if (clicked && insidePavage) {
			color(255,0,0);
			for (unsigned int i=0; i<highlight.size(); i++){
				Point<2>* pointCur = highlight.at(i);
				for (unsigned int j=i+1; j<highlight.size(); j++){
					Point<2>* pointCur2 = highlight.at(j);
					line(300+pointCur->getCoord(0),300+pointCur->getCoord(1),300+pointCur2->getCoord(0),300+pointCur2->getCoord(1));
				}
			}

			color(0,0,0);
			std::stringstream coord;
			coord << pt.getCoord(0) << " " << pt.getCoord(1) <<  " " << "figure : " ;
			for (int i=0; i<3 ;i++){
				coord << *highlight.at(i) << " ";
			}
			

			grapic::print(1, 25,  coord.str().c_str());
			
			fontSize(20);
			color(255,0,0);
			
			std::stringstream interpo;
			interpo << "Valeur d'interpolation : " << pavage.interpolation(pt);
			
			grapic::print(1, 1,  interpo.str().c_str());
			
			fontSize(16);
			color(0,0,0);
		}
		//Si on est en dehors du pavage on et qu'on a cliqué sur aucun bouton, on l'indique à l'utilisateur
		else if (!insidePavage){
			color(255,0,0);
			std::stringstream avert;
			avert << "Vous etes en dehors du pavage!";
			grapic::print(1, 1,  avert.str().c_str());
		}
		//Sinon on affiche le point associé a la position de la souris
		else if (insidePavage){
			color(0,0,0);
			std::stringstream coord;
			coord << pt.getCoord(0) << " " << pt.getCoord(1);
			grapic::print(1, 1,  coord.str().c_str());
		}
		
		//On créé des petits rectangles pour chaque points
		std::list<Point<2>*> list = pavage.getSinglePoints();
		for (const auto pt : pavage.getSinglePoints()){
			color(0,0,0);
			rectangleFill(pt->getCoord(0)+299,pt->getCoord(1)+299,pt->getCoord(0)+301,pt->getCoord(1)+301);
		}
		
		//On affiche les dessins précédemment créé
		winDisplay();                                      
		delay(50);                                          
		winClear();
		highlight.empty();
		if(grapic::isKeyPressed(SDL_SCANCODE_SPACE)) {		
			stop = true;     
		}
	}

	pause();                                               
	winQuit();
}
