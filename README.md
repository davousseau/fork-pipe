# fork() et pipe()
## Auteur
[David Brousseau](mailto:dbrsseau@gmail.com)

## Contexte académique
Projet effectué dans le cadre du cours **INF3172 Principes des systèmes d'exploitation**, remis à l'enseignante **Sonia Dimassi** à l'[Université du Québec à Montréal](https://etudier.uqam.ca/) le 15 avril 2019. Ce projet a été retranscris en décembre 2020 pour le rendre public et l'insérer dans mon porte-folio.

## Description
Conception d'un logiciel qui distingue les chiffres des lettres à partir d'un flux de caractères en utilisant un [tube](https://fr.wikipedia.org/wiki/Tube_(shell)). Le logiciel doit afficher la somme des chiffres et la fréquence de chaque lettre.

## Compatibilité
Testé sous un environnement **Linux seulement**.

## Dépendances
- [GCC, the GNU Compiler Collection](https://gcc.gnu.org/), compilateur pour le language C/C++.
- [Doxygen <sup>*</sup>](https://www.doxygen.nl/index.html), outil pour générer la documentation automatique.
- [Valgrind <sup>*</sup>](https://www.valgrind.org/), outil pour vérifier qu'il n'y a pas de fuites de mémoire.

_<sup>*</sup> Dépendances optionnelles selon votre utilisation._

## Environnement suggéré
- [VS Code](https://code.visualstudio.com/), éditeur de texte pour modifier le code.
    - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools), extension pour le language C/C++.
    - [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format), extension pour le formatage du code.
    - [Doxygen Documentation Generator](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen), extension pour générer la documentation.
    - [TODO Highlight](https://marketplace.visualstudio.com/items?itemName=wayou.vscode-todo-highlight), extension pour afficher les TODOs.

## Restriction
Ce logiciel interprète des fichiers d'une **taille maximale** de 255 caractères. Au-delà de ce nombre, les caractères excédentaires seront ignorés.

## Installation
`make`, compile le logiciel.<br>
`make doc`, génère la documentation du projet.<br>
`make memcheck`, vérifie qu'il n'y a pas de fuites de mémoire.<br>
`make clean`, supprime les fichiers compilés.

## Fonctionnement
```
bin/pipeline <filename>
```

## Références
- [fork(2) — Linux manual page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [pipe(2) — Linux manual page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [wait(2) — Linux manual page](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [C Program to demonstrate fork() and pipe()](https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/)
- [Wait System Call in C](https://www.geeksforgeeks.org/wait-system-call-c/)
