
n = 100;
norm[x_] := x.x;
TriplexSquare[{x_, y_, z_}] := If[x == y == 0, {-z^2, 0, 0}, Module[{a = 1 - z^2/(x^2 + y^2)}, {(x^2 - y^2)a, 2 x y a, -2 z Sqrt[x^2 + y^2]}]];
Mandelbulb[c_] := Module[{p = {0,0, 0}, i = 0}, While[i < 24 && norm[p] < 4, p = TriplexSquare[p] + c; i++]; i];
image = Table[z = 1.5; While[z >= -0.1 && Mandelbulb[{x, y, z}] < 24, z -= 3/n]; z, {y, -1.5, 1.5, 3/n}, {x, -2, 1, 3/n}];
ListDensityPlot[image, Mesh -> False, Frame -> False, PlotRange -> {-0.1, 1.5}] 
