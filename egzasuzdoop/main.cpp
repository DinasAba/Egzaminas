#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
    std::string failo_vardas = "tekstas.txt";  // Čia įrašykite savo failo pavadinimą
    std::ifstream tekstas_failas(failo_vardas);
    std::ofstream rezultatas_failas("rezultatas.txt"); // Išorinis failas rezultatams

    if (!tekstas_failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failo_vardas << std::endl;
        return 1;
    }

    std::map<std::string, int> zodziu_daznumas;
    std::map<std::string, std::set<int>> zodziu_eilutes;
    std::string eilute;
    int eilutes_numeris = 0;

    while (getline(tekstas_failas, eilute)) {
        eilutes_numeris++;
        std::istringstream eilutes_srautas(eilute);
        std::string zodis;
        while (eilutes_srautas >> zodis) {
            // Šalinami skyrybos ženklai ir mažosios raidės
            zodis.erase(std::remove_if(zodis.begin(), zodis.end(), [](unsigned char c) { return std::ispunct(c); }), zodis.end());
            std::transform(zodis.begin(), zodis.end(), zodis.begin(), [](unsigned char c) { return std::tolower(c); });

            zodziu_daznumas[zodis]++;
            zodziu_eilutes[zodis].insert(eilutes_numeris);
        }
    }
    tekstas_failas.close();

    // Išvedami žodžiai ir jų pasikartojimų skaičius
    for (const auto& pora : zodziu_daznumas) {
        if (pora.second > 1) {
            rezultatas_failas << pora.first << ": " << pora.second << "\n";
        }
    }

    // Išvedama cross-reference lentelė
    rezultatas_failas << "\nCross-Reference Lentelė:\n";
    for (const auto& pora : zodziu_eilutes) {
        if (pora.second.size() > 1) {
            rezultatas_failas << pora.first << ": ";
            for (int eil_nr : pora.second) {
                rezultatas_failas << eil_nr << " ";
            }
            rezultatas_failas << "\n";
        }
    }

    rezultatas_failas.close();

    return 0;
}

