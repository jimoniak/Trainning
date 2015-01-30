
#include "utils.hpp"
#include "constantes.hpp"

#include <cstdlib>

namespace utils
{

std::vector<std::string> rechercheFichier(std:: string chemin, std::string extension)
{
    std::string  commandeSysteme;
    std::vector<std::string> stringVector;
    if(chemin == "" || chemin.size() > 300  )
    {
        std::cerr<<"Chemin d'acces incorrecte!"<<std::endl;
        return stringVector;
    }
    else
    {

        if(!(extension == "" || extension.size() > 5))
        {
            #ifdef WINDOW
             commandeSysteme = "dir " + chemin + "*" + extension+"* /b > "+ chemin + "liste.txt" ;
            #endif // WINDOW
           #ifdef LINUX
           commandeSysteme = "ls " + chemin + "*" + extension + "/b > "+ chemin + "liste.txt" ;
           #endif // LINUX

           std::cout<< commandeSysteme<<std::endl;

        }

    }
    system(commandeSysteme.c_str());

     std::ifstream fichier((chemin + "liste.txt"));
     std::string s;
     unsigned int i = 0;

    if(fichier){
        while(std::getline(fichier,s))
            {

                stringVector.push_back(s);
               //std::cout<<m_tabCartes[i]<<std::endl;
               i++;
            }
    }
    else
    {
        std::cerr << "Impossible d'ouvrir liste.txt " << std::endl;
        return stringVector;
    }
    fichier.close();

    #ifdef WINDOW

    commandeSysteme = "del " + chemin + "liste.txt";
    #endif // WINDOW

    #ifdef  LINUX
    commandeSysteme = "rm " + chemin + "liste.txt";
    #endif // LINUX



    system(commandeSysteme.c_str());
    return stringVector;
}
}
