# Projet Ing2 S1 Théorie des graphes - Ligne d'assemblage
---

## 1. Contexte

Dans toutes les usines de fabrication à la chaîne, une ligne d'assemblage est utilisée pour assembler les parties d'un produit. Dans ce projet, la ligne d'assemblage de la future voiture électrique ECElecar est étudiée, mais le logiciel développé peut optimiser n'importe quelle ligne d'assemblage.

### 1.1. Contraintes d'exclusion 

Certaines opérations ne peuvent pas être effectuées par la même station.

### 1.2. Contraintes de précédence

Certaines opérations doivent être effectuées avant d'autres.

### 1.3. Contrainte de temps de cycle

Les voitures ne restent qu'un temps donné auprès de chaque station.

### 1.4. Optimisation

L'objectif principal est d'optimiser le nombre de stations, donc de minimiser les coûts de production.

## 2. Cahier des charges

### 2.1. Première approche simpliste

Développer des algorithmes pour répondre aux contraintes indépendamment les unes des autres, en prenant en compte les contraintes d'exclusion, de précédence et de temps de cycle.

### 2.2. Dans un second temps : multi-contraintes

Prendre en compte les contraintes différemment, par exemple, contrainte d'exclusion et de précédence, contrainte d'exclusion et temps de cycle, ou les trois à la fois.

### 2.3. Extension : heuristique

Mise en place d'une heuristique pour optimiser le nombre de stations et minimiser le temps de calcul.

### 2.4. Fichiers de contraintes

Stockage des contraintes dans des fichiers texte avec des formats spécifiques.

- **exclusions.txt**: Liste des paires d'opérations ne pouvant pas être exécutées sur la même station.
- **precedences.txt**: Graphe de précédences en listant les arcs du graphe.
- **operations.txt**: Liste des opérations et leur temps d'exécution.
- **temps_cycle.txt**: Durée du temps de cycle.

## 3. Organisation

### 3.1. Git

Utilisation de Git pour la gestion de version. Les branches seront utilisées pour répartir le travail entre les membres de l'équipe.

### 3.2. Livrables

Deux livrables seront rendus :
1. Un diaporama de soutenance contenant les informations sur le groupe, le versionning Git, la méthodologie de travail, le bilan individuel et collectif, et la bibliographie.
2. Dépôt du projet sur GitHub, ne contenant que les codes sources et fichiers textes.

---

*Ce fichier README fournit une vue d'ensemble du projet et des étapes à suivre. Les détails spécifiques du code, des algorithmes et des résultats seront présentés lors de la soutenance.*
