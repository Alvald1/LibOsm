/*
 * Le droit d'auteur fran�ais s'applique � ce fichier, toutefois cette cr�ation
 * est mise � disposition selon le Contrat Paternit� 3.0 Unported disponible en
 * ligne http://creativecommons.org/licenses/by/3.0/ ou par courrier postal �
 * Creative Commons, 171 Second Street, Suite 300, San Francisco,
 * California 94105, USA.
 *
 * En aucun cas, l'auteur ne peut �tre tenu responsable de tous dommages directs
 * ou indirects ou encore d'un d�faut de fonctionnement de ce code source ou
 * d'un p�riph�rique r�sultant de l'utilisation de ce code source original ou
 * modifi�.
 *
 * Ce code source est fourni tel quel. Les demandes d'aide, de correction de bug
 * ou d'ajout de fonctionnalit� peuvent �tre demand�es, par contre, l'auteur ne
 * garantit pas la correction de ce bug ou l'ajout de fonctionnalit�.
 *
 */

/**
 * \file
 * \author Marc Sibert
 */

#include "../exception.h"
#include <cassert>
#include <iostream>
#include <expat.h>
#include "parsernd.h"
#include "parsernode.h"
#include "parserway.h"

ParserNd::ParserNd(XML_Parser *const apXML_Parser,
				   Parser *const apParent,
				   const string& aName,
				   const vector< pair<string, string> >& aAtts) :
	Parser(apXML_Parser, apParent)
{
	if (aAtts.size() != 1) throw Exception("Nombre d'attributs incorrect", __FILE__, __LINE__, __PRETTY_FUNCTION__);
	if (aAtts[0].first != "ref") throw Exception("Nom de l'attribut incorrect", __FILE__, __LINE__, __PRETTY_FUNCTION__);
    istringstream iss(aAtts[0].second);
    unsigned long val;
    iss >> val;
	dynamic_cast<ParserWay *const>(fpParent)->addNode(val);
}

void ParserNd::startElement(const string& aName,
                            const vector< pair<string, string> >& aAtts)
{
	throw Exception("Pas de sous-element attendu (" + aName + ")", __FILE__, __LINE__, __PRETTY_FUNCTION__);
}

void ParserNd::endElement(const string& aName)
{
	assert(aName == "nd");
}
