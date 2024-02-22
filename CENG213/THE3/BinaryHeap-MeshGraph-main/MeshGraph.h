#pragma once

#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "Structs.h"

struct Color
{
    unsigned char r, g, b;
};

struct Vertex
{
    int id;
    Double3 position3D;
};

enum FilterType
{
    FILTER_BOX,         // Box filter means that all the time weights are 1 in the range
    FILTER_GAUSSIAN     // Gaussian filter can be seen on here
};

class MeshGraph
{
    private:
    std::vector<Vertex>                 vertices;
    std::vector<std::list<Vertex*> >     adjList;
     /*void derinsokan(const std::list<Vertex*> liste, int derinlik, std::vector<int> visited)const {
        
        if(derinlik==0) return;        
        
        for(std::list<Vertex*>::const_iterator sayac2= liste.begin();sayac2!=liste.end();sayac2++){
            visited[(*sayac2)->id]= visited[(*sayac2)->id]+1;
            //std::cout<<(*sayac2)->id<<" ";
        }
        
        
        for(int sayac1=0; sayac1<liste.size();sayac1++){
        derinsokan(liste,derinlik-1,visited);}
        
    }*/
    
    void sirala(std::vector<Vertex*> vektor, Vertex source)const{
        int swapped=1;
        while(swapped){
            swapped=0;
            for(int s1=0; s1<vektor.size()-1;s1++){
                if(Double3::Distance(source.position3D,vektor[s1]->position3D)>Double3::Distance(source.position3D,vektor[s1+1]->position3D)){
                    swapped=1;
                    Vertex* temp=vektor[s1];
                    vektor[s1]=vektor[s1+1];
                    vektor[s1+1]=temp;
                }
            }
            
        }
    }
    
   
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /* void Graph::reset_vectors() {
    for (int v = 0 ; v < Vcnt ; v++) {
        distance[v] = INT_MAX;
        mark[v] = false;
        previous[v] = -1;
    }
}
    
    
    void Graph::BFS(int s) {
    queue<int> q;
    vector<int> adjNodes;
    reset_vectors();
    distance[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        adjNodes = adjNodesOf(v);
        for (int w = 0; w < adjNodes.size(); w++) {
            if (distance[adjNodes[w]] == INT_MAX) {
                distance[adjNodes[w]] = distance[v] + 1;
                previous[adjNodes[w]] = v;
                q.push(adjNodes[w]);
            }
        }
    }
}*/
    
/////////////////////////////////////////////////////////////////////////////////////////////////////
   
    
    

    protected:
    public:
    // Constructors & Destructor
                        MeshGraph(const std::vector<Double3>& vertexPositions,
                                  const std::vector<IdPair>& edges);


    // Functionality
    // Small functionality
    double              AverageDistanceBetweenVertices() const;
    double              AverageEdgePerVertex() const;
    int                 TotalVertexCount() const;
    int                 TotalEdgeCount() const;
    int                 VertexEdgeCount(int vertexId) const;

    void                ImmediateNeighbours(std::vector<int>& outVertexIds,
                                            int vertexId) const;

    // Big functionalities
    void                PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                             int vertexIdFrom, int vertexIdTo,
                                             const Color& color) const;
    void                PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                             int vertexId, const Color& color,
                                             int maxDepth, FilterType type, double alpha) const;
    void                PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                              int vertexId, const Color& color,
                                              int maxDepth, FilterType type, double alpha) const;

    static void WriteColorToFile(const std::vector<Color>& colors, const std::string& fileName);
    static void PrintColorToStdOut(const std::vector<Color>& colors);
};
