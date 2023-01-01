#include <bits/stdc++.h>
using namespace std;

set<int> prime;
int public_key;
int private_key;
int n;

void primefiller()
{
    vector<bool> seive(250, true);
    seive[0] = false;
    seive[1] = false;
    for (int i = 2; i < 250; i++)
    {
        for (int j = i * 2; j < 250; j += i)
        {
            seive[j] = false;
        }
    }
    for (int i = 0; i < seive.size(); i++)
    {
        if (seive[i])
            prime.insert(i);
    }
}

int pickrandomprime()
{
    int k = rand() % prime.size();
    auto it = prime.begin();
    while (k--)
        it++;
    int ret = *it;
    prime.erase(it);
    return ret;
}

void setkeys()
{
    int prime1 = pickrandomprime();
    int prime2 = pickrandomprime();

    n = prime1 * prime2;
    int fi = (prime1 - 1) * (prime2 - 1);
    int e = 2;
    while (1)
    {
        if (__gcd(e, fi) == 1)
            break;
        e++;
    }
    public_key = e;
    int d = 2;
    while (1)
    {
        if ((d * e) % fi == 1)
            break;
        d++;
    }
    private_key = d;
}

long long int encrypt(double message)
{
    int e = public_key;
    long long int encrpyted_text = 1;
    while (e--)
    {
        encrpyted_text *= message;
        encrpyted_text %= n;
    }
    return encrpyted_text;
}

long long int decrypt(int encrpyted_text)
{
    int d = private_key;
    long long int decrypted = 1;
    while (d--)
    {
        decrypted *= encrpyted_text;
        decrypted %= n;
    }
    return decrypted;
}

vector<int> encoder(string message)
{
    vector<int> form;

    for (auto &letter : message)
        form.push_back(encrypt((int)letter));
    return form;
}
string decoder(vector<int> encoded)
{
    string s;

    for (auto &num : encoded)
        s += decrypt(num);
    return s;
}

int main()
{
    primefiller();
    setkeys();

    string message = "Syeda Reeha Quasar 14114802719";

    vector<int> coded = encoder(message);
    cout << "Name and Roll:\n"
         << message;
    cout << "\n\nThe encoded message(encrypted by public key)\n";
    for (auto &p : coded)
        cout << p;
    cout << "\n\nThe decoded message(decrypted by private key)\n";
    cout << decoder(coded) << endl;

    return 0;
}
