# OSY – HW06: Stack overflow

Domaci ukol z predmetu **B4B33OSY** na FEL CVUT. Reseni je napsane v jazyce C a x86-64 assembleru.

Uloha resi prvni dve varianty zadani:

1. Vyvolat na serveru vypis `pwned!` na standardni vystup serveru.
2. Ziskat obsah souboru `/tmp/secret.txt` a vypsat jej na standardni vystup klienta.

## Soubory

- `exploit` – spustitelny shellovy skript, ktery prelozi zdrojove soubory a spusti klienta.
- `exploit.c` – HTTP klient, ktery sestavi a odesle pozadavek a precte odpoved.
- `shellcode.s` – x86-64 kod spoustene casti utoku.

## Pozadavky

- Linux x86-64
- C prekladac `cc`
- GNU binutils (`as` a `objcopy`)
- POSIX shell

## Spusteni

```sh
./exploit http://localhost:8080
```

Skript pouziva docasny adresar pro preklad a neuklada do repozitare zkompilovane soubory. Prvni varianta vypisuje `pwned!` na strane serveru; na stdout klienta se vypise pouze obsah tajneho souboru (druha varianta).

## Odevzdani

Do BRUTE se odevzdava ZIP se zdrojovymi soubory `exploit.c`, `shellcode.s` a spustitelnym skriptem `exploit` (bez binarek). Skript musi jit spustit s jedinym parametrem – URL serveru.

Kod je urceny pro skolni testovaci prostredi a servery, na kterych je testovani povoleno.
