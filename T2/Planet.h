/**
   \file Planet.h
   \brief Descreve o modelo para um planeta

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _PLANET_NOT_INCLUDED_
#define _PLANET_NOT_INCLUDED_

#include "Joint.h"

/**
   \class Planet
   \brief Responsavel por construir um planeta<br>

   \sa Object()
*/
class Planet: public Joint
{
protected:
    float fYearST,      ///< frame inicial da anima�ao de transla�ao do planeta
          fYearEND,     ///< frame final da anima��o de transla�ao do planeta
          fDayST,       ///< frame inicial da anima�ao de rota�ao do planeta
          fDayEND;      ///< frame final da anima�ao de rota�ao do planeta
    bool  bAnimateDay,  ///< flag que indica a anima�ao do dia
          bAnimateYear; ///< flag que indica a anima�ao do ano

public:
    Planet( bool = true, bool = true );
    Planet( const Planet & );
    Planet( Planet* );

    virtual void Initialize();

    void setYearAnimation( float, float );
    void setDayAnimation( float, float );
};

#endif
