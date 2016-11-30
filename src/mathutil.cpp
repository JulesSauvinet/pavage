#include "mathutil.hpp"

/*
 * Calcul du déterminant à partir d'un vecteur de vecteur
 * représentant une matrice carrée
 */
double determinant(std::vector<std::vector<double>> det){
	//Si le vecteur est vide, le déterminant est nulle
	if (det.size()==0){
		return 0;
	}
	//Si le vecteur contient une seule valeur x, le déterminant vaut x
	if (det.size()==1){
		double x10=det.at(0).at(0);
		return x10;
	}
	//Si le vecteur est de la forme 2x2:
	//  |x1 y1|
	//  |x2 y2|,
	//le déterminant vaut x1*y2 - x2*y1
	if (det.size()==2){
		if (det.at(0).size()!=2 || det.at(1).size()!=2){
			std::cerr<<"Proubleme"<<std::endl;
			abort();
		}
		double x10=det.at(0).at(0);
		double x20=det.at(0).at(1);
		double y10=det.at(1).at(0);
		double y20=det.at(1).at(1);
		return x10*y20-y10*x20;
	}
	//Si le vecteur est de la forme NxN:
	//	|x2,2 - x1,1	 ...   xn+1,1 - x1,1|
	//  |x2,2 - x1,2	 ...   xn+1,2 - x1,2|   
	//  |...  	         ...	     ...    | 
	// 	|...	         ...	     ...    |
	//	|x2,n - x1,n  ...      xn+1,n - x1,n|,
	//
	// le déterminant vaut la somme des (déterminants des sous-matrices de taille N-1xN-1 * coefficient a_i,j de ligne i,j 
	// qui a permis d'extraire la sous-matrice * (-1)^(i+j) (cf wikipédia, article déterminant pour plus de détails)
	//
	double detNum=0.;
	for (unsigned int j=0;j<det.size();j++){
		double epsilon=1.;
		if ((j%2) != 0)
			epsilon = -1.;
		std::vector<std::vector<double>> subDet;
		for (unsigned int k=1; k<det.size(); k++){
			std::vector<double> subDetCurColumn;
			for(unsigned int p=0; p<det.size(); p++){
				if(p != j){
					subDetCurColumn.push_back(det.at(k).at(p));
				}
			}
			subDet.push_back(subDetCurColumn);
			subDetCurColumn.clear();
		}
		detNum += epsilon * (double) det.at(0).at(j) * determinant(subDet);
		subDet.clear();
	}
	return detNum;
}
