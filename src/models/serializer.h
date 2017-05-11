#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <QtXml>

#include "node.h"
#include "lexicalpair.h"

void serialize(Node<LexicalPair> *node, QDomDocument *document, QDomElement *root = nullptr);
Node<LexicalPair> *deserialize(QDomDocument *document, QDomElement *_nodeEl = nullptr);

#endif // __SERIALIZER_H__
