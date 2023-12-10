area_retangulo :: Int -> Int -> Int
area_retangulo base altura = base * altura

area_paralelepipedo :: Int -> Int -> Int -> Int
area_paralelepipedo base altura profundidade = (area_retangulo base altura) * profundidade