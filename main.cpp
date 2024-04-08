#include <iostream>
#include <array>
#include <cctype>
#include <chrono>
#include <thread>

#include <digestpp.hpp>
#include <rlutil.h>
#include <random.hpp>
#include <csv.hpp>
#include <date.h>

#include <Helper.h>

/////////////////////////////////////////////////////////////////////////////////////////
/// Exemplu de funcții pentru a stoca parole de utilizatori
/// Folosim biblioteca digestpp pentru a nu stoca parolele în clar
std::string make_salt() {
    /// important este ca salt-ul să fie unic, nu contează că nu este aleatoriu
    /// pentru fiecare user, salt-ul se stochează ca text clar, lângă parola hashed
    /// Exemplu:
    /// class User {
    ///     std::string hashed_password;
    ///     std::string salt;
    /// };
    ///
    static uint64_t nr = 1u;
    std::string salt;
    auto bytes = static_cast<char*>(static_cast<void*>(&nr));
    for(unsigned i = 0; i < 16; i++) {
        salt += bytes[i%8];
    }
    ++nr;
    return salt;
}

std::string hash_password(const std::string& plain, const std::string& salt) {
    return digestpp::blake2b(512).set_salt(salt).absorb(plain).hexdigest();
}
/////////////////////////////////////////////////////////////////////////////////////////

#include <Helper.h>

int main() {
    std::cout << "Hello, world!\n";
    std::array<int, 100> v{};
    int nr;
    std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nr; ++i) {
        std::cout << "v[" << i << "] = ";
        std::cin >> v[i];
    }
    std::cout << "\n\n";
    std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    for(int i = 0; i < nr; ++i) {
        std::cout << "- " << v[i] << "\n";
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    ///                Exemplu de utilizare cod generat                     ///
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////

    std::cin.ignore(); // clear last \n

    std::cout << "-----------------------------------------------\n";

    ///////////////////////////////////////////////////////////////////////////
    ///                Exemplu criptare parole (digestpp)                   ///
    ///////////////////////////////////////////////////////////////////////////
    std::string plain = "temaOOP12345$";
    auto salt1 = make_salt();  // salt pt user1
    auto salt2 = make_salt();  // salt pt user2
    /// Explicație: deși userii au aceeași parolă, vor avea hash-uri diferite
    /// De ce am vrea asta? Dacă aflăm hash-ul pt un user, nu vom avea automat hash-urile
    /// și pentru alți utilizatori care au folosit aceeași parolă
    /// Alte explicații aici: https://en.wikipedia.org/wiki/Rainbow_table
    ///
    std::cout << "Parola hashed pt user1: " << hash_password(plain, salt1) << "\n"
              << "Parola hashed pt user2: " << hash_password(plain, salt2) << "\n";
    ///
    /// Altă variantă pentru parole criptate este cu bcrypt, dar trebuie compilat.
    /// Un exemplu demo (mai vechi) este aici: https://github.com/zackartz/Bcrypt.cpp
    ///
    std::cout << "-----------------------------------------------\n";

    ///////////////////////////////////////////////////////////////////////////
    ///               Exemplu terminal interactiv (rlutil)                  ///
    ///////////////////////////////////////////////////////////////////////////
    rlutil::setConsoleTitle("test");
    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::BLUE);
    rlutil::cls();
    int key = rlutil::getkey(); // apel blocant; apelează kbhit și getch
    switch(std::tolower(key)) {
        case rlutil::KEY_SPACE:
            std::cout << "pressed space\n";
            break;
        case 'w':
            std::cout << "pressed w\n";
            break;
        case 'a':
            std::cout << "pressed a\n";
            break;
        case 's':
            std::cout << "pressed s\n";
            break;
        case 'd':
            std::cout << "pressed d\n";
            break;
        default:
            std::cout << "other key (" << key << ")\n";
            break;
    }
    std::cout << "test color text\n";
    rlutil::resetColor();

    std::cout << "-----------------------------------------------\n";

    ///////////////////////////////////////////////////////////////////////////
    ///                           Exemplu sleep                             ///
    ///////////////////////////////////////////////////////////////////////////
    using namespace std::chrono_literals;
    std::cout << "begin sleep\n";
    std::this_thread::sleep_for(600ms);
    std::cout << "end sleep\n";

    std::cout << "-----------------------------------------------\n";

    ///////////////////////////////////////////////////////////////////////////
    ///                     Exemplu numere aleatoare                        ///
    ///////////////////////////////////////////////////////////////////////////
    using Random = effolkronium::random_static;
    // Random::seed(42);
    std::cout << Random::get(1, 1000) << "\n";

    std::cout << "-----------------------------------------------\n";

    ///////////////////////////////////////////////////////////////////////////
    ///           Exemplu fișier CSV (comma separated value)                ///
    ///////////////////////////////////////////////////////////////////////////
    using namespace csv;
    CSVReader reader{"date.csv"};
    for (CSVRow& row : reader) {
        std::cout << "nume: " << row["nume"].get_sv() << "\n";
        // std::cout << "nume: " << row["nume"].get<>() << "\n";
    }

    std::cout << "-----------------------------------------------\n";

    ///////////////////////////////////////////////////////////////////////////
    ///              Exemplu de lucru cu date calendaristice                ///
    ///////////////////////////////////////////////////////////////////////////
    using namespace std::chrono;
    using namespace date;
    using date::sys_days;
    using date::days;
    using date::weeks;
    using date::months;
    auto d1 = 2022_y/10/01;
    auto d2 = 2023_y/05/26;

    auto dp1 = sys_days{d1};
    auto dp2 = sys_days{d2};

    std::cout << "Anul 2022-2023 are "
              << duration<float, months::period>(dp2 - dp1).count() << " luni"
              << " sau "
              << duration<float, weeks::period>(dp2 - dp1).count() << " săptămâni"
              << " sau "
              << duration<float, days::period>(dp2 - dp1).count() << " zile"
              << ", adică "
              << floor<months>(dp2 - dp1).count() << " luni, "
              << floor<weeks>(dp2 - dp1 - floor<months>(dp2 - dp1)).count() << " săptămâni, "
              << floor<days>(dp2 - dp1 - floor<weeks>(dp2 - dp1)).count() - 1 << " zile."
              << "\n";

    std::cout << "-----------------------------------------------\n";
    return 0;
}
