# terkepszinezes
Térképszinezés: adott n ország a térképen, adott számú színnel,
hogyan lehet kiszínezni úgy a térképet, hogy a szomszédos országok ne legyenek egyforma színűek.

Három algoritmus segítségével oldjuk meg:
- nyers backtracking algoritmus
- backtracking + MVR + forward checking algoritmus
- backtracking + MVR + AC-3 algoritmus

A feladathoz ausztrália államait használtuk példának.
A gráf csúcsait a következőképpen számoztuk:
  - 1 - WA
  - 2 - NT
  - 3 - SA
  - 4 - Q
  - 5 - NSW
  - 6 - V
  - 7 - T
  
  Mivel a feladat bemenő paraméterének kéne a szomszédsági mátrix is, ezért a program nem vár paramétereket. Erre a példára fut le és írja ki az értékadások számát. (7 csúcs, 3 szín)
