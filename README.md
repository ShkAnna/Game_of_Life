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

# Les commandes de programme

| Commande | Description |
| ------ | ------ |
| n | Changer le fichier avec la grille |
| c | Changer le type de voisinage (cyclique / non-cyclique) |
| v | Activer / désactiver le vieillissement |

Générer la documentation
------------------------
~~~{.sh}
make doc
~~~

Exécuter le programme
------------------------
~~~{.sh}
./bin/main <numero de la grille>
~~~

Créer l'archive du projet
------------------------
~~~{.sh}
make dist
~~~

### Versions
* v0.1 - Première partie du projet
* v0.2 - Deuxième partie du projet
* v0.3 - Troisième partie du projet
* v0.4 - Quatrième partie du projet
* v0.5 - Cinquième partie du projet
