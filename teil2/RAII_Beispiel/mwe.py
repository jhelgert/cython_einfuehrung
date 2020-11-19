#!/usr/bin/env python3

from OurLibrary import Vector

if __name__ == '__main__':
	v = Vector(100)
	v.fill()
	v.print()
	print(f"Summe = {v.sum()}")