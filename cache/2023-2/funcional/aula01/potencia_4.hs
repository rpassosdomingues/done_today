potencia_quadrado :: Int -> Int
potencia_quadrado x = x * x

potencia_quarta :: Int -> Int
potencia_quarta x = potencia_quadrado (potencia_quadrado x)