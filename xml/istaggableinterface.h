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

#ifndef ISTAGGABLEINTERFACE_H
#define ISTAGGABLEINTERFACE_H

#include <string>

using namespace std;

/**
 * \interface IsTaggableInterface
 * Classe virtuelle pure (interface) assurant la capacit� d'ajouter un tag �
 * l'instance en h�ritant.
 */
class IsTaggableInterface
{
  public:
/**
 * Ajoute un Tag � l'instance.
 * @param aKey Une r�f�rence sur la valeur de la cl�.
 * @param aValue Une r�f�rence sur le contenu du Tag.
 */
    virtual void addTag(const string& aKey,
                        const string& aValue) = 0;
};

#endif
