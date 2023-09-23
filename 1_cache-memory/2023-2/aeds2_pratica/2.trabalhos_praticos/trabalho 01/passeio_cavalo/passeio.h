#ifndef PASSEIO_H
#define PASSEIO_H

#include <stdbool.h>

bool **ler_instancia(int instancia_num, int *n, int *m);
void computa_passeios(bool **tabuleiro, int n, int m);

#endif /* PASSEIO_H */

