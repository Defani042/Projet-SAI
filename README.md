# Porjet-SAI

## ARCHITECTURE 
Le projet est structuré en modules pour une architecture :

```text
Projet-SAI/
├─ 📁 include/
│  ├─ 📁 config/
│  ├─ 📁 moteur/
│  └─ 📁 noyau/
├─ 📁 src/
│  ├─ 📁 config/
│  ├─ 📁 moteur/
│  └─ 📁 noyau/
├─ 📁 build/
├─ 📁 game/
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

## Description des modules

Le projet est organisé en modules pour séparer les responsabilités et faciliter l'évolution du moteur de jeu.

---

### 1 Module `noyau`

**Responsabilité : logique fondamentale du jeu**

- **position** (`position.c / position.h`)  
  Gère les coordonnées 3D pour les objets et le joueur.

- **objet** (`objet.c / objet.h`)  
  Gestion des objets 3D :  
  - Création d'objets  
  - Ajout au début ou à la fin d’une liste  
  - Suppression par index ou pointeur  
  - Concaténation de listes  
  - Affichage et calcul de la taille de la liste

- **joueur** (`joueur.c / joueur.h`)  
  Gère l'état du joueur et ses déplacements dans la carte.

- **carte** (`carte.c / carte.h`)  
  Représente la carte et la disposition des objets dans l’espace 3D.

- **aleatoire** (`aleatoire.c / aleatoire.h`)  
  Fournit des fonctions utilitaires pour générer des positions ou valeurs aléatoires.

---

### 2 Module `moteur`

**Responsabilité : interaction et rendu**

- **affichage** (`affichage.c / affichage.h`)  
  - Rendu OpenGL de la scène et des objets  
  - Debug visuel des listes d’objets

- **controle** (`controle.c / controle.h`)  
  - Gestion des entrées clavier et souris  
  - Déplacement du joueur et interaction avec la carte

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

###  Résumé

| Module     | Responsabilité principale |
|------------|--------------------------|
| `noyau`    | Gestion des objets, positions, joueur, carte et utilitaires |
| `moteur`   | Rendu OpenGL, gestion des entrées et debug visuel |
| `config`   | Paramètres globaux du jeu |
| `main`     | Boucle principale et orchestration des modules |