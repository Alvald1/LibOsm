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

#ifndef BASEOSM_H
#define BASEOSM_H

#include "basesqlite3.h" // inheriting class's header file
#include "xml/baseinterface.h"
#include "osm/way.h"
#include "osm/member.h"

/**
 * Classe permettant d'instancier une base de donn�es contenant les diff�rents
 * �l�ments d'OSM.
 * Elle h�rite de BaseSQLite3 pour ses primitives, et de l'interface
 * BaseInterface pour �tre utilisable par le parseur XML qui va y ins�rer les
 * �l�ments.
 */
class BaseOsm : public BaseSQLite3, public BaseInterface
{
    private:
/// Commande pr�compil�e pour lire un enregistrement depuis la table tag.
        Commande fSelectTag;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table tag.
        Commande fInsertTag;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table changeset.
        Commande fInsertChangeset;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table changeset_tags.
        Commande fInsertChangesetTags;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table node.
        Commande fInsertNode;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table node_tags.
        Commande fInsertNodeTags;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table way.
        Commande fInsertWay;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table way_tags.
        Commande fInsertWayTags;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table way_nodes.
        Commande fInsertWayNodes;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table relation.
        Commande fInsertRelation;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table relation_tags.
        Commande fInsertRelationTags;

/// Commande pr�compil�e pour ajouter un enregistrement dans la table relation_members.
        Commande fInsertRelationMembers;

/// Nombre de Changeset.
        unsigned fNbChangesets;

/// Nombre de Node.
        unsigned fNbNodes;

/// Nombre de Way.
        unsigned fNbWays;

/// Nombre de Changeset.
        unsigned fNbRelations;

/**
 * Cr�e toutes les tables dans la base courante.
 */
        void createTables();

/**
 * Cr�e toutes les statments.
 */
        void createStatments();

/**
 * M�thode statique qui est appel�e r�guli�rement par le moteur SQLite3 afin
 * d'afficher la progression de l'application.
 * Pour le moment cette m�thode est sans action.
 * \param apBaseOsm Un pointeur sur l'instance courante de BaseOsm.
 * \return Une valeur <> 0 provoque l'arr�t du moteur SQLite.
 */
        static int progress(void *const apBaseOsm);

/**
 * Retourne l'identifiant d'une paire Key, Value et cr�e cette paire si elle
 * n'existe pas.
 * \param aKey Une cha�ne contenant la cl� du Tag
 * \param aValue Une cha�ne contenant la valeur du Tag.
 * \return Un entier unique pour la paire cl� / valeur.
 */
        unsigned long getIdTag(const string& aKey,
                               const string& aValue);


    protected:
/**
 * Ajoute un enregistrement dans la table Changeset.
 * \param aChangeset Une r�f�rence sur un Changeset.
 */
        void insertChangeset(const Changeset& aChangeset);

/**
 * Ajoute les enregistrements n�cessaires dans la table ChangesetTags.
 * \param aTop Une r�f�rence sur un Changeset.
 * \param aTags Une r�f�rence sur une liste de Tag associ�s.
 */
        void insertChangesetTags(const Top& aTop,
                                 const Top::ListeTags& aTags);

/**
 * Ajoute un enregistrement dans la table Node.
 * \param aNode Une r�f�rence sur un Node.
 */
        void insertNode(const Node& aNode);

/**
 * Ajoute les enregistrements n�cessaires dans la table NodeTags.
 * \param aTop Une r�f�rence sur un Node.
 * \param aTags Une r�f�rence sur une liste de Tag associ�s.
 */
        void insertNodeTags(const Top& aTop,
                            const Top::ListeTags& aTags);

/**
 * Ajoute un enregistrement dans la table Way.
 * \param aWay Une r�f�rence sur un Way.
 */
        void insertWay(const Way& aWay);

/**
 * Ajoute les enregistrements n�cessaires dans la table WayTags.
 * \param aTop Une r�f�rence sur un Way.
 * \param aTags Une r�f�rence sur une liste de Tag associ�s.
 */
        void insertWayTags(const Top& aTop,
                           const Top::ListeTags& aTags);

/**
 * Ajoute les enregistrements n�cessaires dans la table WayNodes.
 * \param aTop Une r�f�rence sur un Way.
 * \param aNodes Une r�f�rence sur une liste de Node associ�s.
 */
        void insertWayNodes(const Top& aTop,
                            const Way::ListeNodes& aNodes);

/**
 * Ajoute un enregistrement dans la table Relation.
 * \param aRelation Une r�f�rence sur une Relation.
 */
        void insertRelation(const Relation& aRelation);

/**
 * Ajoute les enregistrements n�cessaires dans la table RelationTags.
 * \param aTop Une r�f�rence sur une Relation.
 * \param aTags Une r�f�rence sur une liste de Tag associ�s.
 */
        void insertRelationTags(const Top& aTop,
                                const Top::ListeTags& aTags);

/**
 * Ajoute les enregistrements n�cessaires dans la table RelationMembers.
 * \param aTop Une r�f�rence sur une Relation.
 * \param aMembers Une r�f�rence sur une liste de Member associ�s.
 */
        void insertRelationMembers(const Top& aTop,
                                   const list<Member>& aMembers);


	public:
/**
 * Constructeur de l'instance.
 * Initialise une connexion au fichier de la base SQLite3.
 * \param aPath Chemin vers le fichier.
 * \param aFlags Options d'ouverture du fichier. Par d�faut en lecture/�criture
 *               et cr�ation en cas d'absence.
 */
		BaseOsm(const string& aPath,
                const bool aInitSpatialite = false,
                const int aFlags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

/**
 * Destructeur virtuel de l'instance.
 * Sans action.
 */
		virtual ~BaseOsm() {}

/**
 * Ajoute un Changeset dans la base.
 * \param aChangeset Une r�f�rence sur un Changeset qui sera ajout� dans la base.
 */
        void add(const Changeset& aChangeset);

/**
 * Ajoute un Node dans la base.
 * \param aNode Une r�f�rence sur un Node qui sera ajout� dans la base.
 */
        void add(const Node& aNode);

/**
 * Ajoute un Way dans la base.
 * \param aWay Une r�f�rence sur un Way qui sera ajout� dans la base.
 */
        void add(const Way& aWay);

/**
 * Ajoute une Relation dans la base.
 * \param aRelation Une r�f�rence sur une Relation qui sera ajout�e dans la base.
 */
        void add(const Relation& aRelation);

/**
 * Cr�� les indexes g�n�ralement n�cessaires.
 */
        void createIndexes();

/**
 * Retourne le nombre de Changeset dans la base (estimation).
 * \return Une estimation du nombre de Changeset.
 */
        unsigned nbChangesets() const { return fNbChangesets; }

/**
 * Retourne le nombre de Node dans la base (estimation).
 * \return Une estimation du nombre de Node.
 */
        unsigned nbNodes() const { return fNbNodes; }

/**
 * Retourne le nombre de Way dans la base (estimation).
 * \return Une estimation du nombre de Way.
 */
        unsigned nbWays() const { return fNbWays; }

/**
 * Retourne le nombre de Relation dans la base (estimation).
 * \return Une estimation du nombre de Relation.
 */
        unsigned nbRelations() const { return fNbRelations; }

};

#endif // BASEOSM_H
