# Homework 1 - TPA - Natale Consalvi
## Device: Valigia

In questo homework viene realizzato il device valigia tramite file .svg.

### Parametri utilizzati
I parametri utilizzati sono:
- Posizione della valigia
- Altezza del corpo
- Larghezza del corpo
- Altezza dell'asta
- Larghezza della maniglia
- Raggio delle ruote
- Angolo compreso tra il corpo e l'asta

### Vincoli da rispettare
I vincoli che devono essere rispettati nella costruzione sono:
- Tutti i parametri devono essere strettamente maggiori di zero
- I punti estremi della valigia (descritti volta per volta in base alla rotazione dell'asta) devono essere all'interno del file di dimensione 800x600 pixel
- L'altezza dell'asta deve essere strettamente minore dell'altezza del corpo della valigia
- La larghezza della maniglia deve essere strettamente minore della larghezza del corpo della valigia
- La larghezza dell'asta deve essere strettamente maggiore della larghezza della maniglia
- Il raggio delle ruote deve essere strettamente minore della metà della larghezza della corpo della valigia
- L'angolo di rotazione deve essere tale da non far toccare la maniglia con il corpo o con le ruote della valigia

### Flag aggiuntive
E' stata implementata una funzione in grado di inserire la quotatura delle parti della valigia, tale funzione può essere abilitata o meno dall'utente tramite una scelta inserita nel main.
E' possibile caricare un file .svg dal main e tramite la funzione parse si è in grado di costruire un device tramite il file caricato.

#### Esempio
Di seguito viene mostrato un esempio di device con aggiunta di quotatura.

![alt text](https://github.com/NataleConsalvi/homeworktpa-nc/blob/main/bozzadevice.svg)
