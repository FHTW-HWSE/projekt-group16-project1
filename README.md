# Project Gruppe16-1

# Contributors

- Medina Quku
- Jasmina Quku
- Arnel KAupert


## Description

Folgende Aufgaben erfüllt das Programm:
- Generieren des ausgewählten Belegungsmusters bei Angabe von Reihen und Spalten des Hörsaals.
- Vergabe des Sitzplatzes bei Eingabe einer Studierendenkennung.
- Abspeichern der Studierendenkennung und des Sitzplatzes.
- Abfragen der direkten Nachbarn eines bestimmten Studierenden.
- Abfragen der indirekten Nachbarn eines bestimmten Studierenden.

## Use Case 1: 
Ich als Vortragender möchte wissen, wo die Studenten während der Prüfung sitzen, damit im Falle eines positiven Covid-19 Falles das Contact Tracing möglich ist .
Akzeptanzkriterien: 
Wenn ein Student: in während der Prüfung, unwissend, positiv ist und unmittelbar nach der Prüfung das auch rückmeldet 
Dann wird die Anzahl der Studenten: innen die an der Prüfung teilgenommen und direkt neben den Studierenden gesessen sind informiert, indem die Daten aus der gespeicherten Datei aufgerufen werden
Und die Studierenden werden von der Abteilungsleitung informiert

## Use Case 2: 
Ich als Student möchte wissen, ob ich zur Prüfung angemeldet bin.
Wenn ich nicht schon angemeldet bin 
Dann melde ich mich an 
Und finde gleich heraus wo ich mich sitzen werde
 
## Use Case 3: 
Ich als Student melde mich zu spät für die Prüfung an und es gibt keine Plätze frei mehr.
Wenn der Fall eintritt
Dann wird geprüft ob schon alle 24 Plätze besetzt sind
Und im Fall, dass keine Plätze mehr frei sind, werde ich zur Prüfung nicht ehr zugelassen.

# KOMPILIEREN

- Um das Programm zu kompilieren, setze, "set(TESTING FALSE)" bei CMakeLists.txt
- Und fuer die Unit Tests, setze "set(TESTING TRUE)" im CMakeLists.txt