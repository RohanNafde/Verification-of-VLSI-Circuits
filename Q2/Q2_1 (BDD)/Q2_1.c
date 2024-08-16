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

	// initializations
	bdd u3 = bdd_new_var_last(bddm);
	bdd u2 = bdd_new_var_last(bddm);
	bdd u1 = bdd_new_var_last(bddm);
	bdd u0 = bdd_new_var_last(bddm);

	bdd u3n = bdd_not(bddm, u3);
	bdd u2n = bdd_not(bddm, u2);
	bdd u1n = bdd_not(bddm, u1);
	bdd u0n = bdd_not(bddm, u0);

	bdd care = or_4(bddm, and_3(bddm, u3n, u2n, u1n), and_3(bddm, u3n, u2n, u0n), and_3(bddm, u3n, u1n, u0n), and_3(bddm, u2n, u1n, u0n));

	// Specifications
	bdd e_s = bdd_and(bddm, or_4(bddm, u3, bdd_and(bddm, u3n, u2), and_3(bddm, u3n, u2n, u1), and_4(bddm, u3n, u2n, u1n, u0)), care);
	bdd c1_s = bdd_and(bddm, bdd_or(bddm, u3, bdd_and(bddm, u3n, u2)), care);
	bdd c0_s = bdd_and(bddm, bdd_or(bddm, u3, and_3(bddm, u3n, u2n, u1)), care);

	// Tests
	bdd e_t = bdd_and(bddm, or_4(bddm, u3, u2, u1, u0), care);
	bdd c1_t = bdd_and(bddm, bdd_or(bddm, u3, u2), care);
	bdd c0_t = bdd_and(bddm, bdd_or(bddm, u3, u1), care);

	// print
	printf("\n---------------------------------------------------------------------------\n\n");
	if(e_s == e_t)
		printf("true\n");
	else
		printf("false\n");
	if(c1_s == c1_t)
		printf("true\n");
	else
		printf("false\n");
	if(c0_s == c0_t)
		printf("true\n");
	else
		printf("false\n");

	printf("\n---------------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm, e_s, NULL, NULL, NULL, stdout);
	printf("\n---------------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm, c1_s, NULL, NULL, NULL, stdout);
	printf("\n---------------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm, c0_s, NULL, NULL, NULL, stdout);
	printf("\n---------------------------------------------------------------------------\n\n");
	return(0);
}