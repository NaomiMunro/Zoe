#include "gene.h"
#include "zoedata.h"
#include "kdebug.h"
#include <cmath>
#include <QQueue>

QHash<char, int> Gene::geneticFuncs;
void Gene::setupArgNums() {
	geneticFuncs.insert('+', 2);
	geneticFuncs.insert('-', 2);
	geneticFuncs.insert('/', 2);
	geneticFuncs.insert('*', 2);
	geneticFuncs.insert('Q', 1);
}
	
Gene::Gene(int headLength, int argNum)
	: symbols("Q*/+-")
{
	m_headLength = headLength;
	int tailLength = headLength + 1;
	
	for (int i = 0; i < argNum; i++)
	{
		arguments.append(i + Zoe::arg_offset);
	}
		
	symbols.append(arguments);
	
	for (int h = 0; h <headLength; h++)
	{
		m_gene.append(symbols.at(rand() % (symbols.size())));
	}
	
	for (int t = 0; t <tailLength; t++)
	{
		m_gene.append(arguments.at(rand() % argNum));
	}
	
	m_codingLength = length();
	
}

Gene::Gene(Gene &oldGene, QByteArray newGene)
	: m_gene(newGene),
	  m_codingLength(oldGene.m_codingLength),
	  m_headLength(oldGene.m_headLength),
	  symbols(oldGene.symbols),
	  arguments(oldGene.arguments)
{
	m_codingLength = length();
}

Gene::~Gene()
{
	destroyTree(m_tree);
}

void Gene::destroyTree(expTree tree)
{
	if (tree !=NULL) {
		destroyTree(tree->left);
		destroyTree(tree->right);
		delete tree;
	}
}

double Gene::express(int a, int b, int c)
{
	m_tree = new node;
	buildTree();
	double result = evaluateTree(a, b, c);
	return result;
}

void Gene::buildTree()  // modified level order traversal
{
	QQueue<expTree> q;
	int index = 0;
	m_tree->data = m_gene.at(index);
	q.enqueue(m_tree);
	while (q.size() != 0) {
		expTree temp = q.dequeue();
		temp->data = m_gene.at(index);
		int args = geneticFuncs.value(m_gene.at(index));
		if (args == 1) {
			expTree left = new node();
			temp->left = left;
			temp->right = NULL;
			q.enqueue(left);
		} else if (args == 2) {
			expTree left = new node();
			expTree right = new node();
			temp->left = left;
			temp->right = right;
			q.enqueue(left);
			q.enqueue(right);
		} else {
			temp->left = NULL;
			temp->right = NULL;
		}
		index++;
	}
}

double Gene::evaluateTree(int a, int b, int c)
{
	 return evaluate(m_tree, a, b, c);
}

double Gene::evaluate(expTree tree, int a, int b, int c)
{
	switch (tree->data)
	{
		case 'Q':
				return sqrt(evaluate(tree->left, a, b, c)); break;
		case '+':
				return evaluate(tree->left, a, b, c) + evaluate(tree->right, a, b, c); break;
		case '-':
				return evaluate(tree->left, a, b, c) - evaluate(tree->right, a, b, c); break;
		case '/':
				return evaluate(tree->left, a, b, c) / evaluate(tree->right, a, b, c); break;
		case '*':
				return evaluate(tree->left, a, b, c) * evaluate(tree->right, a, b, c); break;
		case 'a':
				return a; break;
		case 'b':
				return b; break;
		case 'c':
				return c; break;
	}
	return 1;  //shouldn't happen, but keeps compiler happy
}

int Gene::length() 
{
	return lengthAux(0);
}

int Gene::lengthAux(int index) 
{
	int args = 1; //geneticFuncs.value(m_gene.at(index));
	while (args) {
		int next_args = 0;
		for (int i = 0; i < args; i++) {
			if (geneticFuncs.contains(m_gene.at(index)))
			{
				next_args += geneticFuncs.value(m_gene.at(index));
			}
			index++;
		}
		
		args = next_args;
	}
	return index;
}

Gene Gene::copy()
{
	QByteArray newCopy(m_gene);
	int mutationSite = rand() % newCopy.size();
	char mutation;
	if (mutationSite < m_headLength)
		mutation = symbols.at(rand() % symbols.size());
	else mutation = arguments.at(rand() % arguments.size());
	
	m_lastMutation = mutation;
	newCopy[mutationSite] = mutation;
	return Gene(*this, newCopy);
}

QByteArray Gene::sequence()
{
	return m_gene;
}

void Gene::printGene()
{
	kDebug() << "Gene: " << m_gene << ", Length: " << m_codingLength;
}
