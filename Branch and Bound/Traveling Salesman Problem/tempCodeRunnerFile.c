int cycle(Edge x[], int k, int next){
	int has_cycle = 0, i=0;
	while(i<k && !has_cycle){
		if (x[i].start == next) has_cycle = 1;
		else i++;
	}
	return has_cycle;
}