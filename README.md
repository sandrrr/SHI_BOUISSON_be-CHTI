# BE CHTI

Binôme : Mengxia SHI et Arnaud BOUISSON

# Branches

Nous avons 3 branches :
 - master qui contient le travail demandé a l'étape 1 et 2
 - speed_challenge qui contient notre travail pour le speed challenge
 - size_challenge qui contient notre travail pour le size challenge

# Objectif 0 (Branche master)

Cet objectif correspond a l'étape 1 qui est plus une introduction au BE et qui ne rentre plus dans les objectifs du nouveau sujet.

Fait et testé pour les fréquences de 100Hz, 10kHz et 20kHz.

Afin de vérifier la période, nous avons calculé le temps écoulé (t1 dans Keil) entre 2 appels du callback.  

# Objectif 1 (Branche master)

Cet objectif correspond aux étapes 2.1 et 2.2.

Etape 2.1 : Fait et testé avec une boucle for (pour i de 0 à 63).  
Etape 2.2 : Fait et testé avec tous les jeux de tests.  e

Afin d'observer la table res pour l'étape 2, nous avons mis un watcher sur res et un point d'arrêt sur la boucle infinie.  

# Challenge (Branches speed_challenge et size_challenge)

Résultat speed challenge : 1135 (avant nos modifications - branche master, nous avions 1740)  
Résultat size challenge : 82 (avant nos modifications - branche master, nous avions 94)  

# Objectif 2 (branche master)

Cet objectif correspond  l'étape 3.

Fait et testé avec 0x33, 0x52, 0x3E, 0x3C et 0x4E comme valeur pour le parametre Duree_Ech_ticks de Init_TimingADC_ActiveADC_ff().

Pour tester nous vous conseillons de mettre un point d'arret apres un changement de score dans le callback (ligne 24 du code C) afin d'apprécier chaque tir réussi ou un point d'arret au niveau de la boucle while (ligne 58 du code C). Dans le second cas, il faudra attendre quelques secondes pour que les scores aient le temps d'augmenter. Comme la valeur de Duree_Ech_ticks est 0x52 apres que le tableau des scores se soit rempli, vous devriez observer au niveau du watch de la tableau score (score des 6 pistolets) a respectivement comme valeur 1, 2, 3, 4, 5 et 15 (0xF).


