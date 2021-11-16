#include <iostream>

using namespace  std;


string operator * (string str, unsigned int n){
	/** permet de multiplier des chaines de caractere par des entier positif de la meme facon qu'en python
	 * @param str la chaine de caractere
	 * @param n le nombre de repetition
	 * @return str concataine n-1 fois avec lui-même
	**/
    string output = "";
    while (n--) {
        output += str;
    }
    return output;
}
