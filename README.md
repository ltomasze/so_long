Projekt so_long to jedno z pierwszych zadań w ramach programu szkoły 42, polegające na stworzeniu prostej gry 2D z wykorzystaniem biblioteki graficznej MiniLibX (MLX).<br>
Celem gry jest poruszanie się po mapie, zbieranie wszystkich dostępnych przedmiotów i dotarcie do wyjścia, przy jednoczesnym unikaniu przeszkód.<br>​

Opis gry <br>
Gracz steruje postacią na mapie z góry, używając klawiszy W, A, S, D do poruszania się w górę, lewo, dół i prawo.<br> Mapa jest reprezentowana w pliku .ber, gdzie:<br>
1 oznacza ściany (nieprzekraczalne)<br>
0 to puste przestrzenie<br>
C to przedmioty do zebrania (collectibles)<br>
E to wyjście z mapy<br>

P to początkowa pozycja gracza<br>​

Gra kończy się sukcesem, gdy gracz zbierze wszystkie przedmioty i dotrze do wyjścia.<br>​

Kompilacja i uruchomienie<br>
Aby skompilować projekt, użyj polecenia:<br> 
make<br>
Następnie uruchom grę za pomocą:<br>
./so_long maps/example.ber<br>
Upewnij się, że biblioteka MiniLibX jest poprawnie zainstalowana i dostępna w projekcie.<br>​

Projekt so_long stanowi doskonałe wprowadzenie do programowania gier, grafiki komputerowej oraz obsługi zdarzeń w języku C, rozwijając umiejętności w zakresie zarządzania pamięcią, przetwarzania danych wejściowych i renderowania grafiki.<br>
