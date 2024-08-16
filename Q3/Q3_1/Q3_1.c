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
	int s = 4; // making it robust for any number of states (s)
	bdd_manager bddm = bdd_init();	

	// declaration of x and r
    bdd r[s+1], x[s+1]; // inputs (5 for each)

	// initialization of x and r
	for(int i=0; i<s+1; i++)
	{
		if(i==0)
			r[i] = bdd_one(bddm); // fixed to 1 as given in question r(0) = 1
		else
			r[i] = bdd_new_var_last(bddm);
		x[i] = bdd_new_var_last(bddm);
	}

	// Circuit 1

	// declaration of BDDs
    bdd s0[s+1], s1[s+1], s2[s+1], s3[s+1]; // state variables (5 for each)
    bdd o1[s+1]; // outputs (5)

	// initialisation
    s0[0] = bdd_new_var_last(bddm);
    s1[0] = bdd_new_var_last(bddm);
    s2[0] = bdd_new_var_last(bddm);
    s3[0] = bdd_new_var_last(bddm);

	// State Transition with state as i
	for(int i=0; i<s; i++)
	{
		s0[i+1] = bdd_ite(bddm, r[i], bdd_one(bddm), bdd_ite(bddm, x[i], s3[i], s1[i]));
		s1[i+1] = bdd_ite(bddm, r[i], bdd_zero(bddm), bdd_ite(bddm, x[i], s0[i], s2[i]));
		s2[i+1] = bdd_ite(bddm, r[i], bdd_zero(bddm), bdd_ite(bddm, x[i], s1[i], s3[i]));
		s3[i+1] = bdd_ite(bddm, r[i], bdd_zero(bddm), bdd_ite(bddm, x[i], s2[i], s0[i]));
	}

	// output for state i
	for(int i=0; i<s+1; i++)
		o1[i] = bdd_and(bddm, bdd_not(bddm, r[i]),bdd_ite(bddm, x[i], s3[i], s1[i]));

	// Circuit 2

	// declaration
	bdd t0[s+1], t1[s+1], xor[s+1], equal[s+1];
	bdd o2[s+1];

	// initialization
	t0[0] = bdd_new_var_last(bddm);
    t1[0] = bdd_new_var_last(bddm);
	xor[0] = bdd_xor(bddm, t0[0], t1[0]);
	equal[0] = bdd_xnor(bddm, t0[0], t1[0]); // xnor is our equality checker

	// state transition with state as i
	for(int i=0; i<s; i++)
	{
        t0[i+1] = bdd_ite(bddm, r[i], bdd_zero(bddm), bdd_not(bddm, t0[i]));
        t1[i+1] = bdd_ite(bddm, r[i], bdd_zero(bddm), bdd_ite(bddm, x[i], xor[i], equal[i]));
		xor[i+1] = bdd_xor(bddm, t0[i+1], t1[i+1]);
		equal[i+1] = bdd_xnor(bddm, t0[i+1], t1[i+1]);
	}

	// output for state i
    for (int i =0; i < s+1; i++)
        o2[i] = bdd_and(bddm, bdd_not(bddm, r[i]), bdd_ite(bddm, x[i], equal[i], xor[i]));


	// print
	printf("\n---------------------------------------------------------------------------\n\n");
	for(int i=0; i<s+1; i++)
	{
		if(o1[i] == o2[i])
			printf("true\n");
		else
			printf("false\n");
	}
	printf("\n---------------------------------------------------------------------------\n\n");
	return(0);
}