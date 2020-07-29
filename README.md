# Diplomová práca
## Automatické segmentačné metódy biologických dát

Tento repozitár obsahuje projekt s diplomovou prácou. Zdrojový kód je umiestnený v podpriečinku src/. 
Súbory na kompiláciu v TeXu k textu diplomovej práci spolu s aktuálnym pdf súborom sa nachádza v podpriečinku  tex_files/. 
Testovacie dáta sa nachádzajú v priečinku test_data/.

Na vybuildovanie projektu je potrebné použiť [cmake](https://cmake.org/).

Na skompilovanie sú potrebné knižnice:

* [Qt v5.13.1](https://www.qt.io/) ~ použité na vytvorenie UI.
* [VTK](https://vtk.org/) ~ použité na zobrazovanie dát.

# Kompilovateľné pre verzie VTK knižníc

## v8.2.0

* projekt kompilovaateľný pod v8.2.0 sa nachádza v **master** vetve.

## v9.0.0

* projekt kompilovaateľný pod v9.0.0 sa nachádza v **vtk9** vetve.
* pri kompilovaní VTK knižníc treba pridať nasledujúce moduly (treba ešte skontrolovať či sú všetky moduly naozaj potrebné):
        
    ![ included modules ](modules.png)


