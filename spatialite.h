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

#ifndef SPATIALITE_H
#define SPATIALITE_H

#include <spatialite/sqlite3.h>
#include <spatialite/gaiageo.h>
#include <spatialite.h>
#include <string>

using namespace std;

/**
 * Classe wrapper de la biblioth�que Spatialite sous la forme d'un Singleton.
 *  Pour obtenir une instance, appeler la m�thode makeSpatialite().
 */
class Spatialite
{
	private:
/// Instance unique de la classe
		static Spatialite* fpSpatialite;

	protected:
/**
 * Constructeur de l'instance. Il est prot�g� pour s'assurer du respect du
 * singleton.
 */
		Spatialite(void);

	public:
/**
 * Retourne une r�f�rence sur l'unique instance du singleton.
 * @return Une r�f�rence sur une instance de Spatialite.
 */
		static Spatialite& makeSpatialite(void);

/**
 * Retourne une cha�ne d�crivant les versions des biblioth�ques utilis�es.
 * @return Une cha�ne de caract�res.
 */
		string versions(void) const;

};

#endif
