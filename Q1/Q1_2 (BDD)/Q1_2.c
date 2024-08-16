#include <stdlib.h>
#include <stdio.h>
#include <bdduser.h>

bdd and_3(bdd_manager bddm, bdd a, bdd b, bdd c)
{
	bdd t1 = bdd_and(bddm, a, b);	
	return bdd_and(bddm, t1, c);	
}

bdd or_3(bdd_manager bddm, bdd a, bdd b, bdd c)
{
	bdd t1 = bdd_or(bddm, a, b);	
	return bdd_or(bddm, t1, c);	
}

bdd and_4(bdd_manager bddm, bdd a, bdd b, bdd c, bdd d)
{
	bdd t1 = and_3(bddm, a, b, c);	
	return bdd_and(bddm, t1, d);	
}

bdd or_4(bdd_manager bddm, bdd a, bdd b, bdd c, bdd d)
{
	bdd t1 = or_3(bddm, a, b, c);	
	return bdd_or(bddm, t1, d);
}

int main (int argc, char* argv[])
{
	bdd_manager bddm = bdd_init();	

	bdd x1 = bdd_new_var_last(bddm);
	bdd x2 = bdd_new_var_last(bddm);
	bdd x3 = bdd_new_var_last(bddm);
	bdd x4 = bdd_new_var_last(bddm);
	bdd x5 = bdd_new_var_last(bddm);
	bdd x6 = bdd_new_var_last(bddm);

	bdd a = bdd_not(bddm,bdd_and(bddm, x1, x2));
	bdd b = bdd_not(bddm,bdd_and(bddm, x3, x4));
	bdd c = bdd_not(bddm,bdd_and(bddm, x5, x6));

	bdd final  = bdd_and_3(bddm, a, b, c);

	// print
	printf("\n---------------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm, final, NULL, NULL, NULL, stdout);
	printf("\n---------------------------------------------------------------------------\n\n");
	return(0);
}