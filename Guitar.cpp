/***********************************************************************
// OOP244 Workshop #4 p2: tester program
//
// Version 1.0
// Date: Summer 2023
// Author Michael Huang
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Guitar.h"


using namespace std;

namespace seneca {
    const char* GuitarStr::material() const {
        return m_material;
    }
    double GuitarStr::gauge() const {
        return m_gauge;
    }
    GuitarStr::GuitarStr() {};

    GuitarStr::GuitarStr(const char* ma, double ga)
    {
        strncpy(m_material, ma, MAT_LEN);
        m_gauge = ga;

    };


    Guitar::Guitar(const char* mod)
    {
        m_strings = nullptr;
        m_numStrings = 0;

        if (mod != nullptr && mod[0] != '\0')
        {
            strcpy(m_model, mod);
        }
    }

    Guitar::Guitar(GuitarStr strs[], int ns, const char* mod)
    {
        if (strs != nullptr && ns > 0 && mod != nullptr && mod[0] != '\0' )
        {
            m_numStrings = ns;
            strcpy(m_model, mod);
            m_strings = new GuitarStr[m_numStrings];

            for (int i = 0; i < m_numStrings; i++)
            {
                m_strings[i] = strs[i];
            }
        }
    }

    Guitar::~Guitar()
    {
        deString();
    }

    bool Guitar::changeString(const GuitarStr& gs, int sn)
    {
        bool change = false;
         
        if (sn >= 0 && sn <= m_numStrings)
        {
            m_strings[sn] = gs;
            change = true;
        }
        else
        {
            change = false;
        }

        return change;
    }

    void Guitar::reString(GuitarStr strs[], int ns)
    {
        if (ns >= 0 && strs != nullptr)
        {
            if (!strung())
            {
                m_numStrings = ns;
                m_strings = new GuitarStr[m_numStrings];
            }
            else if (m_strings != nullptr)
            {
                deString();
                m_numStrings = ns;
                m_strings = new GuitarStr[m_numStrings];
            }


            for (int i = 0; i < m_numStrings; i++)
            {
               m_strings[i] = strs[i];
            }
            
        }
    }

    void Guitar::deString()
    {
        if (m_strings != nullptr)
        {
            delete[] m_strings;

            m_strings = nullptr;

            m_numStrings = 0;
        }
    }

    bool Guitar::strung() const
    {
        bool strung = false;

        if (m_numStrings > 0)
        {
            strung = true;
        }

        return strung;
    }


    bool Guitar::matchGauge(double ga) const
    {
        bool match = false;

        for (int i = 0; i < m_numStrings && match == false; i++)
        {
            if (m_strings[i].gauge() == ga)
            {
                match = true;
            }
        }

        return match;
    }


    std::ostream& Guitar::display(std::ostream& os) const
    {
        if (!strung())
        {
            os << "***Empty Guitar***\n";
        }

        else
        {
            os << "Guitar Model: " << m_model << endl;
            os << "Strings: " << m_numStrings << endl;

            if (strung())
            {
                for (int i = 0; i < m_numStrings; i++)
                {
                    os << "#" << i + 1;
                    os.width(MAT_LEN);
                    os << m_strings[i].material();
                    os <<" | ";
                    os.setf(ios::fixed);
                    os.precision(1);
                    os << m_strings[i].gauge() << endl;
                }
            }
        }

        return os;
    }
}