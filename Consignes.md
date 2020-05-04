# BE-Reseau
[Enoncé](https://docs.google.com/document/d/1PXk1MNzCJXGpLSu3j1g5p1aim16oSR33Oi67GCYA-WQ/edit#)
## Objectif général

Puit Multithread masqué au début
Recoit
recv() bloquant
    |
MIC-TCP attend Monothread puis multi
 | (protocol lancé avec 
 |  initialize_components())
 |      -> Multithreading 
 |         masqué au début
 |Boucle
    | void process_received_PDU(...)
        | Verif n°seq
        | Mise ds buff récep
        | Constr + envoi ACK
        | MAJ compteur

Source Monothread
Emet
connect()
Boucle Vidéo pas finie
    | send() bloquant (ACK)
        | Génération PDU DT
        | Compteur
        | Timer
        | Attend



## Diagrammes d'états

Stop and Wait v1-v2-v3 côté puit et source