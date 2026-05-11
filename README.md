#Domande

D1 — Quante sentinelle deve inserire ogni produttore quando raggiunge EOF? Perché proprio quel numero?
    Ogni produttore deve inserire tante sentinelle quanto il numero di consumatori nel buffer per fare in modo che ogni consumatore legga una sentinella e termini la lettura.

D2 — È possibile che due produttori leggano EOF “contemporaneamente” e inseriscano entrambi le sentinelle? Come si evita che le sentinelle vengano inserite più volte del dovuto?
    È possibile, ma si può evitare inserendo una variabile int che, quando un produttore invia le sentinelle, viene aggiornata a 1. Quando i produttori leggono che quella variabile e stata settata a 1 terminano il ciclo.

D3 — Perché il mutex sul buffer (mutex_buf) non è sufficiente da solo e servono anche i semafori sem_vuoti e sem_pieni?
    Il mutex protegge l'accesso alle risorse tra i vari consumatori e produttori, i semafori invece gestiscono le attese tra di essi, permettendo ai consumatori di non legegre celle vuote e ai produttori di non scrivere in celle piene.

D4 — L’ordine dei caratteri in output.txt è garantito essere identico a quello di input.txt? Motivare la risposta considerando che ci sono più consumatori che scrivono sullo stesso file.
    L'ordine dei caratteri nell'output non è garantito essere identico a quello dell'input nei processi con NP e NC > 1. Questo perchè l'obiettivo è il throughput concorrente, non la preservazione dell'ordine.

D5 — Cosa succede se BUFFER_SIZE è inferiore al numero di produttori NP? Il programma può andare in deadlock?
    Il programma può andare in deadlock se BUFFER_SIZE < NP durante l'inserimento delle sentinelle. Se nel frattempo tutti i consumatori sono già terminati, nessuno libera più slot e il produttore rimane bloccato su sem_wait(&sem_vuoti) per sempre.

#Commento

La sincronizzazione si basa su due semafori POSIX (sem_vuoti e sem_pieni) e tre
mutex. sem_vuoti conta gli slot liberi nel buffer (inizializato a BUFFER_SIZE) e blocca
i produttori quando è pieno; sem_pieni conta gli slot occupati (inizializzato a 0) e
blocca i consumatori quando è vuoto. mutex_buf protegge gli accessi concorrenti
agli indici del buffer circolare. mutex_file_in e mutex_file_out serializzano
rispettivamente la lettura dal file di input e la scrittura sul file di output,
evitando interleaving tra thread diversi.

La terminazione avviene tramite sentinel: quando un produttore raggiunge EOF
inserisce NC caratteri '\0' nel buffer, uno per ciascun consumatore. Ogni
consumatore termina non appena ne estrae uno. Il main attende tutti i thread
con pthread_join prima di deallocare le risorse.