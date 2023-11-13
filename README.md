# DF Player für Arduino

## Beschreibung

Die Library dient zum Ansteuern eines DF Players. Der Funktionsumfang beschränkt sich auf das Abspielen von Sounddateien, Anhalten der Wiedergabe und die Einstellung der Lautstärke.  
Wer mehr braucht, ist hier besser bedient.  

Eines der Entwicklungsziele war, den TX Ausgang des Prozessors auch für die Debugausgabe bei 115200 Baud nutzen zu können. Die Umschaltung zwischen 9600 Baud für den DF Player und 115200 zur Debug Ausgabe erledigt die Library.  

## Anschluss

Der DF Player wird mit 5V und Masse angeschlossen. Vom TX Ausgang des Prozessors zum RX Eingang des Prozessors ist noch eine Verbindung nötig, das war es dann auch schon.


[Hier geht es zu den Details.](https://github.com/Woschd/Multi-ESP/blob/main/docs/DF_Player.md)  

Varianten:
https://garrysblog.com/2022/06/12/mp3-dfplayer-notes-clones-noise-speakers-wrong-file-plays-and-no-library/

## Vorbereitung des Programmes

Die Datei DF_Player.h wird in das Verzeichnis des Programmes kopiert.
In unserem Programm wird auf die Datei verwiesen und eine Instanz erzeugt:

```
#include "DF_Player.h"
DFplayer mp3; 
```


## Beispiele

### Einstellen der Lautstärke und Abspielen einer Sounddatei  

Im ersten Beispiel ist die Baudrate fest auf 9600 Baud eingestellt.
Der DF Player benötigt nach jedem Befehl eine Zeit von etwa 100ms, bis der wieder bereit ist. Das wird hier mit dem delay(100) Befehl erreicht.

```
#include "DF_Player.h"
DFplayer mp3; 

void setup() {
  Serial.begin(9600);

  mp3.volume(19);
  delay(100);
  mp3.play(999);
}

void loop() {
}
```

### Einstellen der Lautstärke und Abspielen einer Sounddatei ohne delay()
 Im zweiten Beispiel wechselt die Library nach jedem Befehl zu 115200 Baud um eine Debugausgabe mit höherer Geschwindigkeit zu ermöglichen.
Für die Wartezeiten nach einem Geschwindigkeitswechsel und einem Soundbefehl sorgt die Library.  

```
#include "DF_Player.h"
DFplayer mp3; 

void setup() {
  mp3.play_vol(999, 20);
}

void loop() {
  mp3.run();
}
```

## Die Funktionen


```
mp3.play();
```
Ein Titel entsprechend der Nummerierung auf der SD Karte wird abgespielt.  
Führende Nullen werden weg gelassen, die größte mögliche Titelnummer ist XXXX (!!! keine Ahnung, größer 1000)
Ist die Anzahl der Dateien auf der SD Kart sehr groß, macht sich das mit einer Verzögerung vor dem Abspielen bemerkbar.  

---
```
mp3.volume();
```
Die Lautstärke kann mit Werten zwischen 0 und 30 gesteuert werden. Wird der Parameter weg gelassen, gilt der Wert 15.

---
```
mp3.stop();
```
Während der DF Player eine Sounddatei abspielt, kann mit stop() abgebrochen werden.

---
```
mp3.play_vol();
```
In einer Funktion sind volume() und play() vereint.  
Die Baudrate wird für die Befehle des DF Players auf 9600 gestellt und anschließend wieder auf 115200.  
Die nötigen Pausen zwischen den Befehlen werden hier vorbereitet.  
***Voraussetzung:*** mp3.run in der loop().

---
```
mp3.run();
```
Es muss sichergestellt sein, dass die loop() sehr regelmäßig aufgerufen wird.  
run() wird innerhalb von loop() plaziert und sorgt dafür, dass die Befehle an den DF in zeitlich passender Reihenfolge ausgegeben werden.  




