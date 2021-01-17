# TP du navigateur web "zNavigo", du cours en ligne OpenClassrooms

TP du navigateur web "zNavigo", réalisé dans le cadre de la formation en C++ proposée par le
site OpenClassrooms, à l'adresse suivante : https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c/1901871-tp-znavigo-le-navigateur-web-des-zeros

Ce projet consiste à développer un navigateur Web entièrement réalisé en C++ et Qt, à partir
du moteur Web propre à Qt.
Ce navigateur Web a pour page d'accueil la page d'accueil du site DuckDuckGo.
Une navigation par onglets est possible grâce à ce navigateur Web. Il est aussi possible
d'appeler la page précédente, la page suivante, de réactualiser, arrêter un chargement de page
ou revenir à la page d'accueil de l'onglet actif. Pour ce faire, des icônes à gauche
de la barre d'adresse du navigateur sont accessibles. Le menu "Navigation" du
navigateur permet également de faire cela.

Les raccourcis `Ctrl+T`, `Ctrl+W`, `Ctrl+Q` permettent respectivement d'ouvrir un nouvel
onglet, fermer l'onglet actif et de fermer le navigateur. Ces trois raccourcis sont
également accessibles via le menu "Fichier" du navigateur.

Le menu "A propos" du navigateur affiche des informations complémentaires sur ce projet,
ainsi qu'une redirection sur le site de Qt.



Après avoir cloné ce projet, le programme peut être exécuté en entrant les commandes suivantes
à sa racine, dans une fenêtre de commande Linux (le compilateur g++, Qt et l'éditeur de texte Vim
doivent préalablement être installés):
```
qmake -project
sudo vim ${PWD##*/}.pro
```
Puis dans le fichier ouvert par Vim, ajouter la ligne `QT += gui widgets webkitwidgets`, puis quitter
le fichier Vim (Echap puis :wq) pour entrer les commandes suivantes dans la fenêtre de commande Linux :
```
qmake ${PWD##*/}.pro
make
./${PWD##*/}
```
