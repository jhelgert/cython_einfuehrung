cdef extern from "our_simple_c_lib.h" nogil:
	ctypedef struct c_vec:
		double* data
		int size
	c_vec* clib_init(int n)
	void clib_fill(c_vec* v)
	void clib_print(c_vec* v)
	double clib_sum(c_vec* v)
	void clib_free(c_vec* v)

# Beispiel für RAII:
# Wir packen die Funktionalität der C-Library einfach in eine Klasse, so
# dass Pythons Garbage Collector automatisch den Speicher aufräumt.
# Konkret: Beim Erstellen eines Objekts der Klasse wird __cinit__ und
# daher die C-Fkt clib_init() aufgerufen. Sobald wir das Objekt der Klasse 
# löschen oder unser Programm beenden, wird automatisch __dealloc__
# aufgerufen und daher auch die C-Fkt clib_free().
# 
# ---> Müssen nicht wie in C von Hand den Speicher aufräumen :).
    
cdef class Vector:
	cdef c_vec* __ptr

	def __cinit__(self, N):
		self.__ptr = clib_init(N)
		if self.__ptr == NULL:
			raise MemoryError("Oh no, memory error")

	def __dealloc__(self):
		clib_free(self.__ptr)
		print("Speicher aufgeräumt.")

	def print(self):
		clib_print(self.__ptr)

	def fill(self):
		clib_fill(self.__ptr)

	def sum(self):
		return clib_sum(self.__ptr)
