#include "Garma.h"

int main (int argc, char **argv)
{
    if (argc > 0)
        QCoreApplication::setApplicationName(argv[0]); // autoset my ass…
    if (argc < 2) {
        Garma::printHelp();
        return 1;
    }

    bool helpMission = false;
    for (int i = 1; i < argc; ++i) {
        const QString arg(argv[i]);
        if (arg == "-h" || arg.startsWith("--help")) {
            helpMission = true;
            Garma::printHelp(arg.mid(7)); // "--help-"
        }
    }

    if (helpMission) {
        return 0;
    }

    DApplication::loadDXcbPlugin();
    Garma d(argc, argv);

    return d.exec();
}
