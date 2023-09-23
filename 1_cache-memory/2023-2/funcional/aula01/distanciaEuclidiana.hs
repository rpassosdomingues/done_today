{-
===============================
Autor: Rafael Passos Domingues
   RA: 2023.1.08.036
 Data: Sep 16 Sat [08h43]
===============================
-}

{-
Função para calcular o quadrado da hipotenusa.
Recebe: Dois catetos | Retorna: Quadrado da hipotenusa.
-}
pitagoras :: Float -> Float -> Float
pitagoras a b = a*a + b*b

{-
Função para calcular a distância entre dois pontos (x1, y1) e (x2, y2)
levando em conta a potencial equivalência entre coordenadas.
Obs. A função faz reuso da função pitágoras.
Recebe: Quatro coordenadas | Retorna: Distância Euclidiana.
-}
distancia :: Float -> Float -> Float -> Float -> Float
distancia x1 y1 x2 y2
   | (x1 == x2)   = abs (y2 - y1)
   | (y1 == y2)   = abs (x2 - x1)
   | otherwise    = sqrt (pitagoras (x2 - x1) (y2 - y1))

{-
Função para calcular a quantidade de raízes reais de
uma equação de segundo grau.
Recebe: Três coeficientes | Retorna: Quantidade de raízes reais.
-}
qtdRaizesReais :: Float -> Float -> Float -> Float
qtdRaizesReais a b c
   | (b*b   < 4*a*c)  = 0
   | (b*b   > 4*a*c)  = 2
   | (b*b  == 4*a*c)  = 1
