# BE CHTI

Binôme : Mengxia SHI et Arnaud BOUISSON

# Branches

Nous avons 3 branches :
 - master qui contient le travail demandé a l'étape 1 et 2
 - speed_challenge qui contient notre travail pour le speed challenge
 - size_challenge qui contient notre travail pour le size challenge

# Objectif 0 (Branche master)

Cet objectif correspond a l'étape 1.1 qui est plus une introduction au BE et qui ne rentre plus dans les objectifs du nouveau sujet.

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

Cet objectif correspond à l'étape 3.

Fait et testé avec 0x33, 0x52, 0x3E, 0x3C et 0x4E comme valeur pour le parametre Duree_Ech_ticks de Init_TimingADC_ActiveADC_ff().

Pour tester, nous vous conseillons de mettre un point d'arrêt apres un changement de score dans le callback (ligne 24 du code C) afin d'apprécier chaque tir réussi. Sinon, vous pouvez ne mettre aucun point d'arrêt et attendre quelques secondes avant de stopper l'excution afin que les scores aient eu le temps d'augmenter. Comme la valeur de Duree_Ech_ticks est 0x4E (signal 1 d'amplitude 124, signal 2 d'amplitude 248 et bruit d'amplitude 100), après que le tableau des scores se soit rempli, vous devriez observer au niveau du watch du tableau score (score des 6 pistolets) qu'il a respectivement comme valeur 1, 2, 3, 4, 5 et 15 (0xF).

# Objectif 3 (branche master)

Cet objectif correspond l'étape 1.2.

Fait et testé avec bruitverre.asm (forme du signal correspondant et periode entre chaque echantillon correcte).

Pour tester nous vous conseillons de lancer le programme avec le logic analyser et vous devriez obtenir l'allure ci-contre :

![Signal Obj3](/images/spectre_obj3.png)

L'amplitude est de 0 a 720, car nous avons choisi 100kHz comme frequence pour la PWM.
Pour verifier qu'il y a bien 91us entre deux echantillons, nous vous conseillons de mettre un point d'arret quand un echantillon est load (ligne 22 du code asm). Et de calculer le temps écoulé (t1 dans Keil) entre 2 arrets, vous devriez trouver 91us.

#Objectif 4 (branche master)

Fait et testé avec 0x4E comme valeur pour le parametre Duree_Ech_ticks de Init_TimingADC_ActiveADC_ff() et bruitverre.asm comme son.

Pour tester, nous vous conseillons de mettre un point d'arrêt apres un changement de score dans le callback (ligne 31 du code C) afin d'apprécier chaque tir réussi. Aussi, vous devriez observer que dans le logic analyser un son est joue a chaque changement de score. 
Le signal devrait etre le suivant :

![Signal Obj4](/images/spectre_obj4.png)

Comme la valeur de Duree_Ech_ticks est 0x4E (signal 1 d'amplitude 124, signal 2 d'amplitude 248 et bruit d'amplitude 100), après que le tableau des scores se soit rempli, vous devriez observer au niveau du watch du tableau score (score des 6 pistolets) qu'il a respectivement comme valeur 1, 2, 3, 4, 5 et 15 (0xF).

# Objectif 4 Bonus (branche master)

Bonus (proposé par M.Nouillet) : jouer un son different pour chaque pistolet.

Meme fonctionnement qu'a l'objectif 4 mais maintenant on peut observer des sons diffrents en fonction du pistolet comme le montre le signal ci-dessous :

![Signal Obj4 Bonus](/images/spectre_obj4_bonus.png)

