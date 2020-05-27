	AREA DonneeSon, CODE, READONLY
	export LongueurSon_N
	export PeriodeSonMicroSec_N
	export Son_N
LongueurSon_N	DCD	50		; grep dcw son_M.asm | wc
PeriodeSonMicroSec_N	DCD	91
Son_N
	; palier env. 1 ms
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
	; breve pulse negative
 	dcw	-32767
 	dcw	-32767
 	; front montant
	dcw	32767
	; rampe descendante  env. 1 ms
 	dcw	30000
 	dcw	27000
 	dcw	24000
 	dcw	21000
 	dcw	18000
 	dcw	15000
 	dcw	12000
 	dcw	 9000
 	dcw	 6000
 	dcw	 3000
	dcw	0
	dcw	 -3000
	dcw	 -6000
	dcw	 -9000
	dcw	-12000
	dcw	-15000
	dcw	-18000
	dcw	-21000
	dcw	-24000
	dcw	-27000
	dcw	-30000
	dcw	-32767
	; breve pulse positive
 	dcw	32767
 	dcw	32767
	; palier env. 1 ms
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
 	dcw	0
	end
