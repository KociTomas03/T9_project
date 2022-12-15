# T9_project
1st project at FIT VUT. 
Assignment:
Cílem projektu je vytvořit program, který by emuloval zjednodušený algoritmus hledání kontaktů zadaných pomocí posloupnosti číslic. Vstupem programu je posloupnost číslic. Výstup programu bude obsahovat seznam kontaktů, které odpovídají zadanému číselnému filtru.
Detailní specifikace
Program implementujte ve zdrojovém souboru ''t9search.c''. Vstupní data budou čtena ze standardního vstupu (stdin), výstup bude tisknut na standardní výstup (stdout).
Překlad a odevzdání zdrojového souboru
Odevzdání: Odevzdejte zdrojový soubor ''t9search.c'' prostřednictvím informačního systému.
Překlad: Program překládejte s následujícími argumenty:
gcc -std=c99 -Wall -Wextra -Werror t9search.c -o t9search
Syntax spuštění
Program se spouští v následující podobě: (./t9search značí umístění a název programu):

./t9search CISLO
CISLO zde představuje hledané kritérium, sekvenci číslic 0 až 9, které reprezentují sekvenci hledaných znaků.
Pokud je program spuštěn bez argumentů, program se bude chovat, jako by hledanému kritériu odpovídal každý kontakt ze seznamu.
Implementační detaily
Vstupní telefonní seznam
Telefonní seznam jsou ASCII textová data. Každý záznam o kontaktu obsahuje dva neprázdné (bylo přidáno 2022-10-17, není nutné toto akceptovat) řádky: jméno osoby a jeho telefonní číslo. Každý řádek obsahuje maximálně 100 znaků, jinak se jedná o neplatná data. Seznam kontaktů je neuspořádaný. U všech dat nezáleží na velikosti písmen (tzv. case insensitive). Program musí podporovat alespoň 42 kontaktů.

Kritérium nalezení kontaktu
Pro zjednodušení budeme v tomto projektu uvažovat hledání '''nepřerušené posloupnosti''' zadaných znaků/číslic v telefonním kontaktu. Nepřerušenou posloupností znaků se myslí takový podřetězec, u kterého se na každé pozici vyskytuje znak, který odpovídá jednomu ze znaků, které reprezentuje číslice na stejné pozici v zadaném řetězci. Každá číslice kromě sebe sama reprezentuje ještě následující znaky: 2 (abc), 3 (def), 4 (ghi), 5 (jkl), 6 (mno), 7 (pqrs), 8 (tuv), 9 (wxyz), 0 (+).

Výstup programu
Výstup programu může být dvojího druhu:
žádný kontakt nenalezen,
nalezen jeden a více kontaktů.
