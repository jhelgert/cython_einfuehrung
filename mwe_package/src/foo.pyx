
cdef void cy_foo():
	print("Hi, ich bin eine Cythonfunktion und kann nur aus Cython aufgerufen werden")


def foo():
	cy_foo()

