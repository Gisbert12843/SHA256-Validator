#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>



#pragma warning(disable : 4996)

using namespace std;

#include <openssl/sha.h>
#define SHA256_DIGEST_LENGTH 32

std::string sha256(const string path) //Convert file into hash of sha256

{
    ifstream file(path, std::ios::in | std::ios::binary);

    if (!file.good())
    {
        cout << "Couldnt open file at " + path + ".";
        exit(-3);
    }

    constexpr const std::size_t buffer_size{ 1 << 12 };
    char buffer[buffer_size];

    unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

    SHA256_CTX ctx;

    SHA256_Init(&ctx);
    while (file.good())
    {
        file.read(buffer, buffer_size);
        SHA256_Update(&ctx, buffer, file.gcount());
    }
  
    SHA256_Final(hash, &ctx);

    file.close();


    std::ostringstream os;
    os << std::hex << std::setfill('0');

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        os << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }

    return os.str();
}

int start(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Must be used with a file.\n");
        return(-1);
    }
    else if (argc > 2)
    {
        printf("Must be used with only one file.\n");
        return(-2);
    }
    else

        printf("Using file:\t%s\n", argv[1]);


    string userinputSHA256Key = "";
    do
    {
        std::cout << "Please specify the real SHA256 hash." << std::endl;
        cout << "\t\t\t\t";
        getline(std::cin, userinputSHA256Key);
    } while (userinputSHA256Key.length() != 64 && userinputSHA256Key.length() != 32);

    string filehash = "";

    filehash = sha256(argv[1]);

    std::cout << "Hash of the provided file:\t" << filehash << "\n" << std::endl;

    if (filehash == userinputSHA256Key)
        cout << "Hash validated!" << endl;
    else
        cout << "Hash NOT validated! File got altered!" << std::endl;

    return 0;
}

int main(int argc, char* argv[])
{
    int exception = start(argc, argv);
    if(exception != 0)
        std::cout << "Error: " << exception << ". Visit Github-Repo at @Gisbert12843 for more Information and further troubleshooting." << endl;
    system("Pause");
    
    return 0;
}