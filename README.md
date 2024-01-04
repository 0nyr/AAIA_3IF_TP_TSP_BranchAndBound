# AAIA

> This project is configured for Linux, NixOS

Le problème du voyageur de commerce, ou Travelling Salesman Problem (TSP) en anglais, est un problème classique en recherche opérationnelle et en informatique théorique. Il consiste à trouver le plus court chemin permettant de visiter chaque ville (ou noeud du graphe) une et une seule fois et de retourner à la ville de départ (ou noeud de départ). Le TSP est connu pour être NP-difficile, ce qui signifie qu'il n'existe pas, à l'heure actuelle, d'algorithme permettant de résoudre tous les cas de TSP de manière rapide (en temps polynomial).

Parmi les nombreuses approches pour tenter de résoudre ce problème, l'algorithme Branch & Bound est particulièrement notable. Il s'agit d'une méthode générale de résolution des problèmes d'optimisation discrète, notamment les problèmes d'ordre combinatoire comme le TSP. L'algorithme fonctionne en énumérant systématiquement toutes les solutions possibles et en "coupant" celles qui ne mènent manifestement pas à une solution optimale. Cette technique de coupure, ou "bounding", permet de réduire considérablement l'espace de recherche ce qui accélère d'autant la recherche.

## commands

#### Manual compilation

`gcc src/main.c -O3 -Wall -Werror -o exe`: compile executable.

#### Make compilation

`make dirs`: Before doing anything, create output directories for Make rules.

`make build`: Build by compiling project.

`make run`: Run compiled executable.

#### Python script commands

`kill -9 <PID>`: If you send a Turtle TK windows program to background (with `Ctrl+Z`, which typically suspends the process and sends it to the background in Unix-like operating systems) and can't close it, you can use the provided command to send a SIGKILL (force kill, immediate termination).
