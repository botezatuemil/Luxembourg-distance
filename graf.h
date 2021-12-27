#ifndef GRAF_H
#define GRAF_H
#include "node.h"
#include "Arc.h"
#include <math.h>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <stack>

class Graf
{
    std::vector<Node> noduri;
    std::vector<Node> noduriTareConexe;
    std::vector<Arc> arce;
    std::vector<Arc> arceConexe;
    std::vector<std::vector<int>> matriceAdiacenta;
    std::vector<std::vector<std::pair<Node, int>>> listaAdiacenta;
    std::vector<std::vector<Node>> listaAdiacentaRad;
    std::vector<std::vector<Node>> listaInversaAdiacenta;
    std::stack<Node>s;
    int longmax, longmin, latmax, latmin;
    //std::vector<int>vizitat;

public:
    void GenerareMatriceAdiacenta();
    void GenerareListaAdiacenta();

    void setArce(std::vector<Arc>arce);
    void setNoduri(std::vector<Node>noduri);
    std::vector<std::vector<std::pair<Node, int>>> getListaAdiacenta();
    std::vector<std::vector<Node>> getListaAdiacentaRad();
    std::vector<std::vector<Node>> getListaInversaAdiacenta();
    std::vector<Arc> GetArce();
    std::vector<Node> GetNoduri();
    std::vector<Node> GetNoduriTareConexe();
    std::vector<Arc> GetArceConexe();

    void AddNod(Node n);
    void AddArc(Arc a);
    void DrawGraf(QPainter *p);
    Node GetLastNode();
    int getNumberofNodes();

    bool verifyDistance(QPointF p);
    bool verificareMultiGraf(Node firstNode, Node secondNode);
    void gasireMinMax();
    void adaugareNoduri(int height, int width);
    void gasireApropiatNod();
    void Dijkstra(Node firstNode, Node secondNode);

    void DFS(Node node, std::vector<bool>&marcat);
    void gasireRadacina();
    void print();
};
#endif // GRAF_H
