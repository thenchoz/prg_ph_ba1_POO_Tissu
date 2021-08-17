
README
------


Tous les parties demandées du projet ont été réalisées.

De plus de quelques optionnels tels que l'intégrateur de Newmark (en plus du RK4), la création et modification du système graĉe au terminal (classe Initial) qui verifie les entrées fournies par l'utilisateur, 

de même que la méthode deconnecte pour la suppression d'un ressort et opérateur += des TissuComposee.



Nous avons réalisé une version graphique avec Qt5 de notre simulation de système, où l'on peut voir les masses comme des cubes et les ressorts comme des segements de droites. 
L'avantage des cubes réside dans le fait que grâce à leurs surfaces coloréees avec des couleurs différentes, ça permet de remplacer un système d'axe.
Les contraintes ne sont pas visibles mais leurs effets s'appliquent tout de même sur les masses.





Un compte précis du nombre d'heure par personne n'a pas été fait mais une moyenne de 3.5 heures par personne par semaine serait une approximation résonable. 





Les sources en général sont dans le dossier "general", la partie graphique dans "Qt_GL", la partie text dans "text" et les test dans "Test"


Execution du programme
----------------------



Pour exécuter le programme final :
 
 - ouvrir le dossier "gregoireh-g109"
 - ouvrir dans un terminal;
 
 - taper qmake;
 
 - taper make;

 - pour executer en mode text :		taper ./text/projet_text
 - pour executer en mode graphique : 	taper ./Qt_GL/projet_gl
   

Lorsqu'on exécute le programme, le terminal va nous poser différentes questions par exemple le type d'intégrateur, le type de tissu, les attributs des masses,
les attributs des ressorts, le nombre de contraintes et leurs types respectifs...
L'utilisateur devra entrer entrer un nombre qui correspond à une option particulière (type d'intégrateur par exemple) ou à une valeur (constante de rappel des ressorts). 
Les entrées invalides par exemple une masse négative ne sont pas acceptées. 
Une fois que le système a été définit, l'animation du système est lancée.
On peut arrêter/redémarrer la simulation avec la barre espace. A chaque arrêt il sera possible de modifier le système si on le désire (changer d'inégrateur, ajouter des contraintes...)
La vue de la caméra, qui visualise le système peut être déplacé grâce aux touches.



Pour exécuter les tests :
 

 - ouvrir le dossier "Tests"

 - ouvrir dans un terminal;
 
 - taper make;
 
 - taper ./test*cible*, avec *cible* le  nom de la class à tester (attention, pour certains test il faut faire suivre avec un entier correspondant au numéro du test)


Les anciens tests seraient tous à refaire. En effet, il y a eu des modifications des constructeurs, car les classes Masse, Ressort et Tissu héritent désormais de Dessinable.
