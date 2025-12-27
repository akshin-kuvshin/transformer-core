import math
import pywintypes
import sys

ms = ThisDrawing.ModelSpace
ut = ThisDrawing.Utility
ptCenter = ut.GetPoint(None, "Укажите центр звезды")

while (n := ut.GetInteger("Укажите количество лучей (больше 2х)")) <= 2: ...

d = ut.GetDistance(ptCenter, "Задайте внутренний радиус")
dt = ut.GetDistance(ptCenter, "Задайте внешний радиус")
da = math.pi * 2  / n
hd = da / 2

for i in range(n):
  a = da * i
  pt1 = ut.PolarPoint(ptCenter, a - hd, d)
  pt2 = ut.PolarPoint(ptCenter, a, dt)
  pt3 = ut.PolarPoint(ptCenter, a + hd, d)
  ms.AddLine(pt1, pt2)
  ms.AddLine(pt2, pt3)
