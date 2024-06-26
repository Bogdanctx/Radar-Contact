# Radar Contact

### How to play?

Run the game and choose a region. Available regions: Poland, Iceland, Cyprus, Austria, Turkey, UK & Ireland.

![Alt Text](./resources/general_textures/menu.png)

In case of a missing network connection or if you prefer not to download live data, you can play in Offline mode using 
local data. To achieve this, press the "Offline" button.

![Alt Text](./preview/live_data.gif)

After that, control your airspace! Give instructions to airplanes, helicopters and hot air balloons to arrive to their airports.

A flying entity will disconnect from your frequency when it is inside the arrival airport coverage area (the yellow circles). In order to disconnect, some conditions are required: altitude must be below 10000ft and the airspeed must be below 250 knots.

![Alt Text](./preview/landing.gif)

# Collisions!
Be careful! If 2 flying entities are at the same altitude they'll collide!

![Alt Text](./preview/collision.gif)

# Data of a flying entity

Blue text represents new flight data, if any has been given. 

![Alt Text](./preview/data_meaning.png)

# Controls

Change <b>heading</b> by pressing <b>LSHIFT</b> and <b>move your cursor around</b>.

Change <b>altitude</b> by pressing <b>LALT</b> and <b>UP / DOWN Arrows</b>.

Change <b>airspeed</b> by pressing <b>LCTRL</b> and <b>UP / DOWN Arrows</b>.

To go <b>back to menu</b> press <b>Enter</b>. 

## Task 1

#### Cerințe
- [ ✓ ] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [ ✓ ] constructori de inițializare
- [ ✓ ] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [ ] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [ ✓ ] cât mai multe `const` (unde este cazul)
- [ ✓ ] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [ ✓ ] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [ ✓ ] tag de `git`: de exemplu `v0.1`
- [ ✓ ] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Task 2

#### Cerințe
- [ ✓ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ✓ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate**
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [ ✓ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate
  - [ ✓ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
  - [ ✓ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ✓ ] smart pointers (recomandat, opțional)
  - [ ✓ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
- [ ✓ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- [ ✓ ] excepții
  - [ ✓ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [ ✓ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
- [ ✓ ] funcții și atribute `static`
- [ ✓ ] STL
- [ ✓ ] cât mai multe `const`
- [ ✓ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate**
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou <a href="https://github.com/Bogdanctx/Radar-Contact/commit/f90796aac1f9f8388094c3e4b9543ec16e02fb48">Commit aici</a>
- [ ✓ ] tag de `git`: de exemplu `v0.2`

## Task 3

#### Cerințe
- [ ✓ ] 2 șabloane de proiectare (design patterns)
- [ ✓ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ✓ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ✓ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
- [RainViewer](https://www.rainviewer.com/) (Weather API)
- [VATSIM](https://vatsim.dev/) (Airplanes API)
- [Google Fonts](https://fonts.google.com/specimen/Poppins) (Poppins)
- [Google Fonts](https://fonts.google.com/specimen/Raleway?query=raleway) (Raleway)
- [Flaticon](https://www.flaticon.com/free-icon/radar_15721478?term=radar&page=1&position=33&origin=tag&related_id=15721478) (Radar icon)
- [Pixabay](https://pixabay.com/sound-effects/search/air-traffic-control/) (ATC)
- [Pixabay](https://pixabay.com/sound-effects/search/landing/) (Landing sound)
