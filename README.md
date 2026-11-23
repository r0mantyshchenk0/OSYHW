# B4B33OSY – Operační systémy

Domácí úlohy z předmětu **B4B33OSY** na FEL ČVUT, zimní semestr 2026/2027.

| Složka | Zadání | Soubory |
| --- | --- | --- |
| [HW01](HW01) | 01regex – Text processing & regular expressions | `script.sh` |
| [HW02](HW02) | 02fork-ipc – Processes, IPC, Signals | `forkpipe.c`, `Makefile` |
| [HW03](HW03) | 03threads – Multithreading & synchronization | `prod-cons.zip` (obsahuje `prod-cons.c` a `Makefile`) |
| [HW04](HW04) | 04factory – Podmínkové proměnné | `factory_fixed.zip` (obsahuje `factory.c` a `Makefile`) |
| [HW05](HW05) | 05syscall – Systémová volání v Linuxu | `hexconv.c` |
| [HW06](HW06) | 06exploit – Stack overflow exploit | `exploit`, `exploit.c`, `shellcode.s` |

## Použití

**HW01**
```sh
cd HW01
bash script.sh -h
```

**HW02**
```sh
cd HW02
make
./forkpipe
```

**HW03 a HW04**

Ve složkách jsou zachované archivy původních odevzdání s C zdrojovým kódem a Makefile. Rozbalit pomocí `unzip`, potom spustit `make`.

**HW05**

Program používá Linux `syscall` přes inline assembler (bez standardní knihovny).
```sh
cd HW05
gcc -nostdlib -no-pie -o hexconv hexconv.c
```

**HW06**
```sh
cd HW06
./exploit http://localhost:8080
```

Úlohy jsou určeny pro školní prostředí a autorizované testování. Zkompilované binární soubory do repozitáře nepatří.
