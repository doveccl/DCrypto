#include "../lib/dcrypto.h"

using namespace std;
using namespace DCrypto;

int main() {
    const char *s = "Hello World"; 
    cout << dc_encrypt(s, 110) << endl;
    cout << dc_decrypt(dc_encrypt(s, 110), 110) << endl;
}
