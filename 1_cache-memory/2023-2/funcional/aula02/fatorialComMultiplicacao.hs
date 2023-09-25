{-
===============================
Autor: Rafael Passos Domingues
   RA: 2023.1.08.036
 Data: Sep 22 Fri [19h05]
===============================
-}

--Usando Multiplicação
fatorial :: Integer -> Integer
fatorial 0 = 1			            --base
fatorial n = n * fatorial (n-1) --chamada recursiva passando o valor de n