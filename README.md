# MindMaze
Un labyrinthe en openGL, développé avec QtCreator, il inclut une interface en Qt et une detection de la position du visage à l'aide la caméra et de la bibliothèaue openCV

## Prérequis 
* OpenCV
* Qt
il est impératif que ces deux bibliotèques soient installées pour un fonctionnement normal de l'application

## Fonctionnalitées implémentées 
### Fonctionnalitées demandées par le sujet du projet :
* Aﬃchage d’une scène 3D représentant un labyrinthe de 10 cases de large par 6 de haut généré aléatoirement. Présence d’une option pour changer la taille du labyrinthe. 
* Présence d’une lumière ambiante sur les murs, le sol et le plafond. 
* Déplacements du joueur dans le labyrinthe commandés par des déplacements de la tête (rotationdroiteougauchepourtourner,inclinaisonverslehautouverslebaspouravancer ou reculer), présence d’une zone aﬃchant l’image de la WebCam en continu. 
* Détection d’une position neutre de la tête du joueur. 
* Aﬃchage du plan 2D du labyrinthe lorsque le joueur est dans une position neutre. 
* Présence d’une sphère émettant une lumière et texturée du logo de TSE dans le labyrinthe, disparition lorsqu’elle aura été atteinte, déclenchement de l’apparition de la porte de sortie du labyrinthe.
* Aﬃchage du chronomètre avec déﬁlement du temps. 
* Détection de la ﬁn de la partie et ré-initialisation pour la partie suivante.

### Fonctionnalitées rajoutées par les élèves :
* Musique de fond et son emit par la sphère-clef
* Texturage des différents éléments et ajout de sur textures aléatoires sur les murs pour faciliter l'orientation dans le labyrinthe
* Animation du personnage pour un déplacement plus doux et plus simple et animations de pas
* Utilisation d'une skybox pour donner plus de profondeur au décor extérieur, visible par la porte du labyrinthe
* Stockage des paramètres dans un fichier .ini, pour les sauvegarder d'une partie sur l'autre
* Possibilité de changer les controles du jeu en cours de jeu grace à des touches du clavier (camera, souris, clavier)
* Controle du personnage au moyen de la souris et/ou du clavier
* Paramétrage du FOV, réglable en jeu par la molette de la souris
* Fonctionnalité de DEBUG et autres paramètres globaux ajouté au code source, modifiable à la compilation
* Reglaghe de la résolution de la fenêtre de jeuy et mode plein écran

# Contributeurs :
* Léon Delcroix
* Hugo Frigard
##### élèves de *Telecom Saint Etienne*


