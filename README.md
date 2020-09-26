# KayoCodingGame

Dépôt contenant le code pour la résolution des jeux sur www.codingame.com.

## CG Local

CGLocal permet de travailler en local sur sa machine tout en étant connecté à l'IDE du site web en parallèle. Grâce à un petit script (ici pour le C++), on peut rassembler tous les fichiers et le push sur l'IDE afin de tester sa solution.

## Installation
  
* Aller sur https://www.codingame.com/forum/t/cg-local/10359 et installer l'extension pour son navigateur.
* Télécharger l'application sur le même lien (c'est un exécutable .jar qui est en fait déjà dans ce dépot, sous le répertoire CGLocal)
* Eventuellement installer OpenJDK (sudo apt-get install openjfx)

## Utilisation

Pour lancer l'application, un petit script est prêt à être lancé : 

	./run-cg.sh

Ensuite, allez sur un challenge de votre choix sur le site www.codingame.com, puis cliquez sur l'icone dans le navigateur.
Vous n'aurez alors plus qu'à choisir le fichier qui servira de "passerelle" vers l'IDE en ligne. 

Pour une utilisation plus simple, un autre script permet d'effectuer le paquetage de tous le code en un seul fichier. Pour faciliter le script, il est conseillé de choisir comme fichier "passerelle" le fichier ".transition.cpp". Lorsque vous souhaitez envoyez le code en ligne pour le tester. Il faut procéder en deux étapes :

* éditer le fichier "FILES" en ajoutant le nom des fichiers .h et .cpp à ajouter DANS LE BON ORDRE.
* exécuter le script "./upload.sh"

Enjoy :-)

