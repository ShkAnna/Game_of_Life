Jeu de la vie
=============

Ce [dépôt](https://git.unistra.fr/sushko/Jeu_de_la_vie) contient mon projet du cours de Techniques de développement : Le Jeu de la Vie (Game of Life).

# Contenu du projet

| Dossier / fichier | Description |
| ------ | ------ |
| grilles/ | Contient les grilles différentes |
| include/ | Contient les fichiers en-tête (headers) contenant les structures et les prototypes des fonctions |
| src/ | Contient les fichiers avec le code source de notre programme|
| Doxyfile | Fichier de configuration de doxygen (permettant de générer la documentation) |
| Makefile | Fichier contenant un ensemble d'actions propres au projet (compilation, suppression des artefacts, etc.) |

Générer la documentation
------------------------
~~~{.sh}
make doc
~~~

Exécuter le programme
------------------------
~~~{.sh}
./bin/make grilles/grille1.txt
~~~

Créer l'archive du projet
------------------------
~~~{.sh}
make dist
~~~

### Versions
* v0.1 - Premier partie du projet

