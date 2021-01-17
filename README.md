# TP du navigateur web "zNavigo", du cours en ligne OpenClassrooms

TP du navigateur web "zNavigo", réalisé dans le cadre de la formation en C++ proposée par le
site OpenClassrooms, à l'adresse suivante : https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c/1901871-tp-znavigo-le-navigateur-web-des-zeros



Après avoir cloné ce projet, le programme peut être exécuté en entrant les commandes suivantes
à sa racine, dans une fenêtre de commande Linux (le compilateur g++, Qt et l'éditeur de texte Vim
doivent préalablement être installés):
```
qmake -project
sudo vim ${PWD##*/}.pro
```
Puis dans le fichier ouvert par Vim, ajouter la ligne `QT += gui widgets`, puis quitter
le fichier Vim (Echap puis :wq) pour entrer les commandes suivantes dans la fenêtre de commande Linux :
```
qmake ${PWD##*/}.pro
make
./${PWD##*/}
```
