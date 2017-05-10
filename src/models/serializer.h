#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <QtXml>

#include "node.h"
#include "lexicalpair.h"

void serialize(Node<LexicalPair> *node, QDomDocument *document, QDomElement *root = nullptr);
// Node<T> *deserialize(QDomDocument *document);

#endif // __SERIALIZER_H__
