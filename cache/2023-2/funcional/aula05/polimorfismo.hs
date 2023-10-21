listaInt :: [Int]
listaInt = [1..5]

listaChar :: [Char]
listaChar = ['a'..'z']

comprimento_lista :: [t] -> Int -- t = qualquer tipo
comprimento_lista [] = 0
comprimento_lista (x:xs) = 1 + comprimento_lista xs