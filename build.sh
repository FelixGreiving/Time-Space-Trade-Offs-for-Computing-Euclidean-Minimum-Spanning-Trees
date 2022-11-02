#!/bin/bash
cmake -B build
cmake --build build -j 2
echo
echo "./build/bin/EMST zum Ausführen des Programms"
echo "./build/bin/test_EMST_and_RNG zum Ausführen der Tests"
echo
echo "python3 ./src/graph_visualizer.py ./data/Aktuelle_Ergebnisse/Delaunay_Triangulation.txt red & zur Visualisierung der Delaunay Triangulation"
echo
echo "python3 ./src/graph_visualizer.py ./data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt blue & zur Visualisierung des Relativen Nachbarschaftsgraphen"
echo
echo "python3 ./src/graph_visualizer.py ./data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt green & zur Visualisierung des EMSTs"
