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

#ifndef BASESQLITE3_H
#define BASESQLITE3_H

#include <spatialite/sqlite3.h>
#include <string>
#include <fstream>
#include "exception.h"
#include <iostream>
#include <sstream>

using namespace std;

/**
 * Wrapper autour du sqlite3_stmt qui permet son instanciation ais�e et sa
 * lib�ration automatique apr�s.
 */
class Commande
{
    private:
/**
 * Cr�e un sqlite_stmt � partir d'une requ�te SQL.
 * @param apSqlite3 Un pointeur vers une connexion SQLite3.
 * @param aSql Une cha�ne contenant la requ�te SQL.
 * @return Un pointeur sur le sqlite3_stmt.
 * @throw Exception en cas d'erreur pendant la cr�ation.
 */
        static sqlite3_stmt* preparer(sqlite3 *const apSqlite3,
                                      const string& aSql)
        {
        	sqlite3_stmt* pRes = 0;
        	if (SQLITE_OK != sqlite3_prepare_v2(apSqlite3, aSql.c_str(), aSql.size(), &pRes, 0))
                throw Exception(sqlite3_errmsg(apSqlite3), __FILE__, __LINE__, __PRETTY_FUNCTION__);
        	if (!pRes) throw Exception(string("Prepared statment NULL pour la requete ") + aSql,
                                       __FILE__, __LINE__, __PRETTY_FUNCTION__);
        	return pRes;
        }

    protected:
// Une cha�ne contenant la requ�te SQL.
//        string fSql;

/// Un pointeur sur la base concern�e (n�cessaire pour r�cup�rer les messages
/// d'erreur).
        sqlite3* fpSqlite3;

/// Un pointeur sur une commande.
        sqlite3_stmt* fpSqlite3_stmt;

    public:

/**
 * Constructeur de l'instance par d�faut.
 */
    Commande() :
//        fSql(""),
        fpSqlite3(0),
        fpSqlite3_stmt(0)
    {};

/**
 * Constructeur d'instance.
 * Initialise et pr�pare la commande � partir de la requ�te SQL pr�sent�e.
 * @param apSqlite3 Un pointeur sur l'instance de base de donn�es.
 * @param aSql Une cha�ne contenant la requ�te SQL � pr�parer.
 * @throw Exception en cas d'erreur pendant la cr�ation.
 */
    Commande(sqlite3 *const apSqlite3,
             const string aSql) :
//        fSql(aSql),
        fpSqlite3(apSqlite3),
        fpSqlite3_stmt(preparer(apSqlite3, aSql))
    {
//        assert(fSql.size());
        assert(fpSqlite3);
        assert(fpSqlite3_stmt);
    }

/**
 * \brief Destructeur de l'instance.
 *
 * Lib�re toutes les ressources li�es � la commande.
 * \throw Exception en cas d'erreur pendant la lib�ration.
 */
    ~Commande()
    {
        if (fpSqlite3_stmt) {
            assert(fpSqlite3);
            if (SQLITE_OK != sqlite3_finalize(fpSqlite3_stmt))
               throw Exception(sqlite3_errmsg(fpSqlite3), __FILE__, __LINE__, __PRETTY_FUNCTION__);
        }
    }

/**
 * \brief Red�finit la commande.
 *
 * Lib�re la commande existante et pr�-calcule une nouvelle commande SQL.
 * @param apSqlite3 Un pointeur sur l'instance de base de donn�es.
 * @param aSql Une cha�ne contenant la requ�te SQL � pr�parer.
 * @throw Exception en cas d'erreur pendant la cr�ation.
 */
    void setStatment(sqlite3 *const apSqlite3,
                     const string& aSql)
    {
        assert(apSqlite3);
        assert(aSql.size());
        if (fpSqlite3_stmt) {
            assert(fpSqlite3);
            if (SQLITE_OK != sqlite3_finalize(fpSqlite3_stmt))
               throw Exception(sqlite3_errmsg(fpSqlite3), __FILE__, __LINE__, __PRETTY_FUNCTION__);
        }
        fpSqlite3 = apSqlite3;
//        fSql = aSql;
        fpSqlite3_stmt = preparer(apSqlite3, aSql);
    }

/**
 * D�finit l'op�rateur * (d�r�f�rencement) pour qu'il retourne le sqlite3_stmt
 * sous-jacent.
 * @return Un pointeur sur le sqlite3_stmt.
 */
    sqlite3_stmt* operator*() { assert(fpSqlite3_stmt); return fpSqlite3_stmt; }

};

/**
 * Wrapper de la librairie SQLite3.
 */
class BaseSQLite3
{
	protected:
/// Handler de la connexion � la base de donn�es.
		sqlite3* fpSqlite3;

/**
 * V�rifie que le code erreur transmis est SQLITE_OK. Si la valeur est
 * diff�rente, l�ve une exception avec le message d'erreur correspondant.
 * @warning dans certains cas (SQLITE_ROW), la m�thode appelante doit filtrer
 *          avant de faire l'appel pour �viter la g�n�ration de l'exception.
 * @throw Exception Lorsque le code erreur transmis est diff�rent de SQLITE_OK.
 * @param aError Le code erreur � analyser.
 * @param aFichier Nom du fichier o� s'est fait l'appel, par d�faut __FILE__.
 * @param aLigne Num�ro de la ligne o� s'est fait l'appel, par d�faut __LINE__.
 * @param aFonction Fonction ou m�thode o� s'est fait l'appel, par d�faut __PRETTY_FUNCTION__.
 */
        inline void check(const int aError,
                          const string& aFichier = __FILE__,
                          const unsigned aLigne = __LINE__,
                          const string& aFonction = __PRETTY_FUNCTION__) const
{
    assert(fpSqlite3);
    if (aError == SQLITE_MISUSE)
        throw Exception("Mauvaise utilisation", aFichier, aLigne, aFonction);
	if (aError != SQLITE_OK) {
        const char *const p = sqlite3_errmsg(fpSqlite3);
        throw Exception((p ? p : "Erreur inconnue"), aFichier, aLigne, aFonction);
    }
}

  public:
/**
 * Constructeur de classe. Initialise l'acc�s � la base de donn�es.
 * @param aNom Chemin du fichier contenant la base de donn�es.
 * @param aFlags Indicateurs SQLite pr�cisant le mode d'ouverture du fichier.
 *               Par d�faut, c'est en SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE.
 */
		BaseSQLite3(const string& aNom,
		            const int aFlags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

/**
 * Destructeur de classe.
 */
		virtual ~BaseSQLite3();

/**
 * Ex�cute une requ�te SQL sans attendre de r�sultat.
 * @param aSql Une cha�ne contenant la requ�te SQL.
 */
		void exec(const string& aSql);

/**
 * Ex�cute la/les requ�te(s) SQL pr�sentent dans le fichier indiqu�.
 * @param aPath Le chemin du fichier � ex�cuter.
 */
		void execFile(const string& aPath);

        static int cbkReturnUnsigned(void* apResult, int aNbCols, char** apValues, char** apNames)
        {
            assert(apResult);
            assert(apValues);
            assert(apNames);
            if (aNbCols != 1) return -1; // erreur
            const string s = *apValues;
            istringstream iss(s);
            unsigned *const p = static_cast<unsigned*>(apResult);
            iss >> *p;
            return 0;
        }

		unsigned cacheSize() const
		{
            unsigned result = 0;
            check(sqlite3_exec(fpSqlite3, "PRAGMA cache_size", BaseSQLite3::cbkReturnUnsigned, &result, 0), __FILE__, __LINE__, __PRETTY_FUNCTION__);
            return result;
        }

		void cacheSize(const unsigned aSize)
		{
            ostringstream oss;
            oss << "PRAGMA cache_size=" << aSize;
            exec(oss.str());
        }
};

#endif
