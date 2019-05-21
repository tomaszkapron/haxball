# haxball
Tomasz Kapron game

Gra multiplayer

#**Zasady gry**:
Celem gry jest strzelanie goli do bramki przeciwnika w celu wygrania meczu.

#**Sterowanie**:
Za pomocą WSAD, strzałek i klawiszy strzału.

#**Mechanika gry**:
Piłka pojawia się po stronie drużyny rozpoczynającej grę. Pionek gracza będącego przy piłce, po wciśnięciu klawisza strzału nadaje mu prędkość i kierunek. Na piłkę działa tarcie. Pilka odbija się od ścian. Pilka ma swój pęd, który może oddziaływać na gracza(delikatnie go przesunać).

Gracz po wciśnięciu klawiszy poruszania się nadaje piłkażykowi predkość i kierunek(tak jak w przypadku piłki). ruch gracza jest jednostajnie opóźniony.(tarcie)


#**tryby gry**:
-1vs1 gracz z graczem na 1 komputerze


**Klasy**:
-pilkarz (ma swoją prędkość,mozliwosc sterowania, nadawania pilce predkosci)

-Pilka

-Boisko (wyznacza granice boiska od których odbija się piłka, ogranicza teren(w przypadku strzelenia gola, gracz który rozpoczyna ma dostęp do piłki))

-fizyka (odpowiedzialna za prędkość, pęd, i ruch obiektów)

-cScena (klasa odpowiedzialna za zasady gry(czas meczu, liczenie wyniku, sprawdzanie wygranej)




