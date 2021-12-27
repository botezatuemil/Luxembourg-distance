#include "graf.h"
#include "mainwindow.h"
#include "qDebug"
#include "QMessageBox"
#include <random>
#include "Arc.h"
#include <fstream>
#include <sstream>
#include <queue>

void Graf::GenerareMatriceAdiacenta()
{

    matriceAdiacenta.resize(getNumberofNodes());
    for (int i = 0; i < getNumberofNodes(); ++i) {
        matriceAdiacenta[i].resize(getNumberofNodes(), 0);
    }

    for (auto& arc : arce) {
        int i = arc.getFirstPoint().getNumber();
        int j = arc.getSecondPoint().getNumber();   
        matriceAdiacenta[i][j] = 1;

      }
}

void Graf::GenerareListaAdiacenta()
{
    listaAdiacentaRad.resize(noduri.size());

    for (auto& arc : arce) {
        if (arc.getFirstPoint().getNumber() != arc.getSecondPoint().getNumber())
            listaAdiacentaRad[arc.getFirstPoint().getNumber()].push_back(arc.getSecondPoint());
    }

}

void Graf::setArce(std::vector<Arc> arce)
{
    this->arce = arce;
}

void Graf::setNoduri(std::vector<Node> noduri)
{
    this->noduri = noduri;
}

std::vector<std::vector<std::pair<Node, int>>> Graf::getListaAdiacenta()
{
    return listaAdiacenta;
}

std::vector<std::vector<Node>> Graf::getListaAdiacentaRad()
{
    return listaAdiacentaRad;
}

std::vector<std::vector<Node>> Graf::getListaInversaAdiacenta()
{
    return listaInversaAdiacenta;
}

std::vector<Arc> Graf::GetArce()
{
    return arce;
}

std::vector<Node> Graf::GetNoduri()
{
    return noduri;
}

std::vector<Node> Graf::GetNoduriTareConexe()
{
    return noduriTareConexe;
}

std::vector<Arc> Graf::GetArceConexe()
{
    return arceConexe;
}

void Graf::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graf::AddArc(Arc n)
{
    arce.push_back(n);
}

Node Graf::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graf::getNumberofNodes()
{
    return noduri.size();
}

bool Graf::verifyDistance(QPointF p)
{
    for (auto& nod : noduri) {
        if (fabs(nod.getPoint().x() - p.x()) < 40 && fabs(nod.getPoint().y() - p.y()) < 40) {
            return false;
        }
    }
    return true;
}

bool Graf::verificareMultiGraf(Node firstNode, Node secondNode)
{
    for(auto &a:arce)
    {
        if(a.getFirstPoint().getNumber() == firstNode.getNumber()
                &&
           a.getSecondPoint().getNumber() == secondNode.getNumber())

        {
            return false;
        }

    }
    return true;
}

void Graf::gasireMinMax()
{
     std::ifstream in("C:\\Emil\\Cursuri\\Anul2\\Semestrul1\\AG\\Tema6\\Harta_Luxemburg.txt");
     longmax = INT_MIN, longmin = INT_MAX, latmax = INT_MIN, latmin = INT_MAX;
     while (!in.eof()) {

         std::string string1, string2, string3, string4, string5;
         int index, longitude, latitude;

         in >> string1 >> string2 >> index >> string3 >> longitude >> string4 >> latitude >> string5;

         if (string1 == "<node") {

             if (longitude > longmax) {
                 longmax = longitude;
             }
             if (longitude < longmin){
                 longmin = longitude;
             }
             if (latitude > latmax) {
                 latmax = latitude;
             }
             if (latitude < latmin) {
                 latmin = latitude;
             }
         }

     }
     in.close();

}

void Graf::adaugareNoduri(int height, int width)
{
    std::ifstream in("C:\\Emil\\Cursuri\\Anul2\\Semestrul1\\AG\\Tema6\\Harta_Luxemburg.txt");

    std::ofstream out("C:\\Emil\\Cursuri\\Anul2\\Semestrul1\\AG\\Tema6\\out.txt");

    std::string line;
    int number;
    listaAdiacenta.resize(42314);
    int indexArc = 0;

    while (!in.eof()) {


        std::string string1, string2, string3, string4, string5;
        int index, longitude, latitude;

        in >> string1 >> string2 >> index >> string3 >> longitude >> string4 >> latitude >> string5;


        if (string1 == "<node") {

            float divider = 300;
            float x = width / ((longmax - longmin) / divider) * ((longitude - longmin) / divider);
            float y = height / ((latmax - latmin) / divider) * ((latmax - latitude) / divider);
            noduri.push_back(QPointF(x, y));
            noduri[index].setNumber(index);
        }
        else if (string1 == "<arc") {

            arce.push_back(Arc(noduri[index], noduri[longitude]));
            arce[indexArc].setLength(latitude);

            listaAdiacenta[index].push_back(std::make_pair(noduri[longitude], latitude));
            indexArc++;
        }

    }

}

void Graf::Dijkstra(Node firstNode, Node secondNode)
{

        std::ofstream out("C:\\Emil\\Cursuri\\Anul2\\Semestrul1\\AG\\Tema6\\out.txt");
        std::priority_queue< std::pair<int, int>, std::vector <std::pair<int, int>> , std::greater<std::pair<int, int>> > pq;


        std::vector<int> dist(noduri.size(), INT_MAX);

        pq.push(std::make_pair(0, firstNode.getNumber()));
        dist[firstNode.getNumber()] = 0;


        while (!pq.empty() && pq.top().second != secondNode.getNumber())
        {

            int top = pq.top().second;
            pq.pop();

            for (auto& pair : listaAdiacenta[top])
            {

                int v = pair.first.getNumber();
                int weight = pair.second;

                if (dist[v] > dist[top] + weight)
                {
                    dist[v] = dist[top] + weight;
                    pq.push(std::make_pair(dist[v], v));

                }
            }
       }

        Node elem = secondNode;

        while (elem.getNumber() != firstNode.getNumber()) {

            int costMin = INT_MAX;
            Node newNode;

             for (auto& pair : listaAdiacenta[elem.getNumber()]) {
                 if (dist[pair.first.getNumber()] < costMin) {
                     costMin = dist[pair.first.getNumber()];
                     newNode = pair.first;
                 }
             }

            int pos = 0;
            for (int i = 0; i < arce.size(); ++i) {
                if (arce[i].getFirstPoint().getNumber() == elem.getNumber() && arce[i].getSecondPoint().getNumber() == newNode.getNumber()) {
                    arce[i].setMarcat(true);
                    break;
                }
            }

            elem = newNode;
        }

}

void Graf::DFS(Node node, std::vector<bool>&marcat)
{
    marcat[node.getNumber()] = true;

    for (auto vecin : listaAdiacentaRad[node.getNumber()]) {
        if (!marcat[vecin.getNumber()]) {
            DFS(vecin, marcat);
        }
    }
}

void Graf::gasireRadacina()
{
    std::vector<bool>marcat(noduri.size(), false);
    GenerareListaAdiacenta();
    //noduri.clear();
    //arce.clear();

    int v;

    for (auto& nod : noduri) {
        if (!marcat[nod.getNumber()]) {
            DFS(nod, marcat);
            v = nod.getNumber();
        }
    }

    std::fill(marcat.begin(), marcat.end(), false);
    DFS(noduri[v], marcat);

    for (int i = 0; i < noduri.size(); ++i) {
        if (!marcat[i]) {
            v = -1;
        }
    }

    if(v == -1) {
            QMessageBox messageBox;
            messageBox.critical(0, "Root not found", "GRAFUL NU ARE RADACINA!");
            messageBox.setFixedSize(800, 700);
            //noduri.clear();
            //arce.clear();
        }
        else {
            QMessageBox messageBox;
            messageBox.critical(0, "Root found!", "Radacina grafului este " + QString::number(v));
            messageBox.setFixedSize(800, 700);
            //noduri.clear();
            //arce.clear();
        }
}

void Graf::print()
{
    std::ofstream out("C:\\Emil\\Cursuri\\Anul2\\Semestrul1\\AG\\Tema6\\out.txt");

   for (int i = 0; i < listaAdiacenta.size(); ++i) {
       out << i << " => ";
       for (auto pair : listaAdiacenta[i]) {

            out << pair.first.getNumber() << " " << pair.second << " " << "\n";
       }

   }
}


