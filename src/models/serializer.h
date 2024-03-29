#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <QtXml>

#include "andortree.h"
using kkcs::AndOrTree;

#include "node.h"
using kkcs::Node;

#include "lexicalpair.h"
using kkcs::LexicalPair;

void serialize(Node<LexicalPair> *node, QDomDocument *document, QDomElement *root = nullptr);
Node<LexicalPair> *deserialize(QDomDocument *document, QDomElement *_nodeEl = nullptr, Node<LexicalPair> *parent = nullptr);
AndOrTree<LexicalPair> *readTree(const QString filename);
void writeTree(AndOrTree<LexicalPair> *tree, const QString filename);

#endif // __SERIALIZER_H__
