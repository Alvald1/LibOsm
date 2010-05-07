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

// Class automatically generated by Dev-C++ New Class wizard

#ifndef CHANGESET_H
#define CHANGESET_H

#include "top.h" // inheriting class's header file

#include <ctime>
#include <string>
#include "datetimeiso8601.h"

using namespace std;

/**
 * Classe d�finissant un Changset tel que le d�crit l'Api OSM.
 */
class Changeset : public Top
{
    protected:
        DateTimeISO8601 fCreatedAt;

        DateTimeISO8601 fClosedAt;

        bool fOpen;

        double fMinLon;

        double fMinLat;

        double fMaxLon;

        double fMaxLat;

    public:
/**
 * Constructeur de l'instance faisant aussi office de constructeur par d�faut.
 */
        Changeset() :
            Top(0, "", 0),
            fCreatedAt(),
            fClosedAt(),
            fOpen(false),
            fMinLon(0),
            fMinLat(0),
            fMaxLon(0),
            fMaxLat(0)
        {}

/**
 * Destructeur de l'instance.
 */
        virtual ~Changeset() {}

/**
 * Ajoute un attribut � l'instance Changeset.
 * L'attribut doit faire partie de la liste accept� par les ELements de l'Api osm.
 * @param aKey Le nom de l'attribut.
 * @param aValue La valeur de l'attribut sous la forme d'une cha�ne de caract�res.
 */
		virtual void setAttribut(const string& aKey, const string& aValue);


/// Nom de la classe utilis�e par certaines m�thodes templates de la classe ApiOsm.
        static const string NOM;

/**
 * Injecte une description du Changeset au format XML de l'API Osm dans un flux
 * de sortie.
 * @param aStream Un flux de sortie.
 * @return Le flux de sortie apr�s injection de la description de l'Element.
 */
        ostream& afficher(ostream& aStream) const;

/**
 * Test et retourne l'�galit� des diff�rents champs de l'instance.
 * @param aChangeset Une r�f�rence sur le Changeset compar� � l'instance.
 * @return true si les 2 Elements sont �gaux, false sinon.
 */
        bool operator==(const Changeset& aChangeset) const;

        const DateTimeISO8601& createdAt() const { return fCreatedAt; }

        const DateTimeISO8601& closedAt() const { return fClosedAt; }

        bool open() const { return fOpen; }

        const double& minLon() const { return fMinLon; }

        const double& minLat() const { return fMinLat; }

        const double& maxLon() const { return fMaxLon; }

        const double& maxLat() const { return fMaxLat; }
};

/**
 * Permet l'injection de la description d'une instance de Changeset dans un flux
 * de sortie. La pr�sentation correspond � un flux XML.
 * @param aStream Un flux de sortie recevant la description.
 * @param aChangeset L'instance dont la description est produite.
 * @return Le flux de sortie apr�s injection de la description.
 */
ostream& operator<<(ostream& aStream, const Changeset& aChangeset);

#endif // CHANGESET_H