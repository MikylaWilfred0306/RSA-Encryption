
// Mikyla Wilfred mrw104

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"


using std::string;

bool fermet(const BigUnsigned &p) {
if (p == 1){
    return false;
}
BigInteger a = modexp(17,p-1,p);

if (a == 1) return true;

else return false;
}


BigInteger gcd(const BigInteger &x, const BigInteger &y) {
	if (y == 0) return x ;
	else return gcd(y,x % y);
}

BigUnsigned stringToBigUnsigned_mine(string postive_string){
    BigUnsigned x = 0;
    int length = postive_string.length();

    for (int i=0;i<length;i++) {
         x = x*10 + (int)postive_string[i];
    }
    return x;
}
int main() {
	/* The library throws `const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a `try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
    //These take a while to run.
      BigUnsigned big1 = BigUnsigned(1);

       //Test number if the number goes too long
      //big1 = stringToBigUnsigned("5");

   for (int i=0;i<525;i++) {
         big1 = big1*10 +rand();
      }
     if (!fermet(big1)){
         big1 = big1*10 + 7;

     }
    while (!fermet(big1)){
        big1 = big1 + 2;
     }

      BigUnsigned big2 = BigUnsigned(1);

     //Test number if the number goes too long
     // big2 = stringToBigUnsigned("7");


    for (int i=0;i<525;i++) {
         big2 = big2*10 +rand();
      }
      if (!fermet(big2)){
         big2 = big2*10 + 7;
     }

     while (!fermet(big2)){
        big2 = big2 + 2;
     }

       std::ofstream myfile;
        myfile.open ("p_q.txt");
        myfile << big1;
        myfile << "\n";
        myfile <<  big2;
        myfile.close();

        //Generate numbers
       BigUnsigned n = big1 * big2;
       BigUnsigned e = 241;

       BigUnsigned l = (big1 - 1) * (big2 - 1);
       BigUnsigned d = modinv(e, l);

       std::ofstream myfile2;
        myfile2.open ("e_n.txt");
        myfile2 << e;
        myfile2 << "\n";
        myfile2 <<  n;
        myfile2.close();


         std::ofstream myfile3;
        myfile3.open ("d_n.txt");
        myfile3 << d;
        myfile3 << "\n";
        myfile3 <<  n;
        myfile3.close();




	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}


	return 0;
}
