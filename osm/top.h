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

/**
 * \page arbo_elem Arborescence des classes d'OSM
 *
 * Cette arborescence correspond aux object m�tier de OSM tels que l'on peut les
 * appr�hender au travers des diff�rents flux XML fournis par les applications,
 * en particulier celle qui utilisent les diff�rentes variation de .osm (http://wiki.openstreetmap.org/wiki/.osm) :
 * - les flux XML retourn�s par l'API v0.6 (http://wiki.openstreetmap.org/wiki/API_v0.6) ;
 * - ceux retourn�s par la version �tendues XAPI (http://wiki.openstreetmap.org/wiki/Xapi) ;
 * - les fichiers planet (http://wiki.openstreetmap.org/wiki/Planet) et les
 *   diffs (http://wiki.openstreetmap.org/wiki/Planet.osm/diffs) correspondants.
 *
 * L'arborescence ressence deux classes abstraites qui permettent de regrouper
 * certaines fonctionnalit�s communes aux classes h�rit�es.
 * On trouvera donc :
 * - \ref Top : la classe anc�tre ultime qui assurent les champs communs (comme l'id,
 *         le nom d'utilisateur, son identifiant) et l'aptitude � g�rer les Tags.
 * - \ref Element : cette classe permet f�d�rer les �l�ments g�om�triques (Node, Way
 *             et Relation).
 *
 * La classe Node h�rite aussi d'une autre classe. Cette classe Point permet
 * quelques op�rations sur les coordonn�es angulaires comme des comparaisons
 * (operator==), des mesures de distance approximatives en projection sph�rique
 * et des mesures d'angle par rapport au Nord g�ographique (Bearing).
 *

\dot
digraph G {
    node [shape = record fontname="FreeSans" fontsize=8];
    rankdir=BT

    Top [label="/Top" URL="\ref Top"];
    Tag [label="{Tag|- key : string\l- value : string}" URL="\ref Tag"};
    Member [label="{Member||+ id() : int\l+ type() : (NODE, WAY, RELATION)\l+ role() : string\l}" URL="\ref Member"];
    Point [label="{Point|- longitude : double\l- latitude : double\l}" URL="\ref Point"];
    Element [label="{/Element||+ id() : int\l}" URL="\ref Element"];
    "Node" [URL="\ref Node"];
    Way [URL="\ref Way"];
    Relation [URL="\ref Relation"];
    Changeset [URL="\ref Changeset"];

    Top -> Tag [arrowhead="empty"];

    Element -> Top [URL="\ref Element" arrowhead="empty"];
    Changeset -> Top [URL="\ref Element" arrowhead="empty"];

    "Node" -> Element [URL="\ref Element" arrowhead="empty"];
    "Node" -> Point [URL="\ref Point" arrowhead="empty"];
    Way -> Element [URL="\ref Element" arrowhead="empty"];
    Relation -> Element [arrowhead = "empty"];
    Way -> IdNode [arrowhead="vee" arrowtail="diamond" label="{order}" headlabel="\n      2..*"];
    Relation -> Member [arrowhead="open" arrowtail="diamond" headlabel="\n  *"];
}
\enddot

 *
 */

#ifndef TOP_H
#define TOP_H

#include <map>
#include <string>

using namespace std;

/**
 * Classe anc�tre ultime des diff�rents composants d'OSM.
 * Elle est rendues abstraite en prot�geant son constructeur.
 */
class Top
{
    public:
/// D�finition du type de la liste de Tags.
/// @see fTags
        typedef map<string, string> ListeTags;

    protected:
/// Identifiant de l'�l�ment dans la base OSM.
        unsigned long fId;

/// Compte utilisateur ayant cr�e, modifi� l'Element dans la base.
        string fUser;

/// Identifiant utilisateur.
        unsigned long fUid;

/// Liste des Tags affect�s � cet Element.
        ListeTags fTags;


        static string xmlEntities(const string& aXml);

/**
 * Constructeur de classe. Initialise les diff�rents attributs.
 * Ce constructeur est prot�g� pour assurer la non-instanciation de cette classe.
 */
		Top(const unsigned long& aId = 0,
            const string& aUser = "",
            const unsigned long& aUid = 0) :
            fId(aId),
            fUser(aUser),
            fUid(aUid)
        {}

	public:
/**
 * Destructeur virtuel de l'instance. Sans action particuli�re.
 */
		~Top() {};

/**
 * D�finit un des attributs de l'Element.
 * Les classes h�ritant de celle-ci doivent d�finir leur propres m�thodes
 * setAttribut pour prendre en compte d'autres attributs.
 * @param aKey Nom de l'attribut.
 * @param aValue Cha�ne contenant la valeur � affecter � l'attribut.
 * @throw OsmException si l'attribut n'existe pas pour cet Element.
 */
		virtual void setAttribut(const string& aKey, const string& aValue);

/**
 * Ajoute un Tag � l'Element.
 * @param aKey Nom du Tag.
 * @param aValue Valeur du Tag.
 */
		void setTag(const string& aKey, const string& aValue);

/**
 * Retourne la valeur d'un Tag.
 * @param aKey Le nom du Tag dont on cherche la valeur.
 * @return La valeur du Tag.
 * @throw OsmException si le Tag n'est pas d�fini pour cet Element.
 */
		const string& getTag(const string& aKey) const;

/**
 * Retourne La liste des Tags.
 * @return Une r�f�rence sur la liste des Tags.
 */
    	const ListeTags& tags() const { return fTags; }

/**
 * Retourne l'Id de l'Element.
 * @return Un entier non-sign�, nul si l'Element n'est pas r�f�renc� dans la
 * base OSM.
 */
	   const unsigned long& id() const { return fId; }

	   const string& user() const { return fUser; }

	   const unsigned long& uid() const { return fUid; }

/**
 * Injecte une description de l'Element au format XML de l'API Osm dans un flux
 * de sortie.
 * @param aStream Un flux de sortie.
 * @return Le flux de sortie apr�s injection de la description de l'Element.
 */
	   virtual ostream& afficher(ostream& aStream) const;

/**
 * Injecte une description l'ensemble des Tags au format XML de l'API Osm dans
 * un flux de sortie.
 * @param aStream Un flux de sortie.
 * @return Le flux de sortie apr�s injection des Tags.
 */
	   ostream& afficherTags(ostream& aStream) const;

/**
 * Test et retourne l'�galit� des diff�rents champs de l'instance.
 * @param aTop Une r�f�rence sur le Top compar� � l'instance.
 * @return true si les 2 Tops sont �gaux, false sinon.
 */
	   virtual bool operator==(const Top& aTop) const;


};

#endif // TOP_H
