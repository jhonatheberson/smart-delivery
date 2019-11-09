#include "Vertice.h"
#include "Grafo.h"

void Grafo::Ordenar_vertice(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        Ordenar_vertice(l, m);
        Ordenar_vertice(m + 1, r);

        ///MERGE
        int i, j, k, n1, n2;

        n1 = m - l + 1;
        n2 = r - m;

        Vertice L[n1], R[n2];

        for (i = 0; i < n1; i++)
            L[i] = vertice[l + i];
        for (j = 0; j < n2; j++)
            R[j] = vertice[m + 1 + j];

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (L[i].grau <= R[j].grau)
            {
                vertice[k] = L[i];
                i++;
            }
            else
            {
                vertice[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            vertice[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            vertice[k] = R[j];
            j++;
            k++;
        }
        ///FIM MERGE
    }
}
