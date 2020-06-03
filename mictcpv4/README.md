# Notes

Le programme comporte uniquement la phase de connexion qui fonctionne de mon côté.
Un des cas limites auquel j'ai été confronté correspond au cas où le dernier ACK de connexion est perdu. Dans ce cas le puit est perdu. J'ai décidé de considérer que si le puit reçoit un paquet et que le paquet précédent était un SYN (indiqué par la variable) il considèrera que la connexion est établie.

J'ai également (pour les tests) mis un taux d'erreur important sur la ligne (80%)