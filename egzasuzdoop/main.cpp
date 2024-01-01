#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>

int main() {
    std::string failo_vardas = "tekstas.txt";  // Čia įrašykite savo failo pavadinimą
    std::ifstream tekstas_failas(failo_vardas);

    if (!tekstas_failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failo_vardas << std::endl;
        return 1;
    }

    std::map<std::string, int> zodziu_daznumas;
    std::string eilute;
    while (getline(tekstas_failas, eilute)) {
        std::istringstream eilutes_srautas(eilute);
        std::string zodis;
        while (eilutes_srautas >> zodis) {
            // Šalinami skyrybos ženklai ir mažosios raidės
            zodis.erase(std::remove_if(zodis.begin(), zodis.end(), ispunct), zodis.end());
            std::transform(zodis.begin(), zodis.end(), zodis.begin(), ::tolower);
            zodziu_daznumas[zodis]++;
        }
    }
    tekstas_failas.close();

    // Atspausdinami žodžiai ir jų pasikartojimų skaičius
    for (const auto& pora : zodziu_daznumas) {
        std::cout << pora.first << ": " << pora.second << std::endl;
    }

    return 0;
}

