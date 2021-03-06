#include <fstream>
#include <iostream> 
#include <vector>
#include <queue> 
#include <algorithm> 
using namespace std;
ifstream in("date.in");
ofstream out("date.out");
class Graf
{
    int muchii;
    int noduri;
    int minim;
    int maxim;
    int start;
    int suma;
    vector<int> okey;
    vector<int> adiacenta[1000];
    vector<int> pozitii[1000];
    vector<vector<int>> lista;

public:

    //DFS

    void citire_DFS()
    {
        int x, y;
        in >> noduri >> muchii;
        lista.resize(noduri + 1);
        for (int i = 1; i <= muchii; i++)
        {
            in >> x >> y;
            lista[x].push_back(y);
            lista[y].push_back(x);
        }
    }
    void DFS(int q, vector <int>& vizitat)
    {
        vizitat[q] = 1;
        for (int i = 0; i < lista[q].size(); i++)
            if (!vizitat[lista[q][i]])
                DFS(lista[q][i], vizitat);
    }
    void afisare_DFS()
    {
        vector <int> vizitat;
        int nr = 0;
        for (int i = 0; i <= noduri; i++)
            vizitat.push_back(0);
        for (int i = 1; i <= noduri; i++)
            if (!vizitat[i])
            {
                nr++;
                DFS(i, vizitat);
            }
        out << nr;
    }

    //BFS

    void BFS()
    {
        int x, y, start;
        vector<int> distanta, coada;
        cin >> noduri >> muchii >> start;
        coada.resize(noduri + 1);
        for (int i = 0; i <= noduri; i++)
            coada[i] = 0;
        distanta.resize(noduri + 1);
        for (int i = 0; i <= noduri; i++)
            distanta[i] = 0;
        lista.resize(noduri + 1);
        for (int i = 1; i <= muchii; i++)
        {
            cin >> x >> y;
            lista[x].push_back(y);
        }
        distanta.resize(noduri + 1);
        for (int i = 1; i <= noduri; i++)
            distanta[i] = -1;
        x = y = 1;
        distanta[start] = 0;
        coada[x] = start;
        while (x <= y)
        {
            for (int i = 0; i < lista[coada[x]].size(); i++)
                if (distanta[lista[coada[x]][i]] == -1)
                {
                    y++;
                    coada[y] = lista[coada[x]][i];
                    distanta[lista[coada[x]][i]] = distanta[coada[x]] + 1;
                }
            x++;
        }
        for (int i = 1; i <= noduri; i++)
            cout << distanta[i] << " ";
    }

    //Havel Hakimi

    void HH()
    {
        vector<int> vector = { 3, 3, 3, 3 };
        int iesire = 0;
        while (!iesire)
        {
            sort(vector.begin(), vector.end(), greater<>());
            if (vector[0] == 0)
            {
                iesire++;
                break;
            }
            int v = vector[0];
            vector.erase(vector.begin() + 0);
            if (v > vector.size())
            {
                iesire = 0;
                break;
            }
            for (int i = 0; i < v; i++)
            {
                vector[i]--;
                if (vector[i] < 0)
                {
                    iesire = 0;
                    break;
                }
            }
        }
        if (iesire)
            cout << "Da";
        else
            cout << "Nu";
    }

    //Componente Tare Conexe

    void CTC()
    {
        int  x, y, nr_ctc = 0;
        vector <int> vizitat;
        cin >> noduri >> muchii;
        vizitat.resize(noduri + 1);
        for (int i = 0; i <= noduri; i++)
            vizitat.push_back(0);
        for (int i = 0; i <= muchii; i++)
            adiacenta[i].resize(noduri + 1);
        for (int i = 0; i < muchii; i++)
        {
            cin >> x >> y;
            adiacenta[x][y] = 1;
        }
        for (int i = 1; i <= noduri; i++)
            for (int j = 1; j <= noduri; j++)
                for (int k = 1; k <= noduri; k++)
                    if (i != j && i != k && j != k)
                        if (adiacenta[j][i] && adiacenta[i][k])
                            adiacenta[j][k] = 1;
        for (int i = 1; i <= noduri; i++)
        {
            if (!vizitat[i])
            {
                nr_ctc++;
                vizitat[i] = nr_ctc;
                for (int j = 1; j <= noduri; j++)
                    if (adiacenta[i][j] && adiacenta[j][i])
                        vizitat[j] = nr_ctc;
            }
        }
        cout << nr_ctc << "\n";
        for (int i = 1; i <= nr_ctc; i++)
        {
            for (int j = 1; j <= noduri; j++)
                if (vizitat[j] == i)
                    cout << j << " ";
            cout << "\n";
        }
    }

    //Sortare Topologica

    void DFS_2(int q, vector <int>& vizitat, vector <int>& afisare)
    {
        vizitat[q] = 1;
        for (int i = 0; i < lista[q].size(); i++)
            if (!vizitat[lista[q][i]])
                DFS_2(lista[q][i], vizitat, afisare);
        afisare.push_back(q);
    }
    void ST()
    {
        vector <int> vizitat, afisare;
        for (int i = 0; i <= noduri; i++)
            vizitat.push_back(0);
        for (int i = 1; i <= noduri; i++)
            if (!vizitat[i])
            {
                DFS_2(i, vizitat, afisare);
            }
        for (int i = afisare.size() - 1; i >= 0; i--)
            cout << afisare[i] << " ";
    }

    //Conexiune Critica
    
    void DFS_3(int timp, vector<vector<int>>& v, vector<int>& numarare, int k, int parinte,
        vector<bool>& vizite, vector<int>& vecin)
    {
        vizite[k] = 1;
        numarare[k] = timp++;
        vecin[k] = numarare[k];
        for (auto fiu : v[k])
        {
            if (fiu == parinte)
                continue;
            if (!vizite[fiu])
            {
                DFS_3(timp, v, numarare, fiu, k, vizite, vecin);
                vecin[k] = min(vecin[k], vecin[fiu]);
                if (vecin[fiu] > numarare[k])
                    lista.push_back({ k, fiu });
            }
            else
                vecin[k] = min(vecin[k], numarare[fiu]);
        }
        return;
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections)
    {
        int timp = 0;
        vector<vector<int>> v(n);
        vector<int> numarare(n, 0);
        vector<int> vecin(n, 0);
        vector<bool> vizite(n, 0);
        for (int i = 0; i < connections.size(); i++)
        {
            v[connections[i][0]].push_back(connections[i][1]);
            v[connections[i][1]].push_back(connections[i][0]);
        }
        DFS_3(timp, v, numarare, 0, -1, vizite, vecin);
        return lista;
    }
    
    //Arbore Partial de Cost Minim
    
    void APM()
    {
        vector<int> x, y, z, v, capat1, capat2;
        in >> noduri >> muchii;
        x.resize(muchii + 1);
        y.resize(muchii + 1);
        z.resize(muchii + 1);
        v.resize(muchii + 1);
        capat1.resize(muchii + 1);
        capat2.resize(muchii + 1);
        for (int i = 0; i <= muchii; i++)
        {
            x.push_back(0);
            y.push_back(0);
            z.push_back(0);
            v.push_back(0);
            capat1.push_back(0);
            capat2.push_back(0);
        }
        for (int i = 1; i <= muchii; i++)
            in >> x[i] >> y[i] >> z[i];
        for (int i = 1; i <= noduri; i++)
            v[i] = i;
        for (int i = 1; i < muchii; i++)
            for (int j = i + 1; j <= muchii; j++)
            {
                if (z[i] > z[j])
                {
                    swap(x[i], x[j]);
                    swap(y[i], y[j]);
                    swap(z[i], z[j]);
                }
            }
        int k = 0, nr = 0, cost = 0, minn, maxx;
        while (nr < noduri - 1)
        {
            k++;
            if (v[x[k]] != v[y[k]])
            {
                nr++;
                cost += z[k];
                capat1[nr] = y[k];
                capat2[nr] = x[k];
                if (v[x[k]] > v[y[k]])
                {
                    minn = v[y[k]];
                    maxx = v[x[k]];
                }
                else
                {
                    minn = v[x[k]];
                    maxx = v[y[k]];
                }
                for (int i = 1; i <= noduri; i++)
                    if (v[i] == maxx)
                        v[i] = minn;
                for (int i = 1; i <= noduri; i++)
                    if (v[i] == v[minn])
                        v[i] = v[maxx];
            }
        }
        out << cost << "\n" << noduri - 1 << "\n";
        for (int i = 1; i < noduri; i++)
            out << capat1[i] << " " << capat2[i] << "\n";
    }
    
    //Dijkstra
    
    void Djk()
    {
        int  x, y, cost, nr_noduri, p, q;
        vector <int> costuri[5000], drumuri, h, d, lungime;
        in >> noduri >> muchii;
        drumuri.resize(muchii + 1);
        h.resize(muchii + 1);
        d.resize(muchii + 1);
        lungime.resize(muchii + 1);
        for (int i = 0; i <= muchii; i++)
        {
            drumuri.push_back(0);
            h.push_back(0);
            d.push_back(0);
            lungime.push_back(0);
            adiacenta[i].resize(noduri + 1);
            costuri[i].resize(noduri + 1);
        }
        for (int i = 1; i <= muchii; i++)
        {
            in >> x >> y >> cost;
            adiacenta[x].push_back(y);
            costuri[x].push_back(cost);
            if (i <= noduri)
            {
                drumuri[i] = 100000;
                h[i] = i;
                d[i] = i;
            }
            lungime[x] = adiacenta[x].size();
        }
        drumuri[1] = 0;
        nr_noduri = noduri;
        for (int i = 1; i <= noduri; i++)
        {
            for (int j = 0; j < lungime[h[1]]; j++)
                if (drumuri[h[1]] + costuri[h[1]][j] < drumuri[adiacenta[h[1]][j]])
                {
                    drumuri[adiacenta[h[1]][j]] = drumuri[h[1]] + costuri[h[1]][j];
                    p = d[adiacenta[h[1]][j]];
                    q = 1;
                    while (q == 1 && p > 1)
                    {
                        q = 0;
                        if (drumuri[h[p]] < drumuri[h[p + 1]])
                        {
                            q = 1;
                            swap(h[p], h[p + 1]);
                            swap(d[h[p]], d[h[p + 1]]);
                            p++;
                        }
                    }
                }
            d[h[1]] = nr_noduri;
            h[1] = h[nr_noduri--];
            p = 1;
            while (1)
            {
                y = 0;
                if (nr_noduri >= p * 2 + 1 && drumuri[h[p * 2 + 1]] < drumuri[h[p * 2]])
                    y = 1;
                if (nr_noduri >= p * 2 + y && drumuri[h[p]] > drumuri[h[p * 2 + y]])
                {
                    q = 1;
                    swap(h[p], h[p * 2 + y]);
                    swap(d[h[p]], d[h[p * 2 + y]]);
                    p = p * 2 + y;
                    continue;
                }
                break;
            }
        }
        for (int i = 2; i <= noduri; i++)
        {
            if (drumuri[i] == 100000)
                out << "0 ";
            else
                out << drumuri[i] << " ";
        }
    }
    
    //Bellman-Ford
    
    void BF()
    {
        vector <int> costuri[1000], distanta, v;
        in >> noduri >> muchii;
        distanta.resize(noduri + 1);
        v.resize(noduri + 1);
        for (int i = 0; i <= muchii; i++)
        {
            v.push_back(0);
            adiacenta[i].resize(noduri + 1);
            costuri[i].resize(noduri + 1);
        }
        int x, y, z;
        for (int i = 1; i <= muchii; i++)
        {
            in >> x >> y >> z;
            adiacenta[x].push_back(y);
            costuri[x].push_back(z);
        }
        int final = 0, inceput = 0;
        for (int i = 1; i <= noduri; i++)
            distanta[i] = 10000;
        v[inceput] = 1;
        v[final] = 1;
        distanta[1] = 0;
        while (inceput <= final)
        {
            x = v[inceput];
            inceput++;
            for (int i = 0; i < adiacenta[x].size(); i++)
                if (distanta[adiacenta[x][i]] > distanta[x] + costuri[x][i])
                {
                    distanta[adiacenta[x][i]] = distanta[x] + costuri[x][i];
                    v[++final] = adiacenta[x][i];
                }
        }
        for (int i = 2; i <= noduri; i++)
            if (distanta[i] == 10000)
                out << 0;
            else
                out << distanta[i] << " ";

    }
    
    //Paduri de multimi disjuncte
    
    int get_root(int x, vector<int>multime)
    {
        while (multime[x] != x)
            x = multime[x];
        return x;
    }
    void Dis()
    {
        int nr_multimi, nr_operatii;
        vector<int> multime;
        in >> nr_multimi >> nr_operatii;
        multime.resize(nr_operatii + 1);
        for (int i = 0; i <= nr_operatii; i++)
            multime.push_back(0);
        for (int i = 1; i <= nr_multimi; i++)
            multime[i] = i;
        for (int i = 1; i <= nr_operatii; i++)
        {
            int cod, x, y, a, b;
            in >> cod >> x >> y;
            a = get_root(x, multime);
            b = get_root(y, multime);
            if (cod == 1)
            {
                if (a < b)
                    multime[b] = a;
                else
                    multime[a] = b;
            }
            else
            {
                if (a == b)
                    out << "DA\n";
                else
                    out << "NU\n";
            }
        }
    }
    
    //Floyd-Warshall
    
    void citire_FW()
    {
        in >> noduri;
        for (int i = 0; i <= noduri; i++)
            adiacenta[i].resize(noduri + 1);
        for (int i = 1; i <= noduri; i++)
            for (int j = 1; j <= noduri; j++)
                in >> adiacenta[i][j];
    }
    void FW()
    {
        for (int k = 1; k <= noduri; k++)
            for (int i = 1; i <= noduri; i++)
                for (int j = 1; j <= noduri; j++)
                    if ((i != j) && adiacenta[i][k] && adiacenta[k][j])
                        if ((adiacenta[i][j] > (adiacenta[i][k] + adiacenta[k][j])) || (!adiacenta[i][j]))
                            adiacenta[i][j] = adiacenta[i][k] + adiacenta[k][j];
    }
    void afisare_FW()
    {
        for (int i = 1; i <= noduri; i++)
        {
            for (int j = 1; j <= noduri; j++)
                out << adiacenta[i][j] << " ";
            out << "\n";
        }
    }
    
    //Diametrul unui arbore

    void citire_arbore()
    {
        in >> noduri;
        okey.resize(noduri + 1);
        for (int i = 1; i < noduri; i++)
            adiacenta[i].resize(noduri + 1);
        for (int i = 1; i < noduri; i++)
        {
            int x, y;
            in >> x >> y;
            adiacenta[x].push_back(y);
            adiacenta[y].push_back(x);
            okey.push_back(0);
        }
        okey.push_back(0);
    }
    void DFS_arbore(int nod, int distanta)
    {
        okey[nod] = 1;
        if (distanta > maxim)
        {
            maxim = distanta;
            start = nod;
        }
        okey[nod] = 1;
        for (int i = 0; i < adiacenta[nod].size(); i++)
            if (!okey[adiacenta[nod][i]])
                DFS_arbore(adiacenta[nod][i], distanta + 1);
        //okey[nod] = 0;
    }
    void afisare_diametru()
    {
        /*for (int i = 0; i < noduri; i++)
            DFS_arbore(i, 0);
        out << maxim + 1;*/
        DFS_arbore(1, 0);
        for (int i = 1; i <= noduri; i++)
            okey[i] = 0;
        maxim = 0;
        DFS_arbore(start, 0);
        out << maxim + 1; 
    }
    
    //Flux maxim
    
    void citire_flux()
    {
        in >> noduri >> muchii;
        for (int i = 1; i < muchii; i++)
            adiacenta[i].resize(noduri + 1);
        int x, y, cost;
        while (in >> x >> y >> cost)
            adiacenta[x][y] = cost;
    }
    int bfs_flux(vector<int> Fluxuri[1000], vector<int>& vizitat, vector<int>& coada, vector<int>& distanta)
    {
        int primul = 1, ultimul = 1;
        coada[primul] = 1;
        vizitat[1] = -1;
        distanta[1] = 100000;
        while (primul <= ultimul)
        {
            for (int i = 1; i <= noduri; i++)
                if (!vizitat[i] && adiacenta[coada[primul]][i] - Fluxuri[coada[primul]][i] > 0)
                {
                    vizitat[i] = coada[primul];
                    coada[++ultimul] = i;
                    if (distanta[coada[primul]] < adiacenta[coada[primul]][i] - Fluxuri[coada[primul]][i])
                        distanta[i] = distanta[coada[primul]];
                    else
                        distanta[i] = adiacenta[coada[primul]][i] - Fluxuri[coada[primul]][i];
                    if (i == noduri)
                        return 0;
                }
            primul++;
        }
    }
    void afisare_flux()
    {
        vector<int> Fluxuri[1000], vizitat(noduri + 1, 0), coada(noduri + 1, 0), distanta(noduri + 1, 0);
        for (int i = 0; i < muchii; i++)
            Fluxuri[i].resize(noduri + 1);
        for (int i = 0; i < muchii; i++)
            Fluxuri[i].push_back(0);
        int x, y, minim, flux = 0;
        do
        {
            for (int i = 1; i <= noduri; i++)
                distanta[i] = vizitat[i] = coada[i] = 0;
            bfs_flux(Fluxuri, vizitat, coada, distanta);
            if (vizitat[noduri])
            {
                minim = 100000;
                x = noduri;
                y = vizitat[x];
                minim = distanta[noduri];
                while (y != -1)
                {
                    Fluxuri[y][x] += minim;
                    Fluxuri[x][y] -= minim;
                    x = y;
                    y = vizitat[x];
                }
                flux += minim;
            }
        } while (vizitat[noduri]);
        out << flux;
    }

    //Ciclu Eulerian

    void citire_Euler()
    {
        in >> noduri >> muchii;
        okey.resize(noduri + 1);

        for (int i = 0; i <= noduri; i++)
        {
            adiacenta[i].resize(noduri + 1);
            pozitii[i].resize(noduri + 1);
        }

        for (int i = 0; i <= noduri; i++)
        {
            okey.push_back(0);
            adiacenta[i].push_back(0);
            pozitii[i].push_back(0);
        }

        for (int i = 1; i <= muchii; i++)
        {
            int x, y;
            in >> x >> y;
            adiacenta[x].push_back(y);
            adiacenta[y].push_back(x);
            pozitii[x].push_back(i);
            pozitii[y].push_back(i);
        }
    }
    void dfs_Euler(int x, vector<int> &vizite, vector<int> &ciclu_euler)
    {
        while (!adiacenta[x].empty())
        {
            int vecin = adiacenta[x].back();
            int pozitie = pozitii[x].back();

            adiacenta[x].pop_back();
            pozitii[x].pop_back();

            if (vizite[pozitie] == 0)
            {
                vizite[pozitie]++;
                dfs_Euler(vecin, vizite, ciclu_euler);
            }
        }
        ciclu_euler.push_back(x);
    }
    void afisare_Euler()
    {
        vector<int> vizite(muchii + 1, 0);
        vector<int> ciclu_euler;
        for (int i = 1; i <= noduri; i++)
            if (adiacenta[i].size() % 2 != 0)
            {
                out << "-1\n";
                return;
            }

        dfs_Euler(1, vizite, ciclu_euler);

        for (int i = 1; i < ciclu_euler.size() - 1; i++)
            out << ciclu_euler[i] << " ";
    }

    //Ciclu Hamiltonian

    void citire_Hamilton()
    {
        in >> noduri >> muchii;
        minim = 100000000;

        for (int i = 0; i <= noduri; i++)
        {
            okey.resize(noduri + 1);
            adiacenta[i].resize(noduri + 1);
        }
            
        for (int i = 1; i <= muchii; i++)
        {
            int x, y, c;
            in >> x >> y >> c;
            adiacenta[x][y] = c;
        }
    }
    int vizitate(vector<int> okey)
    {
        for (int i = 1; i < noduri; i++)
            if (okey[i] == 0)
                return 0;
        return 1;
    }
    void verificare(int nod)
    {
        if (vizitate(okey) && adiacenta[nod][0] > 0)
        {
            suma += adiacenta[nod][0];
            minim = min(minim, suma);
            suma -= adiacenta[nod][0];
            return;
        }

        for (int j = 1; j <= noduri; j++)
            if (!okey[j] && adiacenta[nod][j] > 0)
            {
                okey[j] = 1;
                suma += adiacenta[nod][j];
                verificare(j);
                suma -= adiacenta[nod][j];
                okey[j] = 0;
            }
    }
    void afisare_Hamilton()
    {
        verificare(0);
        if (minim != 100000000)
            out << minim << "\n";
        else
            out << "Nu exista solutie\n";
    }
};
int main()
{
    Graf g;
    int nr_problema;
    cout << "Lista cu probleme:\n";
    cout << "1-DFS\n";
    cout << "2-BFS\n";
    cout << "3-Havel Hakimi\n";
    cout << "4-Componente Tare Conexe\n";
    cout << "5-Sortare Topologica\n";
    cout << "6-Conexiune Critica\n";
    cout << "7-Componente Biconexe\n";
    cout << "8-Arbore Partial de Cost Minim\n";
    cout << "9-Dijkstra\n";
    cout << "10-Bellman-Ford\n";
    cout << "11-Paduri de Multimi Disjuncte\n";
    cout << "12-Floyd-Warshall\n";
    cout << "13-Diametrul unui Arbore\n";
    cout << "14-Flux Maxim\n";
    cout << "15-Ciclu Eulerian\n";
    cout << "16-Ciclu Hamiltonian\n";
    cout << "Introduceti numarul problemei de rezolat:";
    cin >> nr_problema;
    if (nr_problema == 1)
    {
        g.citire_DFS();
        g.afisare_DFS();
        /*
        6 3
        1 2
        1 4
        3 5
        */
    }
    else if (nr_problema == 2)
    {
        g.BFS();
        /*
        5 7 2
        1 2
        2 1
        2 2
        3 2
        2 5
        5 3
        4 5
        */
    }
    else if (nr_problema == 3)
    {
        g.HH();
    }
    else if (nr_problema == 4)
    {
        g.CTC();
        /*
            8 12
            1 2
            2 6
            6 7
            7 6
            3 1
            3 4
            2 3
            4 5
            5 4
            6 5
            5 8
            8 7
            */
    }
    else if (nr_problema == 5)
    {
        g.citire_DFS();
        g.ST();
        /*
            9 8
            1 2
            1 3
            3 4
            3 5
            5 9
            4 6
            4 7
            4 8
            */
    }
    else if (nr_problema == 6)
    {
        //vector<vector<int>> aux;
        //aux = g.criticalConnections(4, { {0, 1} ,{1, 2},{2, 0},{1, 3} });
        cout << "Vizitati leetcode pentru a verifica aceasta problema";
    }
    else if (nr_problema == 7)
    {
        cout << "Problema aceasta nu a fost adaugata inca";
    }
    else if (nr_problema == 8)
    {
        /*
        9 14
        1 2 10
        1 3 -11
        2 4 11
        2 5 11
        5 6 13
        3 4 10
        4 6 12
        4 7 5
        3 7 4
        3 8 5
        8 7 5
        8 9 4
        9 7 3
        6 7 11
        */
        g.APM();
    }
    else if (nr_problema == 9)
    {
        /*
        5 6
        1 2 1
        1 4 2
        4 3 4
        2 3 2
        4 5 3
        3 5 6
        */
        g.Djk();
    }
    else if (nr_problema == 10)
    {
        /*
        5 8
        1 3 -3
        1 5 7
        3 2 -2
        3 4 7
        5 1 4
        5 2 3
        5 3 4
        4 5 3
        */
        g.BF();
    }
    else if (nr_problema == 11)
    {
        /*
        4 6
        1 1 2
        1 3 4
        2 1 3
        2 1 2
        1 1 3
        2 1 4
        */
        g.Dis();
    }
    else if (nr_problema == 12)
    {
        /*
        5
        0 3 9 8 3
        5 0 1 4 2
        6 6 0 4 5
        2 9 2 0 7
        7 9 3 2 0
        */
        g.citire_FW();
        g.FW();
        g.afisare_FW();
    }
    else if (nr_problema == 13)
    {
        /*
        11
        1 2
        1 3
        1 4
        2 5
        3 6
        4 7
        5 8
        5 9
        6 10
        10 11
        */
        g.citire_arbore();
        g.afisare_diametru();
    }
    else if (nr_problema == 14)
    {
        /*
        4 5
        1 2 3
        1 3 5
        2 4 6
        3 4 4
        3 2 3
        */
        g.citire_flux();
        g.afisare_flux();
    }
    else if (nr_problema == 15)
    {
        /*
        4 6
        1 2
        1 3
        2 2
        2 3
        3 4
        3 4
        */
        g.citire_Euler();
        g.afisare_Euler();
    }
    else if (nr_problema == 16)
    {
    /*
    5 10
    0 1 9
    0 3 8
    1 0 7
    1 2 1
    1 4 3
    2 0 5
    2 4 4
    3 2 6
    4 3 7
    4 1 1
    */
    g.citire_Hamilton();
    g.afisare_Hamilton();
    }
    cout << "\nProblema " << nr_problema << " a fost rezolvata, verificati in date.out ce s-a afisat\n";
    in.close();
    out.close();
    return 0;
}