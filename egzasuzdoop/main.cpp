#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <regex>


bool isURL(const std::string& zodis) {

    const std::regex url_pattern(R"((https?:\/\/)?(www\.)?[a-z0-9]+([\-\.]{1}[a-z0-9]+)*\.[a-z]{2,5}(\/[^\s]*)?)");
    return std::regex_match(zodis, url_pattern);
}

int main() {
    std::string failo_vardas = "tekstas.txt";
    std::ifstream tekstas_failas(failo_vardas);
    std::ofstream rezultatas_failas("rezultatas.txt");

    if (!tekstas_failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failo_vardas << std::endl;
        return 1;
    }

    std::map<std::string, int> zodziu_daznumas;
    std::map<std::string, std::set<int>> zodziu_eilutes;
    std::set<std::string> rasti_urlai;
    std::string eilute;
    int eilutes_numeris = 0;

    while (getline(tekstas_failas, eilute)) {
        eilutes_numeris++;
        std::istringstream eilutes_srautas(eilute);
        std::string zodis;
        while (eilutes_srautas >> zodis) {
            if (isURL(zodis)) {
                rasti_urlai.insert(zodis);
                continue;
            }

            zodis.erase(std::remove_if(zodis.begin(), zodis.end(), [](unsigned char c) { return std::ispunct(c); }), zodis.end());
            std::transform(zodis.begin(), zodis.end(), zodis.begin(), [](unsigned char c) { return std::tolower(c); });

            zodziu_daznumas[zodis]++;
            zodziu_eilutes[zodis].insert(eilutes_numeris);
        }
    }
    tekstas_failas.close();


    // isvedami žodžiai
    for (const auto& pora : zodziu_daznumas) {
        if (pora.second > 1) {
            rezultatas_failas << pora.first << ": " << pora.second << "\n";
        }
    }

    // cross-reference lentele
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

    // Url'ai
    rezultatas_failas << "\nRasti URL'ai:\n";
    for (const auto& url : rasti_urlai) {
        rezultatas_failas << url << "\n";
    }

    rezultatas_failas.close();

    return 0;
}



