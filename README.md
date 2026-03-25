# Porjet-SAI

## ARCHITECTURE 
Le projet est structuré en modules pour une architecture :

```text
Projet-SAI/
├─ 📁 include/
│  ├─ 📁 config/
│  ├─ 📁 moteur/
│  ├─ 📁 log/
│  └─ 📁 noyau/
├─ 📁 src/
│  ├─ 📁 config/
│  ├─ 📁 moteur/
│  ├─ 📁 log/
│  └─ 📁 noyau/
├─ 📁 build/
├─ 📁 game/
├─ 📁 fich/
│  └─ 📁 log/
├─ 📄 Makefile
└─ 📄 README.md
```

**Résumé :**

- **include/** → Interface des modules (headers)  
- **src/** → Code source des modules  
- **build/** → Fichiers compilés et objets intermédiaires  
- **game/** → Données et ressources du jeu  
- **Makefile** → Compilation du projet  
- **README.md** → Documentation du projet
- **fich/** → contient tous les fichier géner/utilisé par le jeu


## Description des modules

Le projet est organisé en modules pour séparer les responsabilités et faciliter l'évolution du moteur de jeu.

---

### 1 Module `noyau`

**Responsabilité : logique fondamentale du jeu**

- **position** (`position.c / position.h`)  
  - Gère les coordonnées 3D pour les objets et le joueur.
  - Calcul des distance entre deux position

- **objet** (`objet.c / objet.h`)  
  Gestion des objets 3D :  
  - Création d'objets  
  - Ajout au début ou à la fin d’une liste  
  - Suppression par index ou pointeur  
  - Concaténation de listes  
  - Affichage et calcul de la taille de la liste

- **joueur** (`joueur.c / joueur.h`)  
  - Gère l'état du joueur et ses déplacements dans la carte.
  - Géstion des statistique du joueur

- **carte** (`carte.c / carte.h`)  
  Représente la carte et la disposition des objets dans l’espace 3D.
  - gestion des colision avec les obstacle 
  - gestion des déplacement du joeur 

- **aleatoire** (`aleatoire.c / aleatoire.h`)  
  Fournit des fonctions utilitaires pour générer des positions ou valeurs aléatoires.

- **generateur_carte** (`generateur_carte.c / generateur_carte.h`)  
  création d'une carte de jeu
  - gestion du déplacement du joueur avec les colision
  - gestion des colision entre objet et joueur
---

### 2 Module `moteur`

**Responsabilité : interaction et rendu**

- **affichage** (`affichage.c / affichage.h`)  
  Gestion de l'affichage du jeu (interface + 3D)  
  - Rendu OpenGL de la scène et des objets en 3D
  - Rendu OpenGL de l'interface en 2D

- **controle** (`controle.c / controle.h`)  
  Gestion de l'affichage des input clavier    
  - Gestion des entrées clavier et souris  
  - Déplacement du joueur et interaction avec la carte

- **interface** (`interface.c / interface.h`)  
  Gestion de l'affichage de l'interface en 2D  
  - Rendu OpenGL en 2D de la barre de vie
  - Rendu OpenGL en 2D de la barre du jetpack
  - Rendu OpenGL en 2D du compteur de FPS (éstimation)

- **composant2d** (`composant2d.c / composant2d.h`)    
  Gestion de l'affichage des composant en 2D 
  - affichage d'un rectangle
  - affichage de texte 

- **composant2d** (`composant3d.c / composant3d.h`)     
  Gestion de l'affichage des composant en 3D  
  - affichage d'un parralépipède
  - affichage d'un objet en 3d
  - affichage de la carte en 3D

---

### 3 Module `config`

**Responsabilité : configuration globale du jeu**

- **config** (`config.c / config.h`)  
  Contient les paramètres globaux :  
  - Taille de la fenêtre  
  - Vitesse du joueur  
  - Autres constantes configurables

---

### 4 Module principal

- **main.c**  
  - Point d’entrée du programme  
  - Initialise tous les modules  
  - Boucle principale du jeu : update + rendu  
  - Coordonne l’ensemble du moteur de jeu

---

### 5 Module `log`

**Responsabilité : gestion des logs du jeu**

- **log** (`log.c / log.h`)  
  Contient les fonctions pour créer des journeaux de log :  
  - Création du fichier de log si inexistant  
  - Création des dossiers nécessaires pour les logs  
  - Écriture de messages de log pour le debug ou suivi du jeu  

###  Résumé

| Module     | Responsabilité principale |
|------------|--------------------------|
| `noyau`    | Gestion des objets, positions, joueur, carte et utilitaires |
| `moteur`   | Rendu OpenGL, gestion des entrées et debug visuel |
| `config`   | Paramètres globaux du jeu |
| `main`     | Boucle principale et orchestration des modules |
| `log`      | Gestion des journeaux de log |

## Utilisation du Makefile

Ce projet utilise un **Makefile** pour compiler et exécuter le jeu facilement.

### Commandes principales

- **Compiler le projet** : 
```bash
make
```

ou 

```bash
make all
```
Compile tous les fichiers sources et crée l’exécutable game.  

- **Compile et lancer l’exécutable game** :

```bash
make run
```
Compile si nécessaire puis exécute directement le jeu.  
- **Supprimer les fichiers compilés et l’exécutable** :

```bash
make clean
```
Supprime le dossier build/ et l’exécutable game.  

- **Recompiler complètement le projet** :
```bash
make re
```
Supprime les fichiers compilés et recompile tout depuis zéro.  

- **Compiler et générer les fichier d'assemblage** :  

```bash
make re
```
Compile les fichiers source et génère le code en asembleur.