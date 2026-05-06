# Commande-une-LED-et-un-buzer-avec-le-site
## Étape 1 : Ajouter les boutons dans la page data.php
- il faut rajouter dans la partie body un bouton **"Allumer"**
  Copiez le code dans la partie body
  ```cpp
  <body>

    <PARTIE MESURE A LAISSER>

<h1>Commande ESP32</h1>

   <button onclick="fetch('http://IP_ESP32/son')">
   Allumer
   </button>


</body>
```
