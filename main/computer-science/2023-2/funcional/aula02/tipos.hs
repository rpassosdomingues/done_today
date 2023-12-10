--ehMaior :: Int -> Int -> Bool
--ehMaior m n = m > n

type Nome = String	-- Sinônimo para String  [Nome]
type Idade = Int	   -- Sinônimo para Int     [Idade]
type CPF = Integer	-- Sinônimo para Integer [CPF]

cadastro :: CPF -> (Nome, Idade)
cadastro cpf
   | cpf == 11111111111		= ("Jose", 12)
   | cpf == 22222222222		= ("Joao", 77)
   | cpf == 33333333333		= ("Maria", 50)
   | otherwise			= ("Desconhecido", 0)
