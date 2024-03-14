# TO-DO list

- preverjanje collisionov v zvezi z ledenimi gorami (so ovira, zato noben entity ne more čez) + **VELIKOST** -- `done`
- **OBNAŠANJE KITOLOVCEV** 
    - če igralca ni v bližini so idle -> default random movement
    - če pride do ledene gore se spremeni destination
    - če igralec je v bližini, beži proti najbližjemu kitolovcu, da gresta skp *(session type shit?)*
    - če pride do drugega kitolovca, se zmenta in se združta, če se ju igralec dotakne nardita damage
    - skupaj ostaneta, dokler je igralec v bližini
- **Obnašanje atolov**
    - počasi skozi igro rastejo (na podlagi ticksov tko kt se ledene gore premikajo)
    - začetne koordinate, velikost so naključne
    - ko doseže določeno velikost počasi izgine -> fade-out transition
- **Obnašanje gusarjev**
    - najbl simpl
    - če ne zazna igralca, se randomly premika
    - če ga zazna, ga lovi (destination == igralec)
    - pazi: igralčevim koordinatam sledi z zamikom, izogiba se tudi ledenim goram
    - ne vidi igralca čez ledeno goro *(kako nardit? -> od gusarja do igralca gre premica, če je kera od točk na premici znotraj hitboxa od ledene gore, potem igralca ne vidi več)*
- menjavanje med leveli (to je že bl k ne)
- pause menu, start menu
- victory/defeat screen
- save progress
- save/watch replay
- **RISANJE POVRŠINE/OZADJA**
- **UČINEK KAMERE**
    - ne vidiš celega polja hkrati, ampak je cel zaslon le del polja, ostalo se skriva izven okna (kot agar.io)


*ČE OSTANE CAJT*
- Premikanje z miško