## Voraussetzungen

Um Cython installieren bzw. verwenden zu können, wird ein C Compiler benötigt.

## Wie installiere ich einen C und C++  Compiler?

### Windows 
Hier empfiehlt sich der Microsoft C++ Compiler (MVSC):

- Dieser befindet sich in den [Visual Studio Build Tools](https://visualstudio.microsoft.com/de/thank-you-downloading-visual-studio/?sku=BuildTools&rel=16).
- Im Installer links `C++ Buildtools` auswählen und installieren.

Visual Studio selbst wird nicht benötigt, kann aber gerne auch installiert werden.

PS: Bitte kein MinGW installieren/verwenden.

### macOS
Der Standard C Compiler unter macOS ist clang, welcher in den Command Line Developer Tools enthalten ist. Für Parallelisierung und bessere SIMD-Autovektorisierung verwenden wir allerdings gcc statt clang, zudem wird noch OpenMP benötigt. Am bequemsten kann man alles via [Homebrew](https://brew.sh) installieren.

Dazu folgendes in ein neues Terminalfenster einfügen und mit Enter bestätigen:
``` 
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```

Homebrew wird dabei ggf. automatisch Apples Command Line Developer Tools installieren. 
Nachdem Homebrew installiert wurde, kann innerhalb des Terminals mit
```
brew install gcc g++ libomp
```
die GNU Compiler Collection (gcc) und OpenMP installiert werden.

### Linux

Ihr wisst bestimmt selbst, wie ihr `gcc`, `g++` und `libomp-dev` installiert :)
Für Ubuntu:
```
sudo apt install build-essentials libomp-dev
```

## Wie installiere ich Cython?

**Nachdem** ein C Compiler installiert wurde, kann Cython 0.29.x und der Line Profiler 
einfach via pip innerhalb eines Terminals (Für Windowsuser: cmd.exe oder PowerShell) installiert werden:

```
pip3 install cython line_profiler
```

Die aktuellste Cython 3.0.x Version (noch alpha!), kann auch installiert werden:

```
pip3 install Cython==3.0.0a9
```

Nutzer der Anacondadistribution von Python müssen stattdessen nur den `line_profiler` installieren, da Cython bereits
in Anaconda enthalten ist. Das geht mit

```
conda install -c anaconda line_profiler
```

innerhalb eines Terminals.
