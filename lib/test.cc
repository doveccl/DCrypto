#define __dc_debug 1
#include "dcrypto.h"

using namespace std;
using namespace DCrypto;

int main() {
	const char *s = "Hello World"; 
	cout << dc_encrypt(s, 0) << endl;
	cout << dc_decrypt(dc_encrypt(s, 0), 0) << endl;
}
