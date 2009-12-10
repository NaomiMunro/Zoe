#ifndef GENE_H
#define GENE_H

#include <QByteArray>
#include <QHash>

struct node
{
	char data;
	node *left;
	node *right;
};

typedef node* expTree;

class Gene
{
public:
	Gene(int headLength, int argNum);
	Gene(Gene&, QByteArray);
	~Gene();
	double express(int, int, int);
	int length();
	static void setupArgNums();
	Gene copy();
	QByteArray sequence();
	char lastMutation() {return m_lastMutation; };
	void printGene();
	
private:
	void buildTree();
	double evaluateTree(int a, int b, int c);
	double evaluate(expTree tree, int a, int b, int c);
	int lengthAux(int);
	void destroyTree(expTree);
	
	QByteArray m_gene;
	int m_codingLength;
	int m_headLength;
	QByteArray symbols;
	QByteArray arguments;
	expTree m_tree;
	static QHash<char, int> geneticFuncs;
	char m_lastMutation;
};

#endif
