
.* italiano.ipf - Aiuti in Italiano per Minta.
.*
.*##############################
.*
.*        Minta
.*        =====
.*        italiano.ipf
.*        v 2.50 - GA
.*        2002-05-20
.*
.*        (c) 2002 Alberto Gabrielli
.*
.*##############################
.*

.* 2002-05-20 thth: - Reversed the order of the version history.
.*                  - Added a missing "compact" to the ul tag of the v2.50 entry.

:userdoc.

.im src\common.ipf

.* There are some song titles and band names used in the examples in this
.* file. Please do not translate them.

.*-------------------------------------------------------------------------
.*fold00.*About the program

:h1 id=about res=1000.Informazioni sul programma
:fn id=mp3.
:p.MP3 Š un formato per la codifica di dati audio (canzoni, brani musicali, etc.)
che consente di codificare molti suoni in pochi byte. In altre parole, Š un formato
che permette alti tassi di compressione.
:efn.

:fn id=tag.
:p.Un brano MP3 pu• possedere un cosiddetto "contrassegno ID3" (ID3 tag), che consiste
semplicemente in un segmento di dati aggiunto alla fine del brano. Questi dati comprendono
informazioni addizionali su quel brano musicale&colon. titolo, artista, album, anno,
un commento, il genere musicale, un numero di traccia (ID3 v1.1).
Molti lettori MP3 possono mostrare queste informazioni.
:efn.

.*-------------------------------------------------------------------------

:artwork name='src/data/minta.bmp' align=center.
:p.Questo programma mostra informazioni sui brani audio :link refid=mp3
reftype=fn.MP3:elink., ed eventualmete permette di aggiungere loro un :link refid=tag
reftype=fn.contrassegno ID3:elink..


:p.Esattamente come steste lavorando su un singolo pezzo, &progname. permette facilmente
di modificare i contrassegni di molti brani; sia uno alla volta che contemporaneamente.

:p. anche possibile eliminare il contrassegno da uno o pi— brani, o persino ridenominare
automaticamente i brani stessi!

:p.Il programma pu• anche creare una lista di brani MP3 comprendente tutte o solo una
parte delle informazioni di ogni singolo pezzo.

:p.:hp2.Che c'Š di nuovo?:ehp2.

:p.Se interessati, nella :link refid=history reftype=hd.lista delle revisioni:elink. potete
trovare cosa ci sia di nuovo o modificato in questa versione.

:p.Tenete presente che ci sono molte cose che potrebbero, e saranno, aggiunte nelle prossime
versioni del programma. Eventualmente (sebbene io non prometta nulla ;-) mandatemi i
vostri commenti ed eventuali richieste su cosa vi piacerebbe avere...

:p.:hp2."Registrazione":ehp2.

:p.&progname. Š "mailware", quindi per favore se lo usate mandatemi un breve messaggio di
posta elettronica! (od anche una cartolina, o quel che preferite)
(vedi anche :link refid=register reftype=hd."Le 10 migliori scuse per non registrare
&progname.":elink.;-)



.*-------------------------------------------------------------------------
.*fold00.*The windows

:h1 id=windows res=2000.Le finestre
:p.Questa sezione illustra le varie finestre di &progname., quali funzioni offrano e
come usarle.

:p.
:ul compact.
:li.La :link refid=mainwindow reftype=hd.finestra principale:elink.
:li.La :link refid=settingswindow reftype=hd.finestra delle Impostazioni:elink.
:li.La :link refid=listwindow reftype=hd.finestra della Lista:elink.
:li.La :link refid=autoopenwindow reftype=hd.finestra per l'Apertura Automatica:elink.
:li.La :link refid=renamewindow reftype=hd.finestra per Ridenominare i brani:elink.
:eul.

.*-------------------------------------------------------------------------
.*fold00.*The main window

:h2 id=mainwindow res=2100.La finestra principale
:p.La finestra principale Š quella in cui si compie la maggior parte del lavoro.
Qui si possono modificare i contrassegni ed ottenere informazioni sui brani.

:p.La finestra principale ha le seguenti sezioni&colon.
:ul compact.
:li.:link refid=filelist reftype=hd.La lista dei brani selezionati:elink.
:li.:link refid=fileinfo reftype=hd.Il visualizzatore di informazioni sul brano:elink.
:li.:link refid=taginfo reftype=hd.Il visualizzatore di informazioni sul contrassegno:elink.
:li.:link refid=buttons reftype=hd.I pulsanti ed il menu:elink.
:eul.


.*-------------------------------------------------------------------------
.*fold00.*The selected files list

:h3 id=filelist res=2110.La lista dei brani selezionati
:p.Questa lista contiene i nomi dei brani selezionati, cioŠ di quelli su cui
potete intervenire.

:dl break=all tsize=5.

:dt.:hp2.Aggiunta di brani alla lista:ehp2.
:dd.Ci sono diversi metodi per aggiungere brani alla lista&colon.
:ul.

:li.Potete usare la finestra che appare spingendo il pulsante "Apri..." o selezionando
"Apri..." dal menu "Brano".

:li.Potete fare in modo che sia &progname. a :hp1.cercare nelle cartelle i brani da
aggiungere:ehp1. selezionando "Apri gruppo..." dal menu "Brano".
Apparir… :link refid=autoopenwindow reftype=hd.una finestra:elink. in cui
selezionare la cartella che dovr… essere esplorata in cerca di brani MP3 da aggiungere.

:p.:hp1.Nota&colon.:ehp1. verranno esplorate anche tutte le sottocartelle della cartella
indicata.

:li.Si possono trascinare brani e/o cartelle sulla finestra principale di &progname. usando
la manipolazione diretta col mouse. I brani saranno aggiunti alla lista; le cartelle
saranno esplorate in cerca di brani da aggiungere.
:eul.

:dt.:hp2.Togliere brani dalla lista:ehp2.
:dd.Ci sono diversi metodi per togliere brani dalla lista&colon.
:ul.
:li.Per togliere solo il brano corrente, premere ALT+'t' o selezionare "Togli dalla lista"
dal menu "Brano".
:li.Per togliere tutti i brani, scegliere "Togli tutti dalla lista" dal menu "Brano".
:eul.

:edl.

:p.Le operazioni globali, come "Scrivi su tutti" o "Rimuovi da tutti", agiscono
contemporaneamente su tutti i brani della lista.

:p.Le operazioni singole, come "Registra" e "Rimuovi", agiscono solo sul brano
visualizzato.

:p.Il titolo di questa sezione mostra il numero dei brani attualmente contenuti nella lista.

:p.Premendo ALT+'s' (o scegliendo "Registra &amp. successivo" dal menu "Contrassegno") si
registra il contrassegno corrente e si seleziona il prossimo brano della lista.
Premere ALT+'p' (o scegliere "Registra &amp. precedente" dal menu "Contrassegno") ha lo stesso
effetto, ma seleziona il brano precedente quello visualizzato. Con questo sistema
si possono facilmente modificare uno alla volta molti brani.


.*-------------------------------------------------------------------------
.*fold00.*The file information display

:h3 id=fileinfo res=2120.Il visualizzatore di informazioni sul brano
:p.Questa sezione mostra informazioni tecniche sul brano MP3 corrente.
Questi valori sono letti direttamente dalla testata del brano MP3 e non possono
essere modificati.

:dl break=all tsize=5.

:dt.:hp2.Versione:ehp2.
:dd.Questa riga mostra la :hp1.versione:ehp1. del brano MP3.

:dt.:hp2.Livello:ehp2.
:dd.Questa riga mostra il :hp1.livello:ehp1. (1, 2 o 3) del brano MP3.

:dt.:hp2.Campionamento:ehp2.
:dd.Questa riga mostra la :hp1.frequenza di campionamento:ehp1., o :hp1.tasso di
campionamento:ehp1., del brano.

:dt.:hp2.Bitrate:ehp2.
:dd.Questa riga mostra il :hp1.bitrate:ehp1. del brano MP3. Il "bitrate" indica al lettore
MP3 quanti bit decodificare per ogni secondo.

:dt.:hp2.Modo:ehp2.
:dd.Pu• essere&colon. stereo, joint stereo, dual channel o mono (singolo canale).
Per favore non chiedete a me cosa significhino esattamente "joint stereo" o "dual
channel" &colon.-)

:dt.:hp2.Durata prevista:ehp2.
:dd.Una stima di durata del brano.  calcolata basandosi sulla dimensione del brano
e sul bitrate.

:dt.:hp2.Preenfasi:ehp2.
:dd.Usata raramente. Qualcosa riguardante la riduzione del rumore di fondo...

:dt.:hp2.Privato:ehp2.
:dd.Indica se il brano sia "privato" o meno. Qualunque cosa si ritenga ci• possa
significare.

:dt.:hp2.Copyright:ehp2.
:dd.Questo indica se il contenuto del brano MP3 sia protetto da diritto d'autore.

:dt.:hp2.Originale:ehp2.
:dd.Indica se il brano sia un originale od una copia. Non so esattamente a cosa possa servire
saperlo, n‚ chi o cosa modifichi questa indicazione, ma...

:dt.:hp2.CRC:ehp2.
:dd.Indica se il brano MP3 possieda un qualche tipo di correzione d'errore.

:dt.:hp2.Padding:ehp2.
:dd.Questo ha a che vedere con certe caratteristiche tecniche della codifica MP3.

:edl.


.*-------------------------------------------------------------------------
.*fold00.*The tag information display

:h3 id=taginfo res=2130.Il visualizzatore di informazioni sul contrassegno
:fn id=boc.
:p.Si trova nell'album "Imaginos" dei Blue &Oe.yster Cult.
:efn.
:fn id=sid.
:p.Estratto dal testo di "Shut it down", dall'album "Iron fist" dei Mot&oe.rhead.
:efn.
.*-------------------------------------------------------------------------
:p.Questa sezione mostra le informazioni contenute nel contrassegno ID3.
Potete tranquillamente modificare questi valori, od inserirne di nuovi nel caso il brano
non avesse gi… un contrassegno.
Naturalmente solo se il brano non sia in sola lettura come, ad esempio,
quelli marcati read-only, o quelli memorizzati su CD-ROM.

:p.:hp1.Nota&colon.:ehp1. I limiti di lunghezza sono quelli dettati dallo standard dei
contrassegni ID3, quindi non prendetevela con me se non riuscite ad infilare :link
refid=boc reftype=fn."The siege and investiture of Baron von Frankenstein's
castle at Weisseria":elink. nello spazio del titolo...

:dl break=all tsize=5.

:dt.:hp2.Titolo:ehp2.
:dd.Il titolo della canzone, o di qualunque frammento audio il brano contenga.
Pu• essere lungo fino a 30 caratteri.

:dt.:hp2.Artista:ehp2.
:dd.Mozart, Black Sabbath, Bananarama, un gatto che abbaia... ci siamo capiti.
Pu• essere lungo fino a 30 caratteri.

:dt.:hp2.Album:ehp2.
:dd.L'album di provenienza di questa canzone (o altro). Se il brano non Š di
pertinenza di alcun album o simili, potete anche lasciare in bianco questo spazio.
Altra riga con un limite massimo di 30 caratteri.

:dt.:hp2.Anno:ehp2.
:dd.La data della registrazione, di pubblicazione, del primo posto in classifica, o
qualunque cosa pensiate ci si possa infilare. Anche in lettere dato che, pur nel limite
dei 4 caratteri, non c'Š una restrizione ai soli numeri. Chiss… a cosa potrebbe servire...

:dt.:hp2.Genere:ehp2.
:dd.Il tipo di musica. Selezionarne uno dall'elenco. Non ho idea di chi "inventi"
questi generi. Sembra ci sia un certo accordo "di fatto" al loro riguardo, quindi
non chiedetemi di aggiungerne o toglierne qualcuno. Comunque, volendo, potete farlo
voi direttamente.
(vedi anche :link refid=genresfile reftype=hd.l'elenco dei generi:elink.).

:dt.:hp2.Commento:ehp2.
:dd.Scrivere un commento. Non sul programma, ovviamente, ma sul brano MP3.
Massimo 30 charatteri (solo 28 se si usa anche l'indicatore "Traccia #"). La solita
storia&colon. :link refid=sid reftype=fn.I just wanna shut it down:elink..
:p.:hp1.Nota&colon.:ehp1. Qui si possono usare delle macro, che saranno automaticamente
rimpiazzate dai valori appropriati al momento della registrazione del contrassegno. (Utilizzabile
anche con la funzione "Scrivi su tutti")&colon.
:ul compact.
:li.$T - Titolo
:li.$A - Artista
:li.$a - Album
:li.$Y - Anno
:li.$G - Genere
:li.$v - Versione MPEG
:li.$l - Livello
:li.$t - Durata prevista
:li.$m - Modo
:li.$f - Frequenza (di campionamento)
:li.$b - Bitrate
:li.$r - Traccia
:eul.
:p.:hp1.Esempio&colon.:ehp1. se inserite "Durata=$t, Modo=$m" e registrate, il commento
diverr… qualcosa tipo "Durata=03&colon.14, Modo=Stereo".

:dt.:hp2.Traccia #:ehp2.
:dd.Qui si pu• scegliere, od inserire direttamente a mano, il numero di traccia della
canzone (ad esempio se proveniente da un CD, o simili).
:p.:hp1.Nota&colon.:ehp1. Questa Š una estensione all'ID3 versione 1.0 (Š la v1.1).
Se si inserisce 0 (zero), il contrassegno risultante sar… in versione 1.0;
se si sceglie un altro valore, il contrassegno verr… creato in versione 1.1 Il numero
di traccia Š memorizzato negli ultimi due byte (caratteri) del commento, quindi
il commento
potr… essere di soli 28 caratteri. Se ne inserite uno di 29 o 30, questo sar…
automaticamente troncato a 28 in fase di scrittura.
:edl.


.*-------------------------------------------------------------------------
.*fold00.*The push buttons + menu

:h3 id=buttons res=2140.I pulsanti ed il menu
:dl break=all tsize=5.
:dt.:hp2.Apri...:ehp2.
:dd.Fa apparire la finestra che permette di selezionare i brani che si desidera
aggiungere alla :link refid=filelist reftype=hd.lista dei brani selezionati:elink..

:dt.:hp2.Apri gruppo...:ehp2. (solo da menu)
:dd.Richiama la finestra per l':link refid=autoopenwindow reftype=hd.Apertura
Automatica:elink., che permette di selezionare la cartella che dovr… essere esplorata
in cerca di brani MP3 da aggiungere alla :link refid=filelist reftype=hd.lista dei
brani selezionati:elink.. La ricerca avverr… anche nelle sottocartelle.

:dt.:hp2.Togli dalla lista:ehp2. (solo da menu)
:dd.Serve ad eliminare il brano corrente dalla :link refid=filelist reftype=hd.lista
dei brani selezionati:elink..

:dt.:hp2.Togli tutti dalla lista:ehp2. (solo da menu)
:dd.Elimina tutti i brani dalla :link refid=filelist reftype=hd.lista dei brani
selezionati:elink..

:dt.:hp2.Cambia nomi...:ehp2. (solo da menu)
:dd.Apre la finestra per la :link refid=renamewindow reftype=hd.ridenominazione
automatica:elink.. Questa funzione permette di cambiar nome a tutti i brani in modo
semiautomatico, usando una maschera e delle macro come schema di base
per generare i nomi da usare.

:dt.:hp2.Lista...:ehp2.
:dd.Richiama la funzione :link refid=listwindow reftype=hd.Crea Lista:elink., che
consente di generare un elenco di tutti i brani selezionati. Si pu• anche decidere quali
delle informazioni contenute nel contrassegno debbano effettivamente apparire.

:dt.:hp2.Esci:ehp2.
:dd.Come potreste aver gi… intuito, questa voce consente l'uscita dal programma.
Considerate che non Š prevista richiesta di conferma; quindi meglio ricordarsi di registrare
ci• che non si vuol perdere...

:dt.:hp2.Registra:ehp2.
:dd.Registra come contrassegno del solo brano corrente i dati attualmente visualizzati nella zona
delle :link refid=taginfo reftype=hd.informazioni sul contrassegno:elink..

:dt.:hp2.Registra &amp. successivo:ehp2. (solo da menu)
:dd.Registra il contrassegno corrente e passa al brano successivo della lista.

:dt.:hp2.Registra &amp. precedente:ehp2. (solo da menu)
:dd.Registra il contrassegno corrente e passa al brano precedente della lista.

:dt.:hp2.Scrivi su tutti:ehp2.
:dd.Usa i dati attualmente contenuti nella zona delle :link refid=taginfo reftype=hd.informazioni sul contrassegno:elink.
come origine per i dati da inserire nei contrassegni
di tutti i brani della :link refid=filelist reftype=hd.lista:elink..
:p.Se si lasciano una o pi— righe in bianco (cioŠ assolutamente :hp1.vuote:ehp1.; nemmeno
spazi, nulla!), in caso in un contrassegno siano gi… presenti dei dati, questi non saranno
toccati.
Per la riga di Genere, si ottiene lo stesso effetto selezionando "(nessuno)".

:dt.:hp2.Rimuovi:ehp2.
:dd.Elimina il contrassegno dal brano attualmente selezionato. Sempre che abbia uno, altrimenti
questo comando apparir… inattivo. Non molto utile se usato per recuperare spazio libero
su disco, dato che accorcia i brani di soli 128 caratteri...

:dt.:hp2.Rimuovi da tutti:ehp2.
:dd.Elimina permanentemente il contrassegno da tutti i brani selezionati nella :link
refid=filelist reftype=hd.lista:elink.. Maneggiare con cura!

:dt.:hp2.Suona brano:ehp2. (solo da menu)
:dd.Suona il brano corrente usando il vostro lettore MP3 preferito.
Per maggiori informazioni, vedi i :link refid=playercmdfiles reftype=hd.comandi .CMD per il
lettore:elink..

:dt.:hp2.Mostra i pulsanti:ehp2. (solo da menu)
:dd.Mostra, se nascosti, o nasconde, se visibili, i pulsanti sul lato destro della
finestra.

:dt.:hp2.Mostra le informazioni sul brano:ehp2. (solo da menu)
:dd.Mostra, se nascosto, o nasconde, se visibile, il :link refid=fileinfo reftype=hd.
visualizzatore di informazioni sul brano:elink..

:dt.:hp2.Indice...:ehp2. (solo da menu)
:dd.Richiama l'indice generale dell'aiuto.

:dt.:hp2.Aiuto (da menu&colon. Contesto...):ehp2.
:dd.Richiama l'aiuto contestuale.

:dt.:hp2.Minta...:ehp2.
:dd.Mostra informazioni generali su &progname.&colon. la versione che state usando, come
raggiungere gli autori, e roba del genere...

:edl.


.*-------------------------------------------------------------------------
.*fold00.*The settings window

:h2 id=settingswindow res=2200.La finestra delle impostazioni
:p.La finestra delle impostazioni permette di cambiare ed adattare varie cose secondo i
vostri gusti. Ad esempio se volete che &progname. vi avvisi del verificarsi alcuni eventi
(tipo l'aggiunta di brani alla :link refid=filelist reftype=hd.lista:elink.), o
quale lingua preferiate usare.

:p.Spingendo il pulsante "Ok" in basso, la finestra si chiuder… e le impostazioni saranno
rese attive. Con il pulsante "Annulla modifiche" si riporta allo stato precedente la sola sottopagina corrente.
Il pulsante "Aiuto" porta ad una pagina di spiegazioni per le scelte attualmente visualizzate.

:p.La finestra delle impostazioni ha la seguente struttura&colon.
:ul compact.
:li.:link refid=notification reftype=hd.Avvisi:elink.
:li.:link refid=keepinfo reftype=hd.Informazioni da mantenere:elink.
:li.:link refid=misc reftype=hd.Varie:elink.
:li.:link refid=language reftype=hd.Lingua:elink.
:eul.


.*-------------------------------------------------------------------------
.*fold00.*Notification

:h3 id=notification res=2210.La pagina degli Avvisi
:p.In questa pagina potete decidere di quali eventi &progname. debba avvertirvi,
ed in qual modo debba farlo.
.* In questa pagina potete scegliere gli eventi dei quali volete essere avvisati, ed in qual
.* modo &progname. debba farlo.

:dl break=all tsize=5.

:dt.:hp2.Avverti quando...:ehp2.
:dd.Qui potete selezionare gli eventi dei quali volete essere avvisati. Direi che il tutto
sia abbastanza autoesplicativo.

:dt.:hp2.Tipo di segnalazione:ehp2.

:dd.Scelta del metodo da usare&colon.
:ul.
:li."Pulsante normale" mostrer… un messaggio con un pulsante "Ok" da premere.
:li."Avviso a scomparsa automatica" mostrer… un avviso che sparir… automaticamente
dopo qualche secondo. Volendo, ci si pu• anche fare clic col mouse per farlo sparire prima.
:li."Suono" emetter… semplicemente tre brevi note dall'altoparlante interno dell'elaboratore.
:eul.

:edl.


.*-------------------------------------------------------------------------
.*fold00.*Keep info

:h3 id=keepinfo res=2220.La pagina delle informazioni da mantenere
:p.In questa pagina potete decidere se, e quali, informazioni debbano essere mantenute
anche nel contrassegno successivo quando si cambia brano usando ALT+'s' od ALT+'p'.

:dl break=all tsize=5.

:dt.:hp2.Mantieni informazioni al cambio di brano:ehp2.
:dd.Marcare questo bottone se si desidera usare la funzione di mantenimento
informazioni. Se non attivato, ad ogni cambio di brano il contrassegno del successivo
mostrer… solo le informazioni gi… inserite e memorizzate in precedenza.

:dt.:hp2.Mantieni...:ehp2.
:dd.Qui si pu• scegliere quali parti del contrassegno debbano essere riportate anche nel
successivo.
Abbastanza autoesplicativo, immagino.

:dt.:hp2.Opzioni:ehp2.
:dd.Alcune opzioni per la funzione "mantieni informazioni".
:ul.
:li."Incrementa / decrementa numero di traccia" - Se attivato, il numero di traccia verr…
automaticamente incrementato o decrementato passando al brano successivo o precedente.

:li."Mantieni le informazioni solo se non gi… presenti" - Attivandolo, le informazioni
selezionate saranno mantenute solo se non esistenti nel contrassegno del nuovo brano (cioŠ la
riga sia vuota, il numero di traccia sia zero od il genere sia "Nessuno"). Eventuali
informazioni gi… presenti non verrebbero cambiate.
:eul.
:edl.
:p.:hp1.Esempio&colon.:ehp1. Avete scelto "Titolo" ed "Artista" nel gruppo "Mantieni..."
ed Š attivo "Mantieni le informazioni solo se non gi… presenti" (oltre naturalmente a
"Mantieni informazioni al cambio di brano").
Il Titolo del brano corrente Š "I wish you were a beer" e l'Artista "Cycle Sluts from Hell".
Premete ALT+'s' (o selezionate "Registra &amp. successivo" dal menu "Contrassegno").
Il nuovo brano ha gi… un Titolo (diciamo "Dark Ships") ma nessun Artista. Le informazioni
nelle righe del nuovo brano saranno ora&colon. "Dark Ships" nello spazio del Titolo e
"Cycle Sluts from Hell" in quello per l'Artista.
:p.Se, nell'esempio precedente, non aveste selezionato "Mantieni le informazioni solo se non
gi… presenti", il Titolo per il nuovo brano ora sarebbe "I wish you were a beer".
:p.Hmmm... Spero che capire come funzioni sia molto meno complicato di quanto sia stato il
programmarlo ;-)
[ed il tradurlo... N.d.T.]

:p.:hp1.Nota&colon.:ehp1. se, usando "Mantieni Informazioni", si raggiunge un brano
marcato in sola lettura o che abbia gi… dei dati in una riga e "Mantieni le
informazioni solo se non gi… presenti" Š attivo, &progname. non mantiene i dati del brano
iniziale e, d'ora in poi, user… quelle di QUESTO brano.
Questo comportamento verr… probabilmente corretto in una prossima versione.


.*-------------------------------------------------------------------------
.*fold00.*Misc

:h3 id=misc res=2230.La pagina Varie
:p.In questa pagina si possono impostare varie opzioni.

:dl break=all tsize=5.

:dt.:hp2.Leggi i generi da...:ehp2.
:dd.Inserire qui il nome dell'archivio (in formato testo) da cui &progname. legger…
i nomi dei generi. Per altre informazioni vedi l':link refid=genresfile reftype=hd.elenco dei generi:elink..

:dt.:hp2.Comando per avviare un riproduttore esterno:ehp2.
:dd.Inserire il nome del comando da usare per far partire un lettore di MP3 esterno
quando si usa "Suona brano" dal :link refid=buttons reftype=hd.menu:elink. "Extra"
della :link refid=mainwindow reftype=hd.finestra principale:elink..
Inserire $f nel punto in cui inserire il nome del brano.

:p.:hp1.Nota&colon.:ehp1. Per ragioni tecniche si deve usare un .CMD per lanciare
il riproduttore; chiamare direttamente il .EXE potrebbe non funzionare.
Nella distrubuzione di &progname. ho incluso dei :link refid=playercmdfiles reftype=hd.CMD
gi… predisposti per i pi— comuni lettori MP3:elink. per OS/2.
In caso, modificate quello che pi— si adatta alla vostra configurazione. Potete farlo
con un qualunque programma capace di registrare in formato testo.

:p.:hp1.Esempio&colon.:ehp1. se volete usare PM123 per suonare i vostri brani,
inserite "goPM123 $f".

:dt.:hp2.Altre opzioni:ehp2.
:dd.Impostazione di altre opzioni assortite&colon.
:ul.

:li."Se assente, usa come Titolo il nome fisico del brano" - Se abilitato, e sempre che il
brano non ne abbia gi… uno, &progname. inserisce automaticamente il nome fisico (su disco)
del brano nella riga Titolo delle :link refid=taginfo reftype=hd.informazioni sul
contrassegno:elink.

:li."Usa finestra di apertura personalizzata" - Se abilitato, &progname. user… la propria
finestra personalizzata. (che, a mio parere, Š pi— carina di quella standard).

:li."Non avvisare in caso di brani difettosi" - &progname. talvolta non riesce a decodificare
la testata di un brano MP3 (alcuni brani hanno delle testate :hp1.veramente:ehp1. strane)
ed assume che l'archivio non sia un brano MP3 valido (ovviamente ci• accade anche se
:hp1.veramente:ehp1. non si tratta di un brano MP3!).
Se vi capitano molti brani di questo tipo, potete disabilitare l'avvertimento che &progname.
mostra in questi casi.

:li."Usa caratteri pieni anche per i brani in sola lettura" - Di solito se il brano attuale
Š marcato in sola lettura, &progname. disabilita, rendendole grigie, tutte le righe
della zona delle :link refid=taginfo reftype=hd.informazioni sul contrassegno:elink..
Visto che ci• talvolta le rende difficili da leggere, abilitando questa opzione si indica
a &progname. di rendere semplicemente non modificabili queste righe, ma senza schiarirle.

:eul.
:edl.


.*-------------------------------------------------------------------------
.*fold00.*Language

:h3 id=language res=2240.La pagina della Lingua
:p.In questa pagina potete scegliere la lingua di &progname.. Si pu• indicarne
una qualunque fra quelle mostrate nella lista.

:p.:hp1.Nota&colon.:ehp1. Se si sceglie una lingua diversa dall'attuale, questa non
cambier… sino al successivo riavvio del programma.

:p.:hp1.Nota&colon.:ehp1. Se volete tradurre &progname. in un'altra lingua,
siete i benvenuti! Vedi ":link refid=helpwanted reftype=hd.Richiesta di aiuto!:elink."
per altre informazioni.


.*-------------------------------------------------------------------------
.*fold00.*The list window
:h2 id=listwindow res=2300.La finestra della Lista
:p.Questa finestra vi permette di ottenere una lista di tutti i brani selezionati.
La lista conterr… una riga per ogni brano.

:dl break=all tsize=5.

:dt.:hp2.Archivio, &amp. pulsante "Seleziona...":ehp2.
:dd.Inserire qui il nome dell'archivio di destinazione.
Il pulsante "Seleziona..." apre una finestra che permette di specificare il nome pi—
facimente.

:dt.:hp2.Informazioni da inserire:ehp2.
:dd.Potete decidere quali dati del contrassegno debbano confluire nella lista.
Selezionarne almeno uno...
:p.Per ora non Š possibile cambiare l'ordine dei dati. (Magari in una prossima versione).

:dt.:hp2.Testata:ehp2.
:dd.Selezionando questo bottone, la lista conterr… una riga con le intestazioni delle
colonne.

:dt.:hp2.Durata totale:ehp2.
:dd.Selezionando questo bottone, alla fine della lista viene aggiunto il tempo totale;
ottenuto sommando quelli di tutti i brani elencati.

:dt.:hp2.Larghezza colonne automatica:ehp2.
:dd.Selezionando questo bottone, le colonne verranno dimensionate in base al pi— lungo
dei dati presenti. Se il bottone non Š selezionato, viene usata la massima larghezza
possibile per la specifica colonna.

:p.:hp1.Nota&colon.:ehp1. Se inserite anche "Nome &amp. Cartella", questa colonna verr…
sempre dimensionata automaticamente. Non penso sarebbe carino farla sempre da 256
caratteri, che Š la lunghezza massima di un nome HPFS.
:p.
Si prega anche di notare che attivando quest'opzione quasi si raddoppia il tempo di creazione
della lista. Ci• perch‚ &progname. deve prima analizzare tutti i brani per trovare la
larghezza giusta. (Fa eccezione la colonna "Nome &amp. Cartella", dove la larghezza Š
gi… calcolata al momento dell'inserimento
nell':link refid=filelist reftype=hd.elenco dei brani selezionati:elink.).

:dt.:hp2.Solo brani con contrassegno:ehp2.
:dd.Selezionando questo bottone, in lista vengono inseriti solo i brani
che possiedono un contrassegno ID3; gli altri sono semplicemente ignorati.

:dt.:hp2.Crea:ehp2.
:dd.Genera la lista e la scrive su disco.

:dt.:hp2.Annulla:ehp2.
:dd.Chiude la finestra senza compiere alcuna azione.

:dt.:hp2.Aiuto:ehp2.
:dd.Mostra questa pagina di aiuto.

:edl.

.*-------------------------------------------------------------------------
.*fold00.*The renaming window
:h2 id=renamewindow res=2500.La finestra per ridenominare i brani
:p.Questa finestra permette di ridenominare tutti i brani della lista usando come matrice
una maschera personalizzabile.

:dl break=all tsize=5.

:dt.:hp2.Maschera:ehp2.
:dd.Questa riga contiene la maschera di ridenominazione. Potete inserire qualunque
combinazione di testo e macro: il nome fisico di tutti i brani verr… cambiato in base a
questa maschera. In caso di un nome gi… esistente, viene usato lo stesso nome con l'aggiunta
di un numero.

:p.Sono disponibili le seguenti macro, che verranno automaticamente rimpiazzate dai
corrispondenti valori&colon.
:ul compact.
:li.$T - Titolo
:li.$A - Artista
:li.$a - Album
:li.$Y - Anno
:li.$G - Genere
:li.$C - Commento
:li.$v - Versione MPEG
:li.$l - Livello
:li.$t - Durata prevista
:li.$m - Modo
:li.$f - Frequenza di campionamento
:li.$b - Bitrate
:li.$r - Traccia
:eul.
:p.:hp1.Esempio&colon.:ehp1. Se come maschera inserite "($A)-$T"  ed il Titolo del primo
brano Š "Eat the Rich" dei "Mot&oe.rhead", il nuovo nome fisico del brano sar…&colon.
"(Mot&oe.rhead)-Eat the Rich.mp3".
:p.:hp1.Nota&colon.:ehp1. Tutti i caratteri non ammessi dallo standard per i
nomi HPFS ("*", "?", etc.) vengono convertiti in "_" prima di essere registrati.

:dt.:hp2.Limita la lunghezza dei nomi a non pi— di...:ehp2.
:dd.Questo servizio viene in aiuto specialmente quando si realizzano dei CD, dove la
struttura per registrazione adottata (il "filesystem") potrebbe ad esempio non ammettere nomi pi— lunghi
di 31 caratteri&colon. i nomi, compresa l'estensione, sono troncati automaticamente alla lunghezza data.

:dt.:hp2.Sostituisci gli spazi con sottolineature (trattino basso):ehp2.
:dd.Se non vi piacciono gli spazi nei nomi dei vostri brani, attivate la funzione e
questi saranno sostituiti dal carattere "_".

:dt.:hp2.Cambia i nomi:ehp2.
:dd.Procura ricchezza, celebrit… ed eterna giovinezza!
Beh, non esattamente. (Altrimenti &progname. di sicuro non sarebbe gratis...). Questo
pulsante avvia il processo di ridenominazione.

:dt.:hp2.Annulla:ehp2.
:dd.Se ci toccate il vostro zaino, toglie ogni potere magico a tutti gli oggetti che vi sono contenuti.

.* Will remove the curse from all items in your pack if you zap yourself
.* with it.            questa e' la storia della bacchetta magica
.*
.* It refers to the classic game "Nethack". There is a "Wand of
.* >Cancellation", that will remove the magic (and often other) powers
.* >from all things (items or creatures) that are zapped with this
.* >wand. This may be used to defend yourself against many strong
.* >monsters, as they will lose their special attacks, but will generally
.* >be a bad thing if you zap yourself (and your equipment) with the
.* >wand - the only positive thing of this is, that all your cursed items
.* >(normally a rather bad thing) will become uncursed too.


:p.No, un attimo, documentazione errata! Questo pulsante chiude la finestra, e nient'altro...


:dt.:hp2.Aiuto:ehp2.
:dd.Genera un coro di urla "Aiuto! Aiuto!" su tutte le uscite sonore disponibili.
O una roba del genere...

:edl.
:p.:hp1.Nota&colon.:ehp1. Questa funzione fallir… orribilmente (cioŠ mostrer… un messaggio
d'errore...) se il nome risultasse troppo lungo per la struttura di registrazione usata
(ad esempio su un disco FAT, dove si possono avere nomi lunghi al massimo 8 caratteri).


.*-------------------------------------------------------------------------
.*fold00.*The autoopen window
:h2 id=autoopenwindow res=2400.La finestra per l'Apertura Automatica
:p.Questa finestra permette di selezionare la cartella dove cercare i brani MP3.

.*-------------------------------------------------------------------------
.*fold00.*Commandline arguments
:h1 id=cmdlineargs res=3000.Parametri da riga di comando
:p.Il primo parametro accettato da &progname. Š un nome di brano o di cartella.
Ci• permette di specificare il brano da caricare o la cartella in cui cercare i brani, sia
da riga di comando sia in sede di associazione a &progname. dei brani MP3 via WPS.

:p.:hp1.Esempio:ehp1. Scrivendo "minta c&colon.\mp3" sulla riga di comando,
&progname. cercher… i brani MP3 nella cartella "c&colon.\mp3" (sempre che sia una cartella,
naturalmente ;-) e la finestra principale apparir… con tutti i brani trovati gi… aggiunti
alla :link refid=filelist reftype=hd.lista dei brani selezionati:elink..

:p.Il secondo argomento utilizzabile Š "-f". Per qualche ragione WarpAMP
ha dei problemi a mostrare le informazioni quando, come sarebbe normale, le zone inutilizzate
dei contrassegni MP3 sono riempite di zeri ma preferisce trovare degli spazi. Usando
questo parametro anche &progname. user… spazi invece di zeri.

:p.Un altro parametro Š "-t", che dice a &progname. di usare sempre due cifre per il numero
di traccia (il che significa, se necessario, premettere uno zero) quando ridenomina dei brani.

:p.Ultimo parametro Š "-i<percorso>", che indica a &progname. di cercare il proprio archivio
INI non nella cartella di partenza ma in quella indicata da "percorso".

.*-------------------------------------------------------------------------
.*fold00.*Tips + tricks
:h1 id=tipstricks res=4000.Trucchi &amp. suggerimenti
:p.In questa sezione trovate alcuni trucchi ed idee per risparmiare lavoro o
semplificare alcune cose usando &progname..

:dl break=all tsize=5.

:dt.:hp2.Marcatura di interi album - L'approccio "Scrivi su tutti":ehp2.
:dd.Un sistema per marcare interi album senza dover inserire un sacco di volte gli stessi
dati, Š quello di usare la funzione "Scrivi su tutti"&colon.
:ol compact.
:li.Caricare tutti i brani MP3 dell'album
nella :link refid=filelist reftype=hd.lista dei brani selezionati:elink.. Se tenuti tutti
insieme in una cartella si pu• usare direttamente la funzione
:link refid=buttons reftype=hd.Apri gruppo:elink..
(Per essere certi che nella lista non ci siano gi… altri brani, usare prima
"Togli tutti dalla lista"!)
:li.Inserire Artista, Album, Anno (e, se possibile, il Genere) negli appositi spazi
del :link refid=taginfo reftype=hd.visualizzatore di informazioni sul contrassegno:elink..
Controllate che il resto dei dati sia vuoto (o "0", o "(nessuno)").
:li.Se si vogliono cose come durata o simili nel commento di ogni brano, usare
le appropriate :link refid=taginfo reftype=hd.macro:elink. nello spazio del Commento.
:li.Spingere il pulsante "Scrivi su tutti", o la stessa voce del menu "Contrassegno".
Accettare con "Ok" la richiesta che appare. A questo punto i dati che avete inserito
verranno registrati in tutti i brani.
:li.Scegliete il primo brano dalla :link refid=filelist reftype=hd.lista dei brani
selezionati:elink. ed inserite le informazioni mancanti (Titolo, numero di Traccia, etc.).
:li.Al termine usare, usare ALT+'s' per avanzare al brano seguente e via via a tutti quelli
successivi.
:eol.

:dt.:hp2.Marcatura di interi album - L'approccio "Mantieni informazioni":ehp2.
:dd.L'altro modo di marcare facilmente interi album Š quello di usare la funzione
"Mantieni informazioni al cambio di brano"&colon.
:ol compact.
:li.Aprire la :link refid=settingswindow reftype=hd.finestra delle Impostazioni:elink.
(scegliendo "Impostazioni..." dal menu "Brano") ed andare alla pagina "Informazioni da
mantenere".
:li.Attivare (se non gi… attiva) "Mantieni informazioni al cambio di brano". Nel gruppo
"Mantieni..." scegliere "Artista", "Album", "Anno" e, se opportuno, anche "Genere" e
"Commento". Volendo inserire il numero di traccia in ogni brano, attivare anche
"Incrementa / decrementa numero di traccia".
Disattivare, se ce ne fossero di attivi, tutti gli altri bottoni della pagina.
:li.Chiudere la pagina usando il pulsante "Ok".
:li.Caricare tutti i brani MP3 appartenenti all'album nella :link refid=filelist reftype=hd.lista dei brani selezionati:elink..
In caso siano gi… tutti insieme in una cartella, si pu•
usare direttamente la funzione :link refid=buttons reftype=hd.Apri gruppo:elink..
(Verificate che in lista non ci siano altri brani! Usare prima&colon. "Togli tutti
dalla lista")
:li.Inserire Titolo, Artista, Album, Anno e, se possibile, Genere del primo brano negli
spazi appropriati del :link refid=taginfo reftype=hd.visualizzatore di informazioni sul
contrassegno:elink..
:li.Se nel commento di ogni brano si vogliono cose come durata e simili, usare
le appropriate :link refid=taginfo reftype=hd.macro:elink. nello spazio del Commento.
:li.Se si vuole inserire il numero di traccia in ogni brano, impostare "Traccia #" a 1.
:li.Usare ALT+'s' (o "Registra &amp. successivo" dal menu "Contrassegno") per passare al prossimo
brano. Riempire con le informazioni mancanti e procedere continuando ad usare
ALT+'s' per scorrere tutti i brani in lista ed inserire i dati appropriati.
:eol.
:edl.
:p.Una utile caratteristica che si pu• usare con il secondo approccio, Š quella di attivare
"Se assente, usa come Titolo il nome fisico del brano" nella pagina ":link refid=misc reftype=hd.Varie:elink."
delle :link refid=settingswindow reftype=hd.Impostazioni:elink..
Se i vostri brani hanno gia un nome fisico molto simile al titolo
effettivo (tipo "I_WISH_YOU_WERE_A_BEER.MP3"), tutto ci• che vi rimane da fare Š solo, eventualmente,
adattare il Titolo di ogni brano.

.*-------------------------------------------------------------------------
.*fold00.*Past, present + future
:h1 id=pastpresentfuture res=5000.Passato, presente &amp. futuro
:p.Questa sezione contiene indicazioni sulla storia di &progname.; alcune informazioni
su (e sui problemi) della versione corrente, e cose che potrebbero essere aggiunte
o cambiate in futuro.


.*-------------------------------------------------------------------------
.*fold00.*Version history
:h2 id=history.Cronologia :p.Questa pagina contiene l'elenco dei
cambiamenti nelle varie versioni del programma.


:dl break=all tsize=5.

:dt.:hp2.Versione 2.50:ehp2.
:dd.No, non Š ancora la "Prossima versione Importante" &colon.-)
:ul compact.
:li.Traduzione in Italiano di programma ed aiuto in linea. Molte grazie ad Alberto Gabrielli!!
:li.Varie piccole correzioni e miglioramenti. Di nuovo, un ringraziamento speciale ad Alberto Gabrielli!
:eul.

:dt.:hp2.Versione 2.45:ehp2.
:dd.Causa il mio tempo limitato, la prossima versione "importante" potrebbe tardare
un pochino.
Intanto ho deciso di farne una che corregga alcuni problemini ed aggiunga qualche piccola
funzione.
:ul compact.
:li.Aggiunto un :link refid=cmdlineargs reftype=hd.parametro da riga di comando:elink. per
dire a &progname. di premettere uno zero al numero di traccia quando si ridenomina.
:li.Aggiunto un :link refid=cmdlineargs reftype=hd.parametro da riga di comando:elink. per
indicare a &progname. dove cercare il proprio archivio INI.
:li.Aggiunto un :link refid=cmdlineargs reftype=hd.parametro da riga di comando:elink. per
dire a &progname. di non generare errori se la modifica dell'attributo LONGNAME fallisce.
(pur funzionando la ridenominazione, su alcune configurazioni questa funzione riporta ancora
un errore).
:li.Nel menu, cambiato "Cancella" in "Togli dalla lista". Ora suona meno "pericoloso" &colon.-)
:li.Errore corretto&colon. Quando si ridenomina, se il nuovo nome Š uguale a quello vecchio,
&progname. non prova pi— a ridenominarlo comunque (col risultato di aggiungere inutilmente un
numero al nome).
:li.L'associazione WPS dei brani MP3 a &progname. ora funziona di nuovo.
(Avevo cambiato il parser della linea di comando, e questo ha causato il problema)
:li.Se &progname. viene lanciata da una cartella esterna, ora cerca di caricare tutte le sue
componenti (*.dll, *.hlp, *.ini, generi...) dalla cartella ove risiede il suo eseguibile.
:eul.

:dt.:hp2.Versione 2.41:ehp2.
:dd.Altre traduzioni, e piccole cosette...
:ul compact.
:li.Supporto per la lingua Francese.
:li.Supporto per la lingua Norvegese. (non ancora completo)
:li.Supporto per la lingua Russa. (solo programma)
:li.Quando si ridenominano i brani, anche l'attributo esteso ".LONGNAME" viene corretto.
:li.Ridenominando, si pu• usare anche il numero di traccia.
:eul.


:dt.:hp2.Versione 2.27:ehp2.
:dd.Due correzioni - una per &progname., ed una per... ;-)
:ul compact.
:li.Le informazioni tecniche MP3 sono di nuovo mostrate correttamente.
:li.&progname. ora pu• usare spazi invece di zeri per riempire i campi. Questo corregge un
problema di WarpAMP (vedi i :link refid=cmdlineargs reftype=hd.parametri da riga di
comando:elink.)
:eul.

:dt.:hp2.Versione 2.25:ehp2.
:dd."It's about time the played something cool!" [MTV, N.d.T.] - Gi…, ed ecco quindi la v2.25!
Le nuove carattereistiche comprendono&colon.

.* :dd."It's about time the played something cool!" - Gi…, ed ecco quindi la v2.25!
.* >No, it's a quote from the MTV series "Beavis and Butthead". Every
.* >time a music video they consider good comes on, they utter this
.* >sentence :-)

:ul compact.
:li.Supporto per la lingua Olandese.
:li.Ridenominazione automatica avanzata. (cambia i nomi usando una maschera; macro;
limite di lunghezza sui nomi generati; scelta se rimpiazzare gli spazi con trattini bassi).
:li.I contrassegni ID3 v2.x ora vengono individuati e saltati correttamente. (spiacente,
ma visione e modifica devono ancora arrivare...)
:li.Migliore finestra di apertura, ora con supporto del tipo di brano.
:li.Alcuni cambiamenti interni sul codice.
:li.Qualche problemino sistemato. (Cose cos piccole da non essere state notate da nessuno,
o semplici problemi estetici).
:eul.

:dt.:hp2.Versione 2.00:ehp2.
:dd.Causa l'infinita creativit… dei beta tester, suggerimenti da parte degli utenti e miei
desideri personali, &progname. ora comprende le seguenti nuove funzioni&colon.
:ul compact.
:li.Come gi… promesso per la precedente versione, ora &progname. carica i generi da un
archivio sezionabile e modificabile dall'utente. Come formato &progname. accetta il proprio,
ma pu• anche caricare il "genres.txt" di WarpAMP. Vedi ":link refid=genresfile reftype=hd.l'elenco dei generi:elink."
per altre informazioni.
:li.Se un brano non ha dati nel campo "Titolo", ora &progname. pu• usare automaticamente
il nome fisico come titolo.
:li.Ora &progname. accetta un nome di brano (o di cartella) come :link
refid=cmdlineargs reftype=hd.parametro da linea di comando:elink..
Questo permette sia di specificare da linea di comando il brano da caricare o la cartella in
cui cercare i brani, sia di associare a &progname. i brani MP3 via WPS.
:li.&progname. ora supporta altre lingue (beh, per ora solo Tedesco ed Inglese).
:li.Si possono trascinare brani o cartelle sulla finestra di &progname. per aggiungerli
alla :link refid=filelist reftype=hd.lista dei brani selezionati:elink. o far cercare i brani
da aggiungere alla lista.
:li.Dall'interno di &progname. si pu• facimente lanciare un lettore MP3 di propria scelta,
e passargli il brano corrente.
:li.Cambiando brano, ora si pu• specificare che certe informazioni del contrassegno debbano
essere mantenute nel prossimo brano (utile, ad esempio, per marcare interi album).
:li.In caso di brano in sola lettura, &progname. ora rende i campi del :link refid=taginfo
reftype=hd.visualizzatore di informazioni sul contrassegno:elink. semplicemente di sola lettura
invece che disabiltati (grigi). Talvolta riusciva difficile leggerli.
:li.Si pu• scegliere fra tre diversi stili per gli avvisi.
:li.Ora Š possibile disabilitare l'avvertimento di "Brano MP3 non valido".
:li.La ridenominazione automatica ora pu• limitare i nomi ad un massimo di 31 caratteri.
(utile quando si creano certi CD-ROM con limite a 31)
:li.Migliorato ed esteso la documentazione e l'aiuto in linea.
:li.Corretti alcuni malfunzionamenti (il brano attuale non veniva chiuso se si usava "Rimuovi
da tutti"; un piccolo problema nella finestra "Seleziona cartella..."; &progname. che si
chiudeva elencando brani con genere non valido...)
:eul.

:dt.:hp2.Versione 1.67:ehp2.
:dd.Cambiate/aggiunte le seguenti cose&colon.
:ul compact.
:li.&progname. ora supporta anche i contrassegni ID3 v1.1.
:li.Ora si possono inserire nella lista anche Versione, Livello, Campionamento, Bitrate e
Modo.
:li.Aggiunta la funzione di auto ridenominazione (permette di ridenominare tutti i brani in
base al relativo Titolo.
:li.Si possono usare macro nel campo Commento per inserire automaticamente la durata ed
altro.
:li.A scelta si possono nascondere (e di nuovo mostrare) i pulsanti e/o la finestra di
informazioni.
:li.Finestra Impostazioni, dove abilitare/disabilitare i vari messaggi di notifica.
:li.Colori e caratteri della finestra principale ora si possono cambiare facimente usando il
trascinamento dalle tavolozze appropriate. Anche questi valori sono memorizzati in &inifile..
:li.Modificata l'icona di &progname. per accordarsi all'icona standard per i brani MP3.
:li.Corretti pochi piccoli errori.
:eul.

:dt.:hp2.Versione 1.45:ehp2.
:dd.Non ci posso credere! Alla fine vive! Finalmente Š finita...
Primo rilascio al pubblico.

:dt.:hp2.Versione 1.44:ehp2.
:dd.Avevo appunto detto "v2.0"...
:ul compact.
:li.Ora quando si eseguono operazioni globali (Scrivi su tutti, etc.) il titolo della finestra
mostra il brano e cartella attualmente elaborati
:li.Aggiunta opzione per scrivere in lista solo i brani con contrassegno.
:li.Rimpiazzata la mia personale (stramba, incompleta, probabilmente bacata) routine
per la decodifica degli header MP3 con quella dei sorgenti
di :link refid=credits reftype=hd.mpg123/2:elink. (un po' modificata).
:li.Ristrutturazione interna di alcune parti del codice.
:li.Sistemati alcuni errori; aggiunti di nuovi; sistemati anche quelli...
:eul.

:dt.:hp2.Versione 1.41:ehp2.
:dd.Non commento. Ma dovrebbero pagarmi per questo...  (Oh no! Ô freeware! ;-)
:ul compact.
:li.Aggiunta la possibilit… di ricerca automatica dei brani nelle (sotto)cartelle.
:li.Aggiunti rilevazione e trattamento dei brani in sola lettura.
:li.Aggiunta l'opzione di auto dimensionamento per le colonne della lista dei brani MP3.
:eul.

:dt.:hp2.Versione 1.34:ehp2.
:dd.Penso che dovr• trovarmi dei beta tester meno esigenti...
:ul compact.
:li.Aggiunta selezione di brani da cartelle multiple.
:li.Aggiunta la possibilit… di scrivere il nome fisico sulla lista.
:li.Aggiunta la barra del menu. (Ormai ci sono abbastanza funzioni da giustificarne una...)
:li.Corretti molti piccoli problemi.
:li.Aggiunto a &inifile. un numero di versione interno per prevenire possibili errori
dovuti all'uso di uno vecchio con nuove versioni di &progname..
:eul.

:dt.:hp2.Versione 1.29:ehp2.
:dd.Ancora una volta i beta tester hanno richiesto l'aggiunta di un'altra funzione, e cos ho
fatto. Se questo andazzo continua, probabilmente &progname. diverr… il primo programma il cui
primo rilascio sar… v2.0! ;-)
:ul compact.
:li.Aggiunta una funzione per ottenere in uscita una lista dei brani selezionati.
:li.Ora anche le opzioni per la lista vengono memorizzate in &inifile..
:li.Rimosso un piccolo errore riguardante i pulsanti della finestra principale.
:eul.

:dt.:hp2.Versione 1.16:ehp2.
:dd.Per via del desiderio di funzioni aggiuntive da parte mia e dei beta tester, sono state
aggiunte le seguenti cose&colon.
:ul compact.
:li.Selezione multipla dei brani.
:li.Rimozione di contrassegni da molti brani in un colpo solo.
:li.Aggiunta globale di contrassegni su molti brani in un colpo solo.
:li.Facile modifica di molti brani uno alla volta.
:li.L'ultima cartella di lavoro (da cui siano stati selezionati dei brani) e la posizione
della finestra principale vengono ora memorizzate in &inifile. e ripristinate alla riapertura
del programma.
:li.Aggiunto uno script di installazione per la creazione dell'oggetto WPS di &progname..
:eul.

:dt.:hp2.Versione 1.00:ehp2.
:dd.Questa versione Š stata solo per i beta tester e non Š mai stata rilasciata al pubblico.

.*Added ... something (yes, it's a secret)
.*:li.When doing lengthly jobs (Save all, Rename all, etc.) &progname. now displays
.*a progress status window and those jobs now have their own thread.

:edl.

.*-------------------------------------------------------------------------
.*fold00.*Bugs

:h2 id=bugs.Problemi conosciuti
:p.Al momento non esistono "veri" problemi. Quelli che seguono sono, pi— o meno, dei
semplici fastidi&colon.

:ul compact.
:li.Cancellando tutti i brani dalla lista dei selezionati, il nome dell'ultimo inserito
rimane visualizzato. Per qualche strano motivo la pulizia di questo campo non funziona.
(Ma funziona altrove! Strano, come ho detto).
:li.Devo ammettere che, come nella maggior parte dei miei programmi, anche &progname. non
funziona bene se, ad esempio con la ridenominazione automatica, si usano percorsi (path)
molto lunghi (> 255 caratteri). Comunque non ho mai visto apparire un simile "mostro",
per ora...
:li.Cambiando il Titolo di un brano, la ridenominazione automatica non lo ridenominer… se il
contrassegno non era stato gi… registrato in precedenza. Ma non so se questo possa realmente
essere definito un errore.
:li.Se, usando "Mantieni Informazioni", si raggiunge un brano marcato in sola lettura o che
abbia gi… dei dati in una riga e "Mantieni le informazioni solo se non gi… presenti" Š
attivo, &progname. non mantiene i dati del brano iniziale e, d'ora in poi, user… quelle di
QUESTO brano.
:li.Talvolta le finestre di avviso non "ereditano" colore e carattere da quella principale.
:li.Il trascinamento (drag&amp.drop) funziona solo se rilasciate gli oggetti in uno spazio libero della
finestra principale. Quindi non uno che sia occupato da bottoni, scritte od altro.
:li."Suona questo brano" richiede un CMD per lanciare il lettore MP3 esterno.
:li.Mi Š stato riferito che questo in WarpAMP Š stato sistemato (Š capitato perch‚
si trovavano in giro due versioni leggermente diverse delle specifiche ID3 v1.1)&colon.
La playlist di WarpAMP talvolta non mostra alcuni dei dati ID3. Ora, visto che altri
programmi (PM123, per citarne uno) mostrano tutto perfettamente ed io non ho idea di cosa
possa esserci di sbagliato nei contrassegni, semplicemente do la colpa a WarpAMP ;-)
:eul.

.*-------------------------------------------------------------------------
.*fold00.*Future enhancements

:h2 id=future.Miglioramenti futuri
:p.Queste funzioni prima o poi (si spera) verranno inserite in &progname.&colon.
:p.:hp2.Piccole cose:ehp2.
:ul compact.
:li.Aggiunta di pulsanti/tasti per passare al prossimo/precedente brano in lista.
:li.Possibilit… di copiare/tagliare/incollare contrassegni dagli Appunti.
:eul.
:p.:hp2.Roba "Media":ehp2.
:ul compact.
:li.Permettere altri tipi di ordinamento nella lista dei brani selezionati.
:li.Permettere un ordine diverso per le colonne quando si creano delle liste.
:li.Funzione "Storia" per i campi di inserimento (ovvero un menu a caduta per ogni campo,
in cui scegliere tra gli ultimi N inserimenti).
:li.Aggiunta di una pulsantiera (magari configurabile da utente) alla finestra principale.
:li.Aggiunta di una barra di stato alla finestra principale (che sostituisca le
finestrelle di avviso?)
:li.Supporto per Lyrics3/Lyrics3 v2.00.
:li.Possibilit… di leggere contrassegni da un archivio ed aggiungerli automaticamente ai brani
della lista.
:li.Funzione di auto-marcatura che crei dei contrassegni cercando di recuperare quante pi—
possibili informazioni da nomi fisici ed altro.
:eul.
:p.:hp2.Roba "Grossa":ehp2.
:ul compact.
:li.Aggiunta a &progname. di un database MP3 che permetta di tener facilmente traccia
di tutti i vostri brani MP3, dei loro dati, ricerca di brani, stampare liste di gruppi
selezionati, esportare liste in altri formati, ed altro.
:li.Consentire la visione dei contrassegni ID3 v2.x.
:li.Consentire la modifica dei contrassegni ID3 v2.x.
:li.Aggiunta di una funzione per accedere ad uno (o pi—) degli archivi CD su Internet
attraverso &progname..
:eul.
:p.Fatemi sapere quali funzioni pensate debbano avere la maggiore priorit… e di quali
potreste facilmente fare a meno...

.*:li.Add function for auto-renaming files (i.e. all files will get their
.*filename from the "Title" field for example).
.*:li.Possibility to keep (some of the) tag information when switching files
.*with ALT+N/ALT+P (may be useful for songs from one album, so you don't have to
.*enter Artist, Album, etc. everytime). Using the "Save all" function will allow
.*something like that already (i.e. insert album, artist and everything that
.*should stay the same, "Save all", then use ALT+N/ALT+P to insert the missing
.*fields).
.*:li.Allow macros in the "Comment" field, so things like playtime may be
.*inserted there automatically.
.*:li.Rename all, Save all, Remove all, Scanning/Writing the list and searching
.*for files would perhaps better have their own thread and I would like to have
.*a status window instead of displaying the stuff in the titlebar.
.*:li.Drag &amp. Drop support (add files to the selected files list by dropping
.*them on the window, adding a tag by dropping from window on the file icon,
.*etc.).
.*:li.Function for launching an MP3 player with the currently selected song.
.*:li.Settings dialog, where you can set various stuff (enable/disable the
.*various notification windows for example).
.*:li.Support other languages.
.*:li.Read genres from a user editable file (yes, yes, I promised it for this
.*release ...)
.*:li.Auto-tagging function.
.*:li.Remove the before mentioned "bugs".



.*-------------------------------------------------------------------------
.*fold00.*Files

:h1 id=files.Archivi su disco
:p.Questa sezione documenta alcuni degli archivi forniti con &progname.

.*-------------------------------------------------------------------------
.*fold00.*The genres file

:h2 id=genresfile.L'elenco dei generi
:p.In questo archivio sono memorizzati i nomi dei vari generi.
:p.Normalmente si chiama "genres.txt", ma si pu• usare un nome diverso impostandolo nella
pagina :link refid=misc reftype=hd.Varie:elink. delle :link refid=settingswindow reftype=hd.Impostazioni:elink..
:p.Volendo, questo archivio si pu• anche modificare tramite un comune programma di trattamento
testi, ma prima si prega di fate attenzione alle seguenti cose&colon.
:ul.
:li.Se si cambia il nome di un genere "vecchio", questo cambier… anche in tutti i brani che
lo adottavano.
:li.Un'altra conseguenza Š che probabilmente ora sarete gli unici ad usare questa definizione
di genere&colon. se qualcuno ricevesse un brano MP3 impostato su questo nuovo genere,
vedrebbe quello "vecchio". Cosa che potrebbe non essere ci• che desideravate.
:li.Allo stesso modo, anche se inventate dei nuovi generi (ovvero ne aggiungete di nuovi alla
lista), nessuno ne sapr… nulla. Quindi se qualcun altro user… un brano MP3 con uno di questi
"nuovi" generi, potrebbe riscontrare degli errori o, come minimo, una certa confusione.
:eul.
:p.Il formato preferito per l'elenco dei generi Š quello proprio di &progname.&colon.
:xmp.

.* > "The default format for the genres file is &progname.'s own
.* > format&colon."
.* >
.* > What do you mean with 'default'? Minta's default or THE
.* > DEFAULT format (read: Standard Format) for every program
.* > like this?
.*
.* Minta's.


# &progname. genres file
# This and the line above are comments

Blues
Classic Rock
Country
Dance
 ...
:exmp.
:p.L'elenco viene interpretato riga per riga. Commenti (linee comincianti per '#')
e righe vuote sono ignorati. Le altre righe si presume siano nomi di genere.
I generi vengono numerati nell'ordine in cui vengono trovati (quindi nell'esempio qui sopra
Blues sarebbe 1, Classic Rock 2, e cos via). Righe e nomi di genere possono essere lunghi
al massimo 255 caratteri.

:p.&progname. riesce ad interpretare anche il formato del "genres.txt" di WarpAMP
(dove ogni riga consiste in "nn nome", con "nn" il numero e "nome" il nome del genere).
Volendo i due formati possono anche essere mescolati, ma questo :hp1.non Š raccomandato:ehp1.!
Ad ogni modo &progname. cercher… comunque di estrarre le informazioni corrette.


.*-------------------------------------------------------------------------
.*fold00.*The player CMD-files

:h2 id=playercmdfiles.I comandi .CMD per il lettore
:p.Questi programmi servono per avviare col brano corrente un lettore MP3 di vostra
scelta direttamente dall'interno di &progname..
:p.Per ragioni tecniche &progname. deve usare un .CMD per lanciare il riproduttore;
chiamare direttamente il .EXE potrebbe non funzionare. Spero che questo possa cambiare in
una prossima versione.
Il nome del comando .CMD da usare si imposta nella pagina :link refid=misc reftype=hd.Varie:elink.
della finestra :link refid=settingswindow reftype=hd.Impostazioni:elink..
:p.Probabilmente il comando adatto al vostro lettore dovr… essere adattato&colon. di solito
questo si riduce ad inserire il disco e percorso corretti per la vostra stazione di lavoro.
:p.Vengono forniti i seguenti comandi&colon.
:ul.
:li.gowamp.cmd - per WarpAMP
:li.gopm123.cmd - per PM123
:li.gompg123.cmd - per mpg123
:eul.
:p.Se usate un lettore diverso, dovreste anche essere in grado di modificarne uno (a dire
il vero sono tutti quasi uguali...) per adattarlo al nuovo programma.


.*-------------------------------------------------------------------------
.*fold00.*Disclaimer & legal stuff

:h1 id=disclaimer.Disclaimer &amp. questioni legali

:p.[inizio N.d.T.]

:p.Minta al momento Š da considerarsi di uso gratuito. Unica condizione: darne notizia allo
sviluppatore, come ampiamente descritto in altre sezioni di questa stessa Guida.

:p.Queste brevi indicazioni in Italiano vengono fornite al solo ed unico scopo di chiarezza,
SENZA CHE CIã POSSA IN ALCUN MODO ESSERE CONSIDERATO ASSUNZIONE DI RESPONSABILIT·!

:p.In attesa di una, prossima, completa riorganizzazione dello status legale di Minta, si
prega di far riferimento alla licenza della versione Tedesca. O, eventualmente, di quella Inglese.

:p.Minta Š da considerarsi "AS IS", "cos come Š". Senza alcuna garanzia diretta od indiretta; n‚
espressa n‚ implicita! Chiunque lo usi, lo fa A PROPRIO RISCHIO E PERICOLO!

:p.Compito dell'utilizzatore Š anche quello di accertarsi preventivamente del buon funzionamento del
programma, e se questo sia o meno in grado di rispondere alle proprie esigenze.

:p.PRIMA DI UTILIZZARE IL PROGRAMMA, SI RACCOMANDA FORTEMENTE DI EFFETTUARE UNA COPIA DI
SICUREZZA (BACKUP) DEI DATI E DELLA CONFIGURAZIONE DEL PROPRIO SISTEMA!

:p.Sempre per chiarezza, si ribadisce che n‚ l'autore, Thorsten Thielen, n‚ il traduttore, Alberto
Gabrielli, potranno essere considerati responsabili di malfunzionamenti, perdite di dati
o, comunque, di qualunque altro problema dovesse verificarsi a seguito dell'uso del programma.

:p.[fine N.d.T.]

:p.---

:p.Following are the usual disclaimers. For those of you, who have read them
far too many times, here is just the short version&colon.

:p."I didn't do it! I didn't do it! Butthead did it!" ;-)

:p.Everyone else, please read this and keep in mind&colon.

:p.Though this program has been tested quite a lot, there may still be lots
of bugs in it (even serious ones - though I do not think so). Do not blame
me, if this program screws up your files or whatever.

:p.:hp2.YOU ARE USING THIS PROGRAM AT YOUR OWN RISK!:ehp2. I don't take any
responsibility for damages, problems, custodies, marital disputes,
etc. resulting from use, inability to use, misuse, possession or
non-possession of this program directly or indirectly.
I also don't give any warranty for bug-free operation, fitness
for
a particular purpose or the appropriate behaviour of the program
concerning animals, programers and little children.

:p.THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
PROGRAM IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

:p.Or, in a few words&colon.
If its good, I am responsible.
If its bad, its all your fault. ;-)

:p.Permission is granted to redistribute this program free of charge,
provided it is distributed in the full archive with unmodified
contents and no profit beyond the price of the media on which it
is distributed is made. Exception to the last rule&colon. It may be
included on freeware/shareware collections on CD-ROM, as well as
on magazine cover CD-ROMs.

:p.All trademarks mentioned anywhere around here are property of their
owners and the like ...

:p.(Strange, this section is getting longer and longer with every
program ... &colon.-)


.*-------------------------------------------------------------------------
.*fold00.*Author & Minta homepage

:h1 id=author.L'autore &amp. la pagina Web di &progname.
:p.:hp7.Autore:ehp7.

:dl break=all tsize=5 compact.

:dt.:hp2.Posta tradizionale:ehp2.
:dd.Thorsten Thielen c/o Sascha Weber, Postfach 3928, 54229 Trier, Germany

:dt.:hp2.Posta elettronica:ehp2.
:dd.&email1.

:dt.:hp2.Pagina Web:ehp2.
:dd.&www.

:edl.

:artwork name='src/data/teamlogo.bmp' align=center.
:p.Membro orgoglioso del Team OS/2 Region Trier (:hp1.www.teamos2.ipcon.de:ehp1.),
i creatori del CD-ROM "Team Trier Collection".

:lm margin=1.
:p.
Suggerimenti e segnalazioni di errori sono sempre i benvenuti. Beh... magari quest'ultimi
non :hp1.cos:ehp1. benvenuti... ;-)
:p.
.br
:hp7.La pagina Web di &progname.:ehp7.
:p.Per informazioni generali o su nuove versioni di &progname., visitate la pagina Web&colon.
&www./minta



.*-------------------------------------------------------------------------
.*fold00.*Help wanted!
:h1 id=helpwanted.Richiesta di aiuto!
:p.Adesso che &progname. gestisce altre lingue, ovviamente vorrei includerne quante pi—
possibile. Il problema Š che io parlo solo Inglese e Tedesco abbastanza bene da poterli tradurre. &colon.-)
Quindi, se qualcuno l… fuori vuol tradurre &progname. in una nuova lingua,
Š cordialmente invitato a farlo!

:p.Ho allegato i sorgenti dell'aiuto e le risorse del programma in un archivio ZIP separato
('language.zip'). Prendete semplicemente gli *.rc ed *.hlp di vostra scelta, e cominciate a
lavorare! &colon.-) Se avete domande, liberi di :link refid=author reftype=hd.farmele:elink.!

:p.Se non avete tempo (o semplicemente non avete voglia ;-) di fare una traduzione "completa"
(cioŠ programma ed aiuto in linea) ovviamente potete tradurre anche solo le risorse del
programma (dialoghi, menu, messaggi)! Gi… questo sarebbe di grande aiuto...

.*-------------------------------------------------------------------------
.*fold00.*Credits

:h1 id=credits.Ringraziamenti
:p.Desidero ringraziare le seguenti persone, per il loro l'aiuto ed appoggio su
&progname.&colon.

:ul.
:li.Ringraziamenti vanno a :hp1.Sascha Weber:ehp1. e :hp1.Dirk Riemekasten:ehp1. per il loro
eccellente beta test di &progname.
(E un calcione nel c*** per avermi continuamente costretto ad
aggiungere nuove funzioni ;-)
:li.Grandi ringraziamnenti vanno anche all':hp1.mpg123 team:ehp1. per aver scritto il lettore
MP3 "mpg123" ed aver incluso i sorgenti, cos da permettermi di prendere a prestito la loro
routine di decodifica degli header MP3! Ô decisamente migliore della cosa che avevo scritto
io... (Di mpg123 potrete saperne di pi— su
http&colon.//www.sfs.nphil.uni-tuebingen.de/~hipp/mpg123.html).
:li.Questo programma usa delle piccole sezioni tratte dal codice dell'eccellente monitor di risorse
di sistema "MemSize", di :hp1.Richard Papo:ehp1.
(Potete saperne di pi— su MemSize a http&colon.//www.msen.com/~rpapo).
:li.Dei ringraziamenti particolari vanno a tutti coloro che
hanno tradotto &progname. in altre lingue&colon.
:ul.
:li.Molte grazie a :hp1.Luc Van Bogaert:ehp1. per la traduzione Olandese.
:li.Molte grazie a :hp1.Guillaume Gay:ehp1. per la traduzione Francese.
:li.Molte grazie a :hp1.Jostein Ullestad:ehp1. e :hp1.H†vard Mork:ehp1.
per la traduzione Norvegese.
:li.Molte grazie a :hp1.Cyrill Vakhneyev:ehp1. per la traduzione Russa.
:li.Molte grazie a :hp1.Michael Baryshnikov:ehp1. per aver trovato parecchi errori!
:li.Uno speciale ringraziamento ad :hp1.Alberto Gabrielli:ehp1.. Non solo per la traduzione italiana
di programma ed aiuto in linea, ma anche per aver scoperto e segnalatomi tanti, tanti errori ed
inconsistenze! [troppo buono... N.d.T.]
:eul.
:li.Grazie anche a tutti gli utilizzatori che mi hanno segnalato dei problemi, dato
suggerimenti o che, semplicemente, mi hanno scritto di &progname.!
:eul.


.*-------------------------------------------------------------------------
.*fold00.*Registering
:h1 id=register."Registrazione"
.*:p. if you are satisfied with what &progname. 1.67 offers, you are free to keep
.*using this version ... but please keep in mind that it lacks many useful
.*functions that are present in newer versions and that it is not supported
.*any longer!
:p.Potete diventare utenti registrati di &progname. (&version.) semplicemente :link
refid=author reftype=hd.inviandomi un messaggio di posta elettronica (od una cartolina,
o quel che preferite):elink.. In effetti se usate &progname. questo Š obbligatorio (o almeno, se lo usate pi— di una
volta l'anno. ;-)
:p.Scrivete pure una cosa tipo "Salve, io uso il tuo programma &progname.!"
ed io sar• soddisfatto. Se :hp1.non:ehp1. volete essere inseriti nella lista di distribuzione
(mailing list) con novit… ed informazioni su &progname., non dimenticate di dirmelo!

:p.Ma scommetto che l… fuori c'Š un sacco di gente che ha scoperto &progname.,
ci ha lavorato per un po' e, nonostante tutto, non vuole mandarmi un messaggio per
registrarsi. Bene per voi ho costruito questa lista de...
:p.:hp2.Le 10 migliori scuse per non registare &progname.:ehp2.

:ul compact.

:li.Secondo me &progname. Š un programma abbastanza scarso. Non mi piacciono i colori ed i
caratteri delle finestre (ed ancor meno mi piace l'idea di poterli cambiare!). Non parlo
una sola delle lingue allegate, ed ho anche sentito dire che una volta Š persino stato
trovato un malfunzionamento. Per non parlare della schifosa assistenza tecnica&colon.
scrivere un messaggio per ottenere aiuto Š troppo complicato.

:li.Sono gi… completamente soddisfatto da quel che offre &progname. 1.67.
Trover• da solo il sistema di evitare i malfunzionamenti che si dovessero scoprire!
Non user• mai il trascinamento, le funzioni di marcatura automatica o quelle robe per
catalogare! E l'ID3 v2.x Š comunque molto oltre le mie necessit…. Quindi risparmiami pure
i tuoi aggiornamenti...

:li.Che m'importa di essere avvisato di una nuova versione? Perch‚ dovrei sottoscrivere
un'altra di quelle liste di distribuzione? La mia casella postale gi… straripa regolarmente,
e oltretutto controllo tutti i giorni la sezione "Incoming" di Hobbes!

:li.Non ho proprio il tempo di mandarti un messaggio! Vedi, ho un lavoro, una moglie, 10
figli, un'amichetta, una macchina, una casa, una piscina e migliaia di MP3 ancora senza
contrassegno; quindi sono occupatissimo giorno e notte!
Non oso pensare a cosa potrei perdermi in quei cinque minuti...

.*:li.$10 is far too much money for this program! For this big amount I could,
.*well, buy half of an audio CD! I could go out to dinner with my friend (well,
.*at least if we have already eaten before). I could think of thousand things
.*more ...

:li.Perch‚ dovrei farti pensare che scrivere programmi per OS/2 sia una buona cosa?
Esistono gi… sin troppi programmi per OS/2, e non abbiamo certo bisogno che il mercato sia
inflazionato. Vero?

:li.In giro ci sono gi… un sacco di programmi che fanno la stessa cosa! S, Š vero, forse non
hanno la stessa comoda interfaccia PM; pu• anche darsi che manchino di molte delle
funzioni offerte da &progname.; magari, in effetti, ne esistono solo uno o due. Per• almeno
non mi tocca perderci tempo scrivendo lunghe missive agli autori!

:li.Credo che incoraggiare il concetto di "mailware" non abbia alcun senso. Gli sviluppatori
che danno via programmi perfettamente funzionanti e sperano che, pur potendo
tranquillamente farne a meno, chi effettivamente li usa gli scriva, son sicuramente solo un
branco di pazzi!

.* sono di sicuro solo un branco di pazzi!

.*:li.Credo che incoraggiare il concetto di "mailware" non abbia alcun senso. Gli sviluppatori
.*che danno via programmi perfettamente funzionanti e sperano che chi effettivamente li usa, pur
.*potendo tranquillamente farne a meno, gli scriva, sicuramente son solo un branco di pazzi!



:li.Perch‚ dovrei provare a sostenere i programmi per OS/2? OS/2 Š morto, datemi retta!
"Io sono Bill Gates, della MicroBorg. Questo Sistema Operativo verr… assimilato. Ogni
sviluppo Š inutile."

:li.Ho tradotto il programma in un'altra lingua, e ho gi… scritto qualcosa quando ho
spedito la traduzione. &colon.-)

:li.Non so scrivere! Non ho idea di come mandare messaggi di posta!! Non c'ho neanche
un accesso alla rete!!! E per giunta uso Windows!!!!
:eul.



.*-------------------------------------------------------------------------
.*fold00.*Dedication

.* I think we should keep "Hackers" and "The Plague" untranslated.

:h1 id=dedication.Dedica
:p.&progname. Š dedicato a :hp1."Hackers":ehp1., probabilmente il peggior film
mai realizzato su calcolatori, tecnologia dell'informazione ed il mondo hacker.
Una vera commedia. Son quasi morto dal ridere per tutto il tempo (cioŠ, veramente solo
quando non stavo piangendo).

.*:p.  mi sono ammazzato di risate  Sono quasi morto dal ridere [per]  (beh veramente solo quando

.*:p. really great comedy though, I nearly laughed my *ss off half the time (well, actually only when I wasn't crying).

:p.A proposito, scommetto che "da Vinci" avrebbe buttato gi— qualunque sistema gi… solo per
le risorse di sistema impegnate...
.*la richiesta di risorse di sistema...

:p.A proposito 2&colon. Forse :hp1.il film:ehp1. avrebbero dovuto chiamarlo "The Plague".


.*   > What is "resources"? System hardware resources? Or what?

.*   System ressources on the whole. "da Vinci" was the name of a
.*   virus that some "hacker" (what better would be called a "cracker")
.* inserted into the computer systems of some company. Apart from
.*   being very "intelligent" (allowed to controll whole ships systems
.*   >from afar by itself) it featured minute-long, large fullscreen
.*   animations and high-quality sound effects that would probably take
.*   several 100 megabytes to store :-)

.*   > Same for the next phrase: "Perhaps they should have called
.*   > :hp1.the film:ehp1. "The Plague"?"

.*   "The plague" was the self-assigned name of the above ultra-stupid
.*   (and of course unbelievable evil) cracker that worked under cover
.*   as system security administrator in above company.





:p.No, naturalmente questa non Š la vera dedica...

:p.:artwork name='src/data/godzilla.bmp' align=center.
:hp2.
.ce Questa versione di &progname. Š dedicata a Godzilla.
:ehp2.

.*-------------------------------------------------------------------------
.*fold00.*There's more where that came from ...

:h1 id=moreprogs.There's more where that came from ...
:p.&progname. non Š assolutamente il solo programma OS/2 che io abbia scritto.
Ecco un piccolo elenco di altri programmi :hp1.liberamente disponibili:ehp1. usciti dalle
mie mani&colon.

.* > is "There's more where that came from ..." a citation (It came
.* > from the desert :-?) and should not to be translated?
.* > In the German version is in English...
.* I must admit that I can't remember where exactly I got this
.* sentence from. Just leave it in English.


:dl break=all tsize=5.

:dt.:hp2.Gotcha!:ehp2. (programma di cattura schermate)
:dd.Cattura finestre, interni di finestre, (parti di) schermo. Cattura controllata a tempo,
automatica, ripetuta. Registrazione su disco o negli appunti, etc.

:dt.:hp2.Wanda:ehp2. ("foglietti appiccicosi" per la scrivania)
:dd.Finestrelle di appunti di tutti i colori, forme, etc. Tantissime opzioni di
configurazione. Stampa, registrazione, etc.

:dt.:hp2.Carrie R. Lust:ehp2. (Calcolo dei costi telefonici/tempo di collegamento)
:dd.11 conteggi disponibili (configurabili). 4 eventi di allarme (configurabili).
Traccia di tutte le connessioni, etc.

:dt.:hp2.Xened:ehp2. ("Xenon II" editor)
:dd.Modifica dei prezzi delle armi, modifica delle mappe, trucchi e suggerimenti, etc.
Disponibile anche per DOS e Linux.

:dt.:hp2.CAD/Off:ehp2. (Inibitore di riavvio)
:dd.Disattiva la combinazione di tasti CTRL-ALT-DEL fino allo spegnimento del sistema.

:dt.:hp2.Tomo:ehp2. (Nuova versione del "Tetris")
:dd.Altri mattoni, dimensioni del campo di gioco configurabili, etc. Purtroppo
solo per DOS, ed in Tedesco (ho perso i sorgenti...). [adatto ad OS/2. N.d.T.]

:edl.
:p.Oltre a questi, ce ne sono altri (anche qualche gioco!) in sviluppo proprio in questo momento.
Per saperne di pi—, date un'occhiata a&colon. &www./projects.html

.*-------------------------------------------------------------------------

:euserdoc.
