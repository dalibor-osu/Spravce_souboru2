# CMakeList.txt: Projekt CMake pro Textovy_spravce_souboru, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (Spravce_souboru2 "Spravce_souboru2.cpp" "Spravce_souboru2.h" "Funkce.cpp" "unistd.h" "getopt.h")

# TODO: V případě potřeby přidejte testy a cíle instalace.
