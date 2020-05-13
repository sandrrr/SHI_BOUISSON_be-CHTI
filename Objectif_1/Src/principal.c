int somme_carres(int);
int module_carre(short int[], int);

extern short int TabSig[];

int main(void) {
	int i, res[64];
	for(i=0; i<64; i++) {
		res[i] = module_carre(TabSig, i);
	}
	
	while(1){}
}
