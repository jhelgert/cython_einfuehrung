# Takeaways

## Teil 1 (Beschleunigen von Python)

1. Pythonschleifen sind im Vergleich zu low-level Sprachen wie C/C++/Fortran sehr langsam.
2. C-Typen sind deutlich schneller, haben allerdings auch C-Semantik (z.B. Overflow bei ganzzahligen Datentypen).
3. Pythonfunktionen haben einen großen Overhead.
4. Sobald eine Funktion aufgerufen wurde, besteht für den Code innerhalb der Funktion kein Performanceunterschied zwischen `def`, `cdef`und `cpdef`.
5. Verwende *Fused Types* für generischen Cythoncode
6. Verwende die standardisierten ganzzahligen Typen aus `libc.stdint`.
7. Kompilieren mit Profilingflags verlangsam den Code. Daher niemals für den Releasecode verwenden.
8. Verwende Typed Memoryviews für effizienten Zugriff auf `np.array`s.
9. Schleifen über `np.array`s innerhalb von Python möglichst vermeiden.
10. Verwende für Typed Memoryviews auf `np.array`s den richtigen `dtype`.
11. Die Daten in einem `np.array` sind standardmäßig zeilenweise (*row-major*) gespeichert.
12. Bei der Deklaration eines Memoryviews das Memorylayout möglichst angeben und den Speicher in der angelegten Reihenfolge durchgehen (*Cache-friendly Code*).
13. Deklariere Cythonfunktionen, welche keine Pythonobjekte oder -operationen verwenden, mit `nogil`.
14. Für parallelen Cythoncode muss der *Global Interpreter Lock* deaktiviert werden.
15. Verwende für `prange` geeignetes `schedule` und `chunksize`, um die Arbeit optimal unter den Threads aufzuteilen.

## Teil 2 (*Wrapping* von C)

1. Falls möglich, den C-Speicher für Arrays mit Hilfe von `np.array`s in Python allokieren und durch ein Typed Memoryview an die C-Funktion übergeben.
2. Verwende `cython.view.arrays` für die automatische Verwaltung von C-Speicher, der kompatibel zu einem Memoryview ist.
3. Nutze das [RAII](https://de.wikipedia.org/wiki/Ressourcenbelegung_ist_Initialisierung#:~:text=Ressourcenbelegung%20ist%20Initialisierung%2C%20meist%20abgek%C3%BCrzt,Betriebsmitteln%20(auch%20Ressourcen%20genannt).)-Prinzip für automatische Speicherverwaltung innerhalb Pythons.
4. Stelle sicher, dass die `setup.py` deines Cythonpackages mit verschiedenen Compilern funktioniert.
3. [Read the docs](https://cython.readthedocs.io/en/latest/index.html)!
