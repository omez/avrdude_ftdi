#include <iostream>
#include <zconf.h>

using namespace std;

#define KEXTMODULE "com.apple.driver.AppleUSBFTDI"


int runPriviledged(string command) {
    setuid(geteuid());
    int code = system(command.c_str());
    setuid(getuid());
    return code;
}

int kextload(string bundle) {
    return runPriviledged("kextload -b " + bundle);
}

int kextunload(string bundle) {
    return runPriviledged("kextunload -b " + bundle);
}


int main(int argc, char* argv[]) {
    printf("Real UID\t= %d\n", getuid());
    printf("Effective UID\t= %d\n", geteuid());

    cout << "Unloading kext back..." << endl;
    bool kextUnloaded = kextunload(KEXTMODULE) == 0;


    // DO THE JOB!
    string command = "avrdude ";
    for (unsigned int i = 1; i < argc; i++) command.append(string(argv[i]) + " ");
    system(command.c_str());

    if (kextUnloaded) {
        cout << "Loading kext back..." << endl;
        kextload(KEXTMODULE);
    } else {
        cout << "Skipping kext load..." << endl;
    }

    return 0;
}