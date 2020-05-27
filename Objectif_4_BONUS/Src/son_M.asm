	AREA DonneeSon, CODE, READONLY
	export LongueurSon_M
	export PeriodeSonMicroSec_M
	export Son_M
LongueurSon_M	DCD	68		; grep dcw son_M.asm | wc
PeriodeSonMicroSec_M	DCD	91
Son_M
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
	; pulse niveau bas env. 1 ms
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
	; front montant
 	dcw	32767
	; demi rampe descendante  env. 1 ms
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
	; demi rampe montante  env. 1 ms
	dcw	0
	dcw	 3000
	dcw	 6000
	dcw	 9000
	dcw	12000
	dcw	15000
	dcw	18000
	dcw	21000
	dcw	24000
	dcw	27000
	dcw	30000
	dcw	32767
	; pulse niveau bas env. 1 ms
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
 	dcw	-32767
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
