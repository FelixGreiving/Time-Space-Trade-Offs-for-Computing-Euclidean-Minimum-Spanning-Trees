# Masterarbeit
Im Rahmen meiner Masterarbeit habe ich mich mit Time-Space Trade-Offs zur Berechnung eines Euklidischen Minimalen Spannbaums beschäftigt. 
Als Eingabe erhält der Algorithmus eine Punktmenge der Größe $n$ in allgemeiner Lage und eine natürliche Zahl $s \in$ {1,..., $n$}. Das Ziel ist es,
zu der Eingabepunktmenge unter Ausnutzung von $O(s)$ Speicher den Euklidischen Minimalen Spannbaum mit einer möglichst optimalen Laufzeit zu
berechnen.

Banyassady schlägt in seinem Paper [Time-Space Trade-Offs for Computing Euclidean Minimum Spanning Trees](https://arxiv.org/abs/1712.06431) einen Ansatz vor, mit dem der Euklidische 
Minimale Spannbaum mit einer Laufzeit von $O((n³/s²)\cdot \log(s))$ unter Nutzung von $O(s)$ Speicherzellen berechnet wird. Dabei werden die 
besten oberen Laufzeitschranken für konstante Speichergrößen mit $O(n³)$ und für Speichergrößen, die linear zur Eingabegröße sind, mit $O(n \cdot \log(n))$ 
eingehalten. Für dazwischenliegende Speichergrößen wird die Laufzeit linear zwischen den beiden Laufzeiten interpoliert.

Basierend auf den Ideen Banyassadis habe ich in diesem Projekt einen Time-Space Trade-Off mit der oben genannten Laufzeit implementiert. Die Berechnung des 
EMSTs in der vorgeschlagenen Laufzeit beruht unter anderem stark auf der wiederholten Berechnung des Relativen Nachbarschaftsgraphen (RNG) zu Punktmengen der 
Mächtigkeit s mit einer Laufzeit von $O(s \cdot \log(s))$, wobei $O(s)$ Speicher genutzt wird. Aus diesem Grund habe ich zusätzlich den
Algorithmus von Supovit aus seinem Paper [The Relative Neighborhood Graph, with an Application to Minimum Spanning Trees](https://dl.acm.org/doi/10.1145/2402.322386) implementiert.
Meinen Recherchen zufolge beinhaltet dieses Projekt die erste Implementierung des Time-Space Trade-Offs zur Berechnung eines Euklidischen Minimalen 
Spannbaums nach Banyassadi und die erste Implementierung zur Berechnung eines Relativen Nachbarschaftsgraphen nach Supovit.

Führt man das Build Script aus, so wird initial eine zufällige Eingabepunktmenge, bestehend aus 30 Punkten in allgemeiner Lage berechnet und der EMST zu dieser 
mit s=10 berechnet. Beide Größen sind frei anpassbar. Allerdings sollte Bedacht werden, dass ein kleineres s und eine größere Punktmenge deutlich 
längere Laufzeiten induzieren.

Die folgenden Informationen zur Berechnung des EMSTs zu den zufälligen Eingabepunkten werden in dem Ordner data/Aktuelle_Ergebnisse/ gespeichert:
- Die Datei zufaellige_Eingabepunkte.txt enthät die Eingabepunkte in allgemeiner Lage der Form (x, y)
- Die Datei Delaunay_Triangulation.txt enthält alle Kanten der Delaunay Triangulation zu den Eingabepunkten aus der Datei zufaellige_Eingabepunkte.txt der Form (x,y); (x',y')
- Die Datei Relativer_Nachbarschaftsgraph.txt enthält alle Kanten des Relativen Nachbarschaftsgraphen zu den Eingabepunkten aus der Datei zufaellige_Eingabepunkte.txt in aufsteigender Reihenfolge bzgl. der Kantenlänge der Form (x,y); (x',y')
- Die Datei Euklidischer_Minimaler_Spannbaum.txt enthält alle Kanten des Euklidischen Minimalen Spannbaums zu den Eingabepunkten aus der Datei zufaellige_Eingabepunkte.txt in aufsteigender Reihenfolge bzgl. der Kantelänge der Form (x,y); (x',y')
- Die Datei s-Netz.txt enthält zu jedem Durchlauf, in dem die s nächstgrößeren Kanten des RNG berechnet und anschließend dem EMST zugeordnet werden oder nicht, die (S-Netz) Kanten zur kompakten Repräsentation der face-cycles des aktuellen, partiellen RNG_s der Form (x,y); (x', y') 
- Die Datei Hilfsgraph_G.txt enthält die Punkte und Kanten des Hilfsgraphen G, der während des Einfügens der s nächstgrößeren Kanten zur Repräsentation der face-cycles im aktuellen, partiellen RNG_i,...,RNG_{i+s} dient.
Eine Kante wird als (x,y); (x',y'); komprimierteLänge: a; b gespeichert. Dabei ist die komprimierte Länge a einer Kante von (x,y) zu (x',y') die Anzahl an Kanten eines face-cycles im aktuellen RNG_i, die diese repräsentiert. Da G ein Multigraph ist, gibt b an, ob diese Kante nur einmal (0) oder zweimal vorkommt (1)
- Die Datei face-cycles_G.txt enthält alle face-cycles aus dem Hilfsgraphen G, der während des Einfügens der s nächstgrößeren Kanten zur Repräsentation der face-cycles im aktuellen, partiellen RNG_i,...,RNG_{i+s} dient, als Folge von Kanten der Form (x,y); (x',y'); komprimierteLänge: a; b


## Dependencies:
- gcc
- CMake
- cgal
- boost
- QT5
- python3
- Google Test Framework wird über CMake geladen

## Installation unter Ubuntu ab Version 22.4
- ` $ sudo apt-get install build-essential cmake libcgal-dev libboost-all-dev libcgal-qt5-dev qtbase5-dev qt5-qmake python3`

## Installation unter Ubuntu bis Version 22.4
- ` $ sudo apt-get install build-essential cmake libcgal-dev libboost-all-dev libcgal-qt5-dev qt5-default python3`