# TUI++

Proiectul meu de atestat, 2024

## Descriere

Un library scris in c++20 care tinteste sa inlocuiasca ncurses. Urmarind modelul Elm (relatia Model-View-Update),
libraria are ca tinta robusticitatea, dar si simplicitatea.

## Features:

- [x] Arhitectura Elm
- [x] Suport complet UTF-8
- [x] Lucreaza foarte usor cu terminale TrueColor
- [x] Performanta - Renderer-ul este single-threaded si evita orice procesare non-necesara a outputului. In plus, este atat de rapid incat nici macar nu are nevoie sa calculeze damage.
- [x] Versatilitate - Sistemul de mesaje si comenzi este unul foarte extensibil.
- [x] Simplicitate - Arhitectura MVU duce la cod "clean" si usor de citit
