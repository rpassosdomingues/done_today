ORG 300

INICIO,   LOAD M, N       // Carregue o valor de N em M
          LOAD AC, ZERO   // Inicialize o acumulador AC com 0
          LOAD MQ, ZERO   // Inicialize o multiplicador MQ com 0
          JUMP SOMA

LOOP,     LOAD M, N       // Carregue o valor de N em M
          LOAD MQ, AC     // Carregue o valor atual de AC em MQ
          MUL M, MQ       // Multiplique M por MQ
          LOAD MQ, M[2]   // Carregue o resultado da multiplicação em MQ
          ADD M[1], MQ    // Adicione M[1] a MQ
          STOR MQ, M[1]   // Armazene o resultado em M[1]
          LOAD MQ, AC     // Carregue o valor atual de AC em MQ
          ADD M[2], MQ    // Adicione M[2] a MQ
          STOR MQ, M[2]   // Armazene o resultado em M[2]
          LOAD MQ, M[1]   // Carregue o valor de M[1] em MQ
          ADD MQ, M[2]    // Adicione M[2] a MQ
          ADD MQ, AC      // Adicione o valor atual de AC a MQ
          STOR MQ, AC    // Armazene o resultado em AC
          LOAD MQ, AC     // Carregue o valor atual de AC em MQ
          ADD ONE, MQ     // Adicione 1 a MQ
          STOR MQ, AC    // Armazene o resultado em AC
SOMA,     LOAD MQ, AC     // Carregue o valor atual de AC em MQ
          SUB M, MQ       // Subtraia M de MQ
          JUMPPLUS LOOP   // Pule para LOOP se MQ for positivo
FIM,      HALT

N,        DAT 10          // Defina o valor de N aqui
ZERO,     DAT 0
ONE,      DAT 1

M,        DAT             // Local para armazenar temporariamente o valor de N
          DAT             // Local para armazenar temporariamente os resultados intermediários
