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
    vector<int> adiacenta[1000];
    vector<vector<int>> lista;
public:
    //DFS
    void citire_DFS()
    {
        int x, y;
        cin >> noduri >> muchii;
        lista.resize(noduri + 1);
        for (int i = 1; i <= muchii; i++)
        {
            cin >> x >> y;
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
        cout << nr;
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
    //Conexiune critica
    void DFS_3(int timp, vector<vector<int>>& v, vector<int>& numarare, int k, int parinte, vector<bool>& vizite, vector<int>& vecin)
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
    cout << "5-Sortare topologica\n";
    cout << "6-Conexiune critica\n";
    cout << "7-Componente biconexe\n";
    cout << "Introduceti numarul problemei de rezolat:";
    cin >> nr_problema;
    if (nr_problema == 1)
    {
        g.citire_DFS();
        g.afisare_DFS();
    }
    else if (nr_problema == 2)
    {
        g.BFS();
    }
    else if (nr_problema == 3)
    {
        g.HH();
    }
    else if (nr_problema == 4)
    {
        g.CTC();
    }
    else if (nr_problema == 5)
    {
        g.citire_DFS();
        g.ST();
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
    in.close();
    out.close();
    return 0;
}