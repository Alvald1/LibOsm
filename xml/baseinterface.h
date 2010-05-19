/*
    Copyright � 2010 par Marc Sibert

    This file is part of LIBOSM

    LIBOSM is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LIBOSM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with LIBOSM.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file
 * \author Marc Sibert
 */

#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

//class Changeset;
#include "../osm/changeset.h"
#include "../osm/node.h"

class Way;
class Relation;

/**
 * \interface BaseInterface
 * Classe virtuelle pure (interface) assurant la disponibilit� de 4 m�thodes
 * permettant stocker des instances d'OSM dans une base.
 */
class BaseInterface
{
  public:
/**
 * Ajouter un Changeset dans la base.
 * @param aChangeset Une r�f�rence sur une instance de Changeset � inserer.
 */
    virtual void add(const Changeset& aChangeset) = 0;

/**
 * Ajouter un Node dans la base.
 * @param aNode Une r�f�rence sur une instance de Node � inserer.
 */
    virtual void add(const Node& aNode) = 0;

/**
 * Ajouter un Way dans la base.
 * @param aWay Une r�f�rence sur une instance de Way � inserer.
 */
    virtual void add(const Way& aWay) = 0;

/**
 * Ajouter une Relation dans la base.
 * @param aRelation Une r�f�rence sur une instance de Relation � inserer.
 */
    virtual void add(const Relation& aRelation) = 0;

    virtual unsigned nbChangesets() const  = 0;

/**
 * Retourne de nombre de Nodes dans la base.
 */
    virtual unsigned nbNodes() const  = 0;
    virtual unsigned nbWays() const  = 0;
    virtual unsigned nbRelations() const  = 0;

};

#endif
