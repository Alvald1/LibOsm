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

#include "parser.h"
#include "../exception.h"
#include <cassert>
#include <iostream>
#include <expat.h>


Parser::Parser(XML_Parser *const apXML_Parser,
               Parser *const apParent) :
	fpXML_Parser(apXML_Parser),
	fpParent(apParent),
	fpEnfant(0)
{
	assert(fpXML_Parser);
	XML_SetUserData(*fpXML_Parser, static_cast<void*>(this));
}

Parser::~Parser()
{
	if (fpParent)
		XML_SetUserData(*fpXML_Parser, static_cast<void*>(fpParent));
  else
		XML_SetUserData(*fpXML_Parser, 0);
}

void Parser::startElementHandler(void *userData,
																 const XML_Char *name,
		                             const XML_Char **atts)
{
	Parser *const p = static_cast<Parser*>(userData);
	assert(p);
	vector< pair<string,string> > attributs;
	while (*atts) {
		const string k = *(atts++);
		assert(*atts);
		const string v = *(atts++);
		attributs.push_back(make_pair(k,v));
	}
	p->startElement(name, attributs);
}

void Parser::endElementHandler(void *userData,
                               const XML_Char *name)
{
	Parser *const p = static_cast<Parser*>(userData);
	assert(p);
	p->endElement(name);
	delete p;
}

