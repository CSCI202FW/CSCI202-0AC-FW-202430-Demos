#include "graph.h"

//new connected function.
bool connected(int index1, int index2){
    //make sure indexes are in range.
    if(index1 < 0 || index1 >= gSize || index2 < 0 || index2 >= gSize) {
        throw std::out_of_range("Index out of bounds");
    }
    //call our iterator to traverse the graph from the perspective of index1
    linkedListIterator<int> it;
    for (it = adjList[index1].begin(); it != adjList[index1].end(); ++it) {
        if (*it == index2) {
            return true;
        }
    }
    //double check from the perspective of index2
    for (it = adjList[index2].begin(); it != adjList[index2].end(); ++it) {
        if (*it == index1) {
            return true;
        }
    }

    return false;
}

graphType::graphType(int size)
{
    if (size >= 0)
    {
        maxSize = size;
    }
    else
    {
        maxSize = 0;
    }
    if (maxSize > 0)
    {
        graph.resize(maxSize);
    }
}

bool graphType::isEmpty() const
{
    return graph.empty();
}

void graphType::clearGraph()
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i].destroyList();
    }
    graph.clear();
    maxSize = 0;
}
void graphType::createGraph(std::string filename)
{
    std::ifstream fin(filename);
    int index = 0;
    int vertex = 0;
    int adjcentVertex = 0;
    if (!isEmpty())
    {
        clearGraph();
    }
    if (!fin.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }
    int gSize = 0;
    fin >> gSize;
    if (gSize > maxSize)
    {
        maxSize = gSize;
        graph.resize(maxSize);
    }
    for (index = 0; index < gSize; index++)
    {
        fin >> vertex;
        fin >> adjcentVertex;
        while (adjcentVertex != -999)
        {
            graph[vertex].insert(adjcentVertex);
            fin >> adjcentVertex;
        }
    }
    fin.close();
}

std::string graphType::printGraph()
{
    std::ostringstream out;
    // out << "digraph {" << std::endl; //comment this line out for python output keep for graphViz
    for (int i = 0; i < graph.size(); i++)
    {
        // three lines below for python ready output.
        out << i << " ";
        graph[i].print(out);
        out << std::endl;
        // comment out loop below for python keep for graphViz
        /* for (linkedListIterator<int> graphIt = graph[i].begin(); graphIt != graph[i].end(); ++graphIt)
        {
            out << i << "->" << *graphIt << ";" << std::endl;
        } */
    }
    /* out << std::endl; //graphViz output
    out << "}"; */
    return out.str();
}

std::string graphType::breadthFirstTraversal()
{
    linkedQueue<int> queue;
    bool *visited;
    visited = new bool[graph.size()];
    for (int i = 0; i < graph.size(); i++)
    {
        visited[i] = false;
    }
    std::string out = "";
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);
            visited[i] = true;
            out = out + " " + std::to_string(i) + " ";
            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                for (auto graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = *graphIt;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                        visited[w] = true;
                        out = out + " " + std::to_string(w) + " ";
                    }
                }
            }
        }
    }
    delete[] visited;
    return out;
}

std::string graphType::depthFirstTraversal()
{
    bool *visited;
    visited = new bool[graph.size()];
    std::string output = "";
    for (int i = 0; i < graph.size(); i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            dft(i, visited, output);
        }
    }
    delete[] visited;
    return output;
}

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    output = output + " " + std::to_string(v) + " ";
    linkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt;
        if (!visited[v])
        {
            dft(w, visited, output);
        }
    }
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited;
    visited = new bool[graph.size()];
    std::string output = "";
    for (int i = 0; i < graph.size(); i++)
    {
        visited[i] = false;
    }
    dft(vertex, visited, output);
    delete[] visited;
    return output;
}

graphType::graphType(const graphType &otherGraph)
{
    maxSize = 0;
    // gSize = 0;
    // graph = nullptr;
    copyGraph(otherGraph);
}

graphType::~graphType()
{
    clearGraph();
}

const graphType &graphType::operator=(const graphType &otherGraph)
{
    if (this != &otherGraph)
    {
        copyGraph(otherGraph);
    }
    return *this;
}

void graphType::copyGraph(const graphType &otherGraph)
{
    if (!this->isEmpty())
    {
        this->clearGraph();
    }

    this->maxSize = otherGraph.maxSize;
    // this->gSize = otherGraph.gSize;
    // this->graph = new unorderedLinkedList<int>[this->maxSize];
    graph.resize(otherGraph.graph.size());
    for (int i = 0; i < this->graph.size(); i++)
    {
        this->graph[i] = otherGraph.graph[i];
    }
}
