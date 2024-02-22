#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>






MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,const std::vector<IdPair>& edges){
   
   int sayac=0;
   vertices.resize(vertexPositions.size());
   adjList.resize(vertexPositions.size());
   while(sayac<vertexPositions.size()){
       vertices[sayac].id=sayac;
       vertices[sayac].position3D=vertexPositions[sayac];
       sayac++;
   }
   
   int agasayaci=0;
   while(agasayaci<edges.size()){
       Vertex* aga0=&vertices[edges[agasayaci].vertexId0];
       Vertex* aga1=&vertices[edges[agasayaci].vertexId1];
       adjList[edges[agasayaci].vertexId0].push_front(aga1);
       adjList[edges[agasayaci].vertexId1].push_front(aga0);
       agasayaci++;
   }
    for(int af=0;af<adjList.size();af++){
        adjList[af].sort();
    }
    
    
    
   
 
}







double MeshGraph::AverageDistanceBetweenVertices() const
{
    
    double generalsum=0;
    int paths=0;
    for(int i=0;i<adjList.size();i++){
        for(int j=0;j<adjList[i].size();j++){
            std::list<Vertex*>::const_iterator anno=adjList[i].begin();
            std::advance(anno,j);
            generalsum+=(*anno)->position3D.Distance((*anno)->position3D,vertices[i].position3D);
            paths++;
        }
    }   
    return generalsum/(paths);
    
   
    
}

double MeshGraph::AverageEdgePerVertex() const
{
   
    double generalsum=0;
    for(int i=0;i<adjList.size();i++){
        for(int j=0;j<adjList[i].size();j++){
            
            generalsum++;
        }
    }   
    return generalsum/(2*vertices.size());
    
}

int MeshGraph::TotalVertexCount() const
{
    return vertices.size();
    
}

int MeshGraph::TotalEdgeCount() const
{
    
    
    int paths=0;
    for(int i=0;i<adjList.size();i++){
        for(int j=0;j<adjList[i].size();j++){
            
            paths++;
        }
    }   
    return paths/2;
    
    
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    if(vertexId>=vertices.size()) return -1;
    int paths=0;
    //std::list<Vertex*> depo=adjList[vertexId];
   
    return int(adjList[vertexId].size());
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
  
    outVertexIds.resize(0);
    if(vertexId>=vertices.size()) return;
    
    for(int i=0;i<adjList[vertexId].size();i++){
        std::list<Vertex*>::const_iterator eheh=adjList[vertexId].begin();
        std::advance(eheh,i);
        outVertexIds.push_back((*eheh)->id);
    }
    
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    double sonsuz= INFINITY;
    std::vector<double> distance;
    BinaryHeap anno;
    distance.resize(vertices.size(),0);
    for(int i=0;i<vertices.size();i++){
        if(i==vertexIdFrom){
            distance[i]=0;
            continue;}
        distance[i]=sonsuz;
    }
    outputColorAllVertex.resize(vertices.size());
    for(int i=0; i<vertices.size();i++){
        outputColorAllVertex[i].r=0;
        outputColorAllVertex[i].g=0;
        outputColorAllVertex[i].b=0;
    }
    std::vector<int> isMarked;
    std::vector<int> previous;
    previous.resize(vertices.size(),-1);
    isMarked.resize(vertices.size(),0);
    anno.Add(vertexIdFrom,0.0);

    int e=0;
    while(anno.HeapSize()){
        int currid;
        double currw;
        anno.PopHeap(currid,currw);
        for(std::list<Vertex*>::const_iterator sayac3= adjList[currid].begin();sayac3!=adjList[currid].end();sayac3++){
             
   
                if(distance[(*sayac3)->id]> Double3::Distance(vertices[currid].position3D, (*sayac3)->position3D) + distance[currid]){
                    anno.Add((*sayac3)->id,Double3::Distance(vertices[currid].position3D,(*sayac3)->position3D)+distance[currid]);
                    previous[(*sayac3)->id]=currid;
                    distance[(*sayac3)->id]=Double3::Distance(vertices[currid].position3D,(*sayac3)->position3D)+distance[currid];
                    anno.ChangePriority((*sayac3)->id, Double3::Distance(vertices[currid].position3D,(*sayac3)->position3D)+distance[currid]);
                }
           
                
            
        }
        
    }
    int a=vertexIdTo;
 
    while(1){
        if (a==-1) break;
        outputColorAllVertex[a].r=color.r;
        outputColorAllVertex[a].g=color.g;
        outputColorAllVertex[a].b=color.b;
        a=previous[a];
        
        
    }
    

}




void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    if(vertexId>=vertices.size()||vertexId<0) return;
    
    BinaryHeap depo1;
    BinaryHeap depo2;
    std::vector<int> isVisited;
    std::vector<double> mesafeler;
    int u=0;
    int dumpid;
    double dumpw;
    double iter=0;
    mesafeler.resize(vertices.size(),0.0);
    isVisited.resize(vertices.size(),0);
    mesafeler[vertexId]=0;
    outputColorAllVertex.resize(vertices.size());
    for(int an=0;an<vertices.size();an++){
        outputColorAllVertex[an].r=0.0;
        outputColorAllVertex[an].g=0.0;
        outputColorAllVertex[an].b=0.0;
 
        
    }
    
    isVisited[vertexId]=1;

    
    int curid;
    outputColorAllVertex[vertexId].r=color.r;
    outputColorAllVertex[vertexId].g=color.g;
    outputColorAllVertex[vertexId].b=color.b;
    depo1.Add(vertexId,-1);
    for(int un=0;un<maxDepth;un++){
        
        double curw;
        while(depo1.HeapSize()){
            
            depo1.PopHeap(curid,curw);
            for(std::list<Vertex*>::const_iterator sayac2= adjList[curid].begin();sayac2!=adjList[curid].end();sayac2++){
                if(isVisited[(*sayac2)->id]==0){
                    mesafeler[(*sayac2)->id]=(Double3::Distance(vertices[(*sayac2)->id].position3D,vertices[curid].position3D)+mesafeler[curid]);
                    depo2.Add((*sayac2)->id,iter++);
                    isVisited[(*sayac2)->id]=1;
                    if(type==FILTER_GAUSSIAN){
                    outputColorAllVertex[(*sayac2)->id].r=color.r*exp(-1*(mesafeler[(*sayac2)->id]*mesafeler[(*sayac2)->id]/(alpha*alpha)));
                    outputColorAllVertex[(*sayac2)->id].g=color.g*exp(-1*(mesafeler[(*sayac2)->id]*mesafeler[(*sayac2)->id]/(alpha*alpha)));
                    outputColorAllVertex[(*sayac2)->id].b=color.b*exp(-1*(mesafeler[(*sayac2)->id]*mesafeler[(*sayac2)->id]/(alpha*alpha)));}
                    
                    
                    if(type==FILTER_BOX){
                        int carpan=0;
                        if(-1*alpha<=mesafeler[(*sayac2)->id] && alpha>=mesafeler[(*sayac2)->id]){
                        carpan=1;
                    }
                    outputColorAllVertex[(*sayac2)->id].r=color.r*carpan;
                    outputColorAllVertex[(*sayac2)->id].g=color.g*carpan;
                    outputColorAllVertex[(*sayac2)->id].b=color.b*carpan;
                        
                    }
                    
                }
        
            }
        
            
        }
   
        depo1=depo2;
        while(depo2.HeapSize()){
            
            depo2.PopHeap(dumpid,dumpw);
            //std::cout<<dumpw<<" ";
            
        }
        //std::cout<<"\n";
        
    }
    
   
}
    
       


void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    if(vertexId>=vertices.size()||vertexId<0) return;
  
  BinaryHeap depo1;
    BinaryHeap depo2;
    std::vector<int> isVisited;
    int u=0;
    int dumpid;
    double dumpw;
    double iter=0;
    isVisited.resize(vertices.size(),0);
    outputColorAllVertex.resize(vertices.size());
    for(int an=0;an<vertices.size();an++){
        outputColorAllVertex[an].r=0.0;
        outputColorAllVertex[an].g=0.0;
        outputColorAllVertex[an].b=0.0;
 
        
    }
    
    isVisited[vertexId]=1;

    
    int curid;
    outputColorAllVertex[vertexId].r=color.r;
    outputColorAllVertex[vertexId].g=color.g;
    outputColorAllVertex[vertexId].b=color.b;
    depo1.Add(vertexId,-1);
    for(int un=0;un<maxDepth;un++){
        
        double curw;
        while(depo1.HeapSize()){
            
            depo1.PopHeap(curid,curw);
            for(std::list<Vertex*>::const_iterator sayac2= adjList[curid].begin();sayac2!=adjList[curid].end();sayac2++){
                if(isVisited[(*sayac2)->id]==0){
                   
                    depo2.Add((*sayac2)->id,iter++);
                    isVisited[(*sayac2)->id]=1;
                    double mesafe=Double3::Distance(vertices[(*sayac2)->id].position3D,vertices[vertexId].position3D);
                    if(type==FILTER_GAUSSIAN){
                    outputColorAllVertex[(*sayac2)->id].r=color.r*exp(-1*(mesafe*mesafe/(alpha*alpha)));
                    outputColorAllVertex[(*sayac2)->id].g=color.g*exp(-1*(mesafe*mesafe/(alpha*alpha)));
                    outputColorAllVertex[(*sayac2)->id].b=color.b*exp(-1*(mesafe*mesafe/(alpha*alpha)));}
                    
                    if(type==FILTER_BOX){
                    int carpan=0;
                    if(-1*alpha<=mesafe && alpha>=mesafe){
                        carpan=1;
                    }
                    outputColorAllVertex[(*sayac2)->id].r=color.r*carpan;
                    outputColorAllVertex[(*sayac2)->id].g=color.g*carpan;
                    outputColorAllVertex[(*sayac2)->id].b=color.b*carpan;
                    }
                    
                }
        
            }
        
            
        }
   
        depo1=depo2;
        while(depo2.HeapSize()){
            
            depo2.PopHeap(dumpid,dumpw);
            //std::cout<<dumpw<<" ";
            
        }
        
        
    }
    
   
  
  
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}
